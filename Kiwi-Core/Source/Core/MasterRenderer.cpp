#include "MasterRenderer.h"

#include "OpenGL/OpenGLRenderer.h"

namespace Kiwi {

	glm::mat4 CreateModelMatrix(const Transform& transform)
	{
		glm::mat4 model = glm::mat4(1.0f);

		model = glm::scale(model, transform.scale);

		model = glm::rotate(model, glm::radians(transform.rotation.z), glm::vec3(0, 0, 1)); // Roll
		model = glm::rotate(model, glm::radians(transform.rotation.y), glm::vec3(0, 1, 0)); // Yaw
		model = glm::rotate(model, glm::radians(transform.rotation.x), glm::vec3(1, 0, 0)); // Pitch

		model = glm::translate(model, transform.position);

		return model;
	}

	glm::vec3 GetForwardVector(const Transform& transform)
	{
		float pitch = glm::radians(transform.rotation.x);
		float yaw = glm::radians(transform.rotation.y);

		glm::vec3 forward;
		forward.x = cos(pitch) * sin(yaw);
		forward.y = sin(pitch);
		forward.z = cos(pitch) * cos(yaw);
		return glm::normalize(forward);
	}

	glm::mat4 CreateViewMatrix(const Camera& camera)
	{
		glm::vec3 position = camera.transform.position;
		glm::vec3 forward = GetForwardVector(camera.transform);
		glm::vec3 up = glm::vec3(0, 1, 0);

		glm::vec3 target = position + forward;
		return glm::lookAt(position, target, up);
	}

	glm::mat4 CreateProjectionMatrix(const Camera& camera, int viewportWidth, int viewportHeight)
	{
		float aspectRatio = static_cast<float>(viewportWidth) / static_cast<float>(viewportHeight);

		if (camera.perspective)
		{
			return glm::perspective(glm::radians(static_cast<float>(camera.FOV)), aspectRatio, camera.near, camera.far);
		}
		else
		{
			float orthoScale = 10.0f;
			float left = -orthoScale * aspectRatio;
			float right = orthoScale * aspectRatio;
			float bottom = -orthoScale;
			float top = orthoScale;
			return glm::ortho(left, right, bottom, top, camera.near, camera.far);
		}
	}

	void Renderer::PushMesh(Ref<Mesh> mesh, Ref<ShaderProgramme> shaderProgramme, const Transform& transform, Material material)
	{
		DrawCallData data = DrawCallData(mesh, shaderProgramme, transform, material);

		m_DrawQueue.push_back(data);
	}

	Ref<Kiwi::Renderer> CreateRenderer(RendererType rendererType)
	{
		g_RendererType = rendererType;

		if (rendererType == RendererType::OpenGL)
			return MakeRef<OpenGLRenderer>();
		else if (rendererType == RendererType::None)
			return nullptr;
		else
			return nullptr;
	}

	Ref<Mesh> CreateMesh(std::vector<float> vertices, std::vector<float> texCoords, std::vector<float> normals, std::vector<uint32_t> indices)
	{
		if (g_RendererType == RendererType::OpenGL)
			return MakeRef<OpenGLMesh>(vertices, texCoords, normals, indices);
		else if (g_RendererType == RendererType::None)
			return nullptr;
		else
			return nullptr;
	}

	Ref<Texture> LoadTexture(std::filesystem::path filePath, bool linear)
	{
		if (g_RendererType == RendererType::OpenGL)
			return MakeRef<OpenGLTexture>(filePath, linear);
		else if (g_RendererType == RendererType::None)
			return nullptr;
		else
			return nullptr;
	}

	Ref<ShaderProgramme> CreateShaderProgramme(ShaderProgrammeCreateArgs shaderProgrammeCreateArgs)
	{
		if (g_RendererType == RendererType::OpenGL)
			return MakeRef<OpenGLShaderProgramme>(shaderProgrammeCreateArgs);
		else if (g_RendererType == RendererType::None)
			return nullptr;
		else
			return nullptr;
	}

}