#include "OpenGLRenderer.h"

namespace Kiwi {

	OpenGLRenderer::OpenGLRenderer()
	{
		if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
			KW_ASSERT(false);
	}

	OpenGLRenderer::~OpenGLRenderer() {}

	void OpenGLRenderer::Clear(glm::vec4 colour)
	{
		glViewport(0, 0, g_CurrentWindow->GetWidth(), g_CurrentWindow->GetHeight());

		glClearColor(colour.r, colour.g, colour.b, colour.a);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}

	void OpenGLRenderer::RenderMesh(Ref<Mesh> mesh)
	{
		mesh->Bind();

		glDrawElements(GL_TRIANGLES, mesh->GetIndicesCount(), GL_UNSIGNED_INT, (void*)0);

		mesh->Unbind();
	}

	OpenGLMesh::OpenGLMesh(std::vector<float> vertices, std::vector<uint32_t> indices)
	{
		m_IndicesCount = indices.size();

		glGenVertexArrays(1, &m_VAO);
		glGenBuffers(1, &m_VBO);
		glGenBuffers(1, &m_EBO);

		glBindVertexArray(m_VAO);

		glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
		glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), vertices.data(), GL_STATIC_DRAW);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_EBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(uint32_t), indices.data(), GL_STATIC_DRAW);

		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);

		glBindVertexArray(0);
	}

	OpenGLMesh::~OpenGLMesh() {}

	void OpenGLMesh::Bind()
	{
		glBindVertexArray(m_VAO);
	}

	void OpenGLMesh::Unbind()
	{
		glBindVertexArray(null);
	}

	int32_t OpenGLMesh::GetIndicesCount()
	{
		return m_IndicesCount;
	}

}
