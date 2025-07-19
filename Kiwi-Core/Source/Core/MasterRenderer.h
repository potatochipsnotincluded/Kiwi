#pragma once
#include "Common.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/constants.hpp>

namespace Kiwi {

	struct Transform
	{
		glm::vec3 position;
		glm::vec3 rotation;
		glm::vec3 scale;

		inline Transform()
		{
			position = glm::vec3();
			rotation = glm::vec3();
			scale = glm::vec3(1);
		}

		inline Transform(glm::vec3 position, glm::vec3 rotation, glm::vec3 scale)
		{
			this->position = position;
			this->rotation = rotation;
			this->scale = scale;
		}
	};

	struct Camera
	{
		Transform transform;
		uint32_t FOV;

		bool perspective;

		float near;
		float far;

		inline Camera()
		{
			transform = Transform();
			transform.position.z = -5;

			FOV = 45;

			perspective = true;

			near = 0.1f;
			far = 100.0f;
		}
	};

	struct SunLight
	{
		glm::vec3 sunPosition;
		glm::vec3 sunColour;

		float intensity;

		float ambient;

		SunLight()
		{
			sunPosition = glm::vec3(0, 10, 10);
			sunColour = glm::vec3(1.0f, 1.0f, 1.0f);

			intensity = 10;

			ambient = 0.2f;
		}
	};

	inline Ref<Camera> g_MainCamera = MakeRef<Camera>();

	inline Ref<SunLight> g_SunLight = MakeRef<SunLight>();

	glm::mat4 CreateModelMatrix(const Transform& transform);

	glm::vec3 GetForwardVector(const Transform& transform);

	glm::mat4 CreateViewMatrix(const Camera& camera);

	glm::mat4 CreateProjectionMatrix(const Camera& camera, int viewportWidth, int viewportHeight);

	class OpenGLRenderer;
	class OpenGLMesh;

	enum class UniformType
	{
		Float,
		Vec2,
		Vec3,
		Vec4,
		Int,
		UInt,
		Bool,
		Mat2,
		Mat3,
		Mat4,
		Texture
	};

	enum class RendererType
	{
		OpenGL,
		None
	};

	inline RendererType g_RendererType;

	class Mesh
	{
	public:
		virtual ~Mesh() = default;

		virtual void Bind() = 0;

		virtual void Unbind() = 0;
		
		virtual int32_t GetIndicesCount() = 0;
	};

	struct ShaderProgrammeCreateArgs
	{
		std::filesystem::path openGLVertexShaderPath;
		std::filesystem::path openGLFragmentShaderPath;
	};

	class ShaderProgramme
	{
	public:
		virtual ~ShaderProgramme() = default;

		virtual void Start() = 0;

		virtual void Stop() = 0;

		virtual void AddUniform(std::string_view uniformName, UniformType uniformType, void* value) = 0;
	};

	class Texture
	{
	public:
		virtual ~Texture() = default;

		virtual void Bind() = 0;

		virtual void Unbind() = 0;
	};

	struct Material
	{
		Ref<Texture> albedoMap;

		float metallic;
		float roughness;
	};

	struct DrawCallData
	{
		Ref<Mesh> mesh;
		Ref<ShaderProgramme> shaderProgramme;
		const Transform& transform;
		Material material;
	};

	class Renderer
	{
	public:
		virtual ~Renderer() = default;

		virtual void Clear(glm::vec4 colour) = 0;

		virtual void Render() = 0;

		virtual void ImGuiStartFrame() = 0;
		virtual void ImGuiEndFrame() = 0;

		void PushMesh(Ref<Mesh> mesh, Ref<ShaderProgramme> shaderProgramme, const Transform& transform, Material material);

	protected:
		std::vector<DrawCallData> m_DrawQueue;
	};

	Ref<Renderer> CreateRenderer(RendererType rendererType);

	Ref<Mesh> CreateMesh(std::vector<float> vertices, std::vector<float> texCoords, std::vector<float> normals, std::vector<uint32_t> indices);

	Ref<Texture> LoadTexture(std::filesystem::path filePath, bool linear);

	Ref<ShaderProgramme> CreateShaderProgramme(ShaderProgrammeCreateArgs shaderProgrammeCreateArgs);

}