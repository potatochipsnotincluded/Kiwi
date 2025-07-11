#pragma once
#include "../Common.h"

#include "../Maths.h"

#include <raylib.h>
#include <raymath.h>

namespace Kiwi {

	struct SunLight
	{
		Vec3 position;
		Colour colour;

		float intensity;
	};

	struct Image2D
	{
		Texture2D raylibTexture;
		std::filesystem::path filePath;

		~Image2D()
		{
			UnloadTexture(raylibTexture);
		}
	};

	struct Material
	{
		float roughness = 1.0f;
		float metalness = 0.0f;
		
		Colour diffuseColour;

		Image2D* texture;
	};

	struct Mesh
	{
		Model raylibModel;

		Material material;

		inline ~Mesh()
		{
			UnloadModel(raylibModel);
		}
	};

	inline Transform* g_MainCamera;
	inline float g_FOV = 45;
	inline bool g_IsPerspective = true;

	inline SunLight* g_SunLight;

	inline float g_Ambient = 0.1f;

	Camera UpdateCamera();
	
	namespace TextureHelpers {

		Image2D LoadImage(std::filesystem::path filePath);

	}

	namespace Renderer {

		class ShaderManager
		{
		public:
			~ShaderManager();

			virtual void SetShaderParams(Material material) = 0;

			Shader GetShader();
			
		protected:
			Shader m_Shader;
		};

		class PBRShader : public ShaderManager
		{
		public:
			PBRShader();

			virtual void SetShaderParams(Material material) override;
		};

		struct MeshDrawData
		{
			Mesh* mesh;
			Transform transform;
			ShaderManager* shaderManager;
		};

		class MasterRenderer
		{
		public:
			void Clear(Colour colour);

			void QueueMesh(Mesh* mesh, Transform transform, ShaderManager* shaderManager);

			void Render3D();

			void Present();

		private:
			void DrawMesh(Mesh* mesh, Transform transform, ShaderManager* shaderManager);

			void MainRenderPass();
		private:
			std::vector<MeshDrawData> m_DrawQueue;
		};

	}

	Mesh LoadMesh(std::filesystem::path filePath, Image2D* texture, Renderer::ShaderManager* shaderManager);

}