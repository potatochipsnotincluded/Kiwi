#include "Renderer.h"

#define RLIGHTS_IMPLEMENTATION
#include "rlights.h"

#include <rlgl.h>

namespace Kiwi {

	Camera UpdateCamera()
	{
		Camera camera = { 0 };
		camera.position = g_MainCamera->position;

		float yawRadians = g_MainCamera->rotation.y * DEG2RAD;

		Vector3 forward = {
			sinf(yawRadians),
			0.0f,
			cosf(yawRadians)
		};

		camera.target = Vector3Add(g_MainCamera->position, forward);

		camera.up = { 0.0f, 1.0f, 0.0f };

		camera.fovy = g_FOV;

		camera.projection = g_IsPerspective ? CAMERA_PERSPECTIVE : CAMERA_ORTHOGRAPHIC;

		return camera;
	}

	Mesh LoadMesh(std::filesystem::path filePath, Image2D* image, Renderer::ShaderManager* shaderManager)
	{
		Model model = LoadModel(filePath.string().c_str());
		Material material = Material{1.0f, 0.0f, Kiwi::Colour(1,1,1,1), image};

		SetTextureFilter(material.texture->raylibTexture, TEXTURE_FILTER_TRILINEAR);

		for (int i = 0; i < model.materialCount; i++)
		{
			model.materials[i].shader = shaderManager->GetShader();
			model.materials[i].maps[MATERIAL_MAP_DIFFUSE].texture = material.texture->raylibTexture;
		}
		
		return Mesh(model, material);
	}

	namespace Renderer {

		ShaderManager::~ShaderManager()
		{
			UnloadShader(m_Shader);
		}

		Shader ShaderManager::GetShader()
		{
			return m_Shader;
		}

		PBRShader::PBRShader()
		{
			m_Shader = LoadShader("../Shaders/lighting.vert", "../Shaders/lighting.frag");
		}

		void PBRShader::SetShaderParams(Material material)
		{
			float cameraPos[3] = { g_MainCamera->position.x, g_MainCamera->position.y, g_MainCamera->position.z };
			SetShaderValue(m_Shader, m_Shader.locs[SHADER_LOC_VECTOR_VIEW], cameraPos, SHADER_UNIFORM_VEC3);

			Light light = CreateLight(LIGHT_DIRECTIONAL, g_SunLight->position, Vector3Zero(), g_SunLight->colour*g_SunLight->intensity, m_Shader);
		
			UpdateLightValues(m_Shader, light);

			int ambientLoc = GetShaderLocation(m_Shader, "ambient");
			float ambient[4] = { g_Ambient, g_Ambient, g_Ambient, g_Ambient };
			SetShaderValue(m_Shader, ambientLoc, ambient, SHADER_UNIFORM_VEC4);

			int loc_roughness = GetShaderLocation(m_Shader, "roughnessValue");
			int loc_metallic = GetShaderLocation(m_Shader, "metallicValue");

			float roughness = material.roughness;
			float metallic = material.metalness;

			SetShaderValue(m_Shader, loc_roughness, &roughness, SHADER_UNIFORM_FLOAT);
			SetShaderValue(m_Shader, loc_metallic, &metallic, SHADER_UNIFORM_FLOAT);

			int loc_diffuse = GetShaderLocation(m_Shader, "colDiffuse");

			Color diffuse = material.diffuseColour;

			SetShaderValue(m_Shader, loc_diffuse, &diffuse, SHADER_UNIFORM_VEC4);
		}

		DepthTextureShader::DepthTextureShader()
		{
			m_Shader = LoadShader("../Shaders/depth_texture.vert", "../Shaders/depth_texture.frag");
		}

		void DepthTextureShader::SetShaderParams(Material material)
		{
			float cameraPos[3] = { g_MainCamera->position.x, g_MainCamera->position.y, g_MainCamera->position.z };
			SetShaderValue(m_Shader, m_Shader.locs[SHADER_LOC_VECTOR_VIEW], cameraPos, SHADER_UNIFORM_VEC3);
		}

		MasterRenderer::MasterRenderer()
			: m_ClearColour (0,0,0,1)
		{
			m_DepthTexture = LoadRenderTexture(GetScreenWidth(), GetScreenHeight());
			m_MainTexture = LoadRenderTexture(GetScreenWidth(), GetScreenHeight());
		}

		void MasterRenderer::Clear(Colour colour)
		{
			m_ClearColour = colour;
		}

		void MasterRenderer::QueueMesh(Mesh* mesh, Transform transform, ShaderManager* shaderManager)
		{
			MeshDrawData drawData = MeshDrawData(mesh, transform, shaderManager);
			m_DrawQueue.push_back(drawData);
		}

		void MasterRenderer::DrawMesh(Mesh* mesh, Transform transform, ShaderManager* shaderManager)
		{
			Vector3 position = { transform.position.x, transform.position.y, transform.position.z };
			Vector3 rotation = { DEG2RAD * transform.rotation.x, DEG2RAD * transform.rotation.y, DEG2RAD * transform.rotation.z };
			Vector3 scale = { transform.scale.x, transform.scale.y, transform.scale.z };

			Matrix transMat = MatrixTranslate(position.x, position.y, position.z);
			Matrix rotXMat = MatrixRotateX(rotation.x);
			Matrix rotYMat = MatrixRotateY(rotation.y);
			Matrix rotZMat = MatrixRotateZ(rotation.z);
			Matrix scaleMat = MatrixScale(scale.x, scale.y, scale.z);

			Matrix trsm = MatrixMultiply(MatrixMultiply(MatrixMultiply(scaleMat, rotZMat), MatrixMultiply(rotYMat, rotXMat)), transMat);

			mesh->raylibModel.transform = trsm;
		
			shaderManager->SetShaderParams(mesh->material);

			DrawModel(mesh->raylibModel, Vector3Zero(), 1.0f, WHITE);
		}

		void MasterRenderer::ShadowRenderPass()
		{
			Camera cam = { 0 };
			cam.position = g_SunLight->position;
			cam.target = Vector3 { 0.0f, 0.0f, 0.0f };
			cam.up = Vector3 { 0.0f, 1.0f, 0.0f };

			cam.fovy = 45.0f;
			cam.projection = CAMERA_PERSPECTIVE;

			BeginTextureMode(m_DepthTexture);

			//ClearBackground(Color{255,255,255,255});
			ClearBackground(Color{0,0,0,255});

			BeginMode3D(cam);

			BeginShaderMode(m_DepthShader.GetShader());

			for (MeshDrawData& drawData : m_DrawQueue)
			{
				DrawMesh(drawData.mesh, drawData.transform, &m_DepthShader);
			}

			EndShaderMode();

			EndMode3D();

			EndTextureMode();
		}

		void MasterRenderer::MainRenderPass()
		{
			BeginTextureMode(m_MainTexture);

			ClearBackground(m_ClearColour);

			BeginMode3D(UpdateCamera());

			for (MeshDrawData& drawData : m_DrawQueue)
			{
				BeginShaderMode(drawData.shaderManager->GetShader());

				int location_DepthTexture = GetShaderLocation(drawData.shaderManager->GetShader(), "shadowMap");
				SetShaderValueTexture(drawData.shaderManager->GetShader(), location_DepthTexture, m_DepthTexture.texture);

				DrawMesh(drawData.mesh, drawData.transform, drawData.shaderManager);

				EndShaderMode();
			}

			EndMode3D();

			EndTextureMode();
		}

		void MasterRenderer::Render3D()
		{
			ShadowRenderPass();

			MainRenderPass();

			m_DrawQueue.clear();

			BeginDrawing();

			ClearBackground(m_ClearColour);

			DrawTextureRec(
				m_MainTexture.texture,
			Rectangle {
				0, 0, (float)m_DepthTexture.texture.width, -(float)m_DepthTexture.texture.height
			},
				Vector2 {
				0, 0
			},
				WHITE
			);

			DrawFPS(10, 10);

			EndDrawing();
		}

	}

	Image2D TextureHelpers::LoadImage(std::filesystem::path filePath)
	{
		return Image2D(LoadTexture(filePath.string().c_str()), filePath);
	}

}

