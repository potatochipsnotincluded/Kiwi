#pragma once
#include "../Common.h"

#include "../MasterRenderer.h"

#include "../Window.h"

#include <glad/glad.h>

namespace Kiwi {

	class OpenGLMesh : public Mesh
	{
	public:
		OpenGLMesh(std::vector<float> vertices, std::vector<uint32_t> indices);

		virtual ~OpenGLMesh() override;

		virtual void Bind() override;

		virtual void Unbind() override;

		virtual int32_t GetIndicesCount() override;

	private:
		uint32_t m_VBO = null;
		uint32_t m_EBO = null;
		uint32_t m_VAO = null;

		int32_t m_IndicesCount = null;
	};

	class OpenGLRenderer : public Renderer
	{
	public:
		OpenGLRenderer();

		virtual ~OpenGLRenderer() override;

		virtual void Clear(glm::vec4 colour) override;

		virtual void RenderMesh(Ref<Mesh> mesh) override;
	};

}