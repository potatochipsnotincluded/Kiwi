#pragma once
#include "Common.h"

#include "Pointers.h"

#include <glm/glm.hpp>

namespace Kiwi {

	class OpenGLRenderer;
	class OpenGLMesh;

	enum class RendererType
	{
		OpenGL,
		None
	};

	inline RendererType g_RendererType;

	class Mesh
	{
	public:
		virtual ~Mesh() {};

		virtual void Bind() = 0;

		virtual void Unbind() = 0;
		
		virtual int32_t GetIndicesCount() = 0;
	};

	class Renderer
	{
	public:
		virtual ~Renderer() {};

		virtual void Clear(glm::vec4 colour) = 0;

		virtual void RenderMesh(Ref<Mesh> mesh) = 0;
	};

	Ref<Renderer> CreateRenderer(RendererType rendererType);

	Ref<Mesh> CreateMesh(std::vector<float> vertices, std::vector<uint32_t> indices);

}