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

	inline Ref<Camera> g_MainCamera = MakeRef<Camera>();

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

	class Renderer
	{
	public:
		virtual ~Renderer() = default;

		virtual void Clear(glm::vec4 colour) = 0;

		virtual void RenderMesh(Ref<Mesh> mesh, Ref<ShaderProgramme> shaderProgramme, Transform transform) = 0;
	};

	Ref<Renderer> CreateRenderer(RendererType rendererType);

	Ref<Mesh> CreateMesh(std::vector<float> vertices, std::vector<uint32_t> indices);

	Ref<ShaderProgramme> CreateShaderProgramme(ShaderProgrammeCreateArgs shaderProgrammeCreateArgs);

}