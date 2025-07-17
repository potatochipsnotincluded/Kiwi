#include "OpenGLRenderer.h"

namespace Kiwi {

	OpenGLRenderer::OpenGLRenderer()
	{
		if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
			KW_ASSERT("Could not load OpenGL", false);
	}

	OpenGLRenderer::~OpenGLRenderer() {}

	void OpenGLRenderer::Clear(glm::vec4 colour)
	{
		glViewport(0, 0, g_CurrentWindow->GetWidth(), g_CurrentWindow->GetHeight());

		glEnable(GL_DEPTH_TEST);

		glClearColor(colour.r, colour.g, colour.b, colour.a);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}

	void OpenGLRenderer::Render()
	{
		MainRenderPass();
	}

	void OpenGLRenderer::MainRenderPass()
	{
		for (DrawCallData data : m_DrawQueue)
		{
			RenderMesh(data.mesh, data.shaderProgramme, data.transform);
		}
	}

	void OpenGLRenderer::RenderMesh(Ref<Mesh> mesh, Ref<ShaderProgramme> shaderProgramme, Transform transform)
	{
		shaderProgramme->Start();

		mesh->Bind();

		int width = g_CurrentWindow->GetWidth();
		int height = g_CurrentWindow->GetHeight();

		glm::mat4 modelMatrix = CreateModelMatrix(transform);
		glm::mat4 viewMatrix = CreateViewMatrix(*g_MainCamera);

		glm::mat4 projectionMatrix = CreateProjectionMatrix(*g_MainCamera, width, height);
		shaderProgramme->AddUniform("u_Model", UniformType::Mat4, &modelMatrix);
		shaderProgramme->AddUniform("u_View", UniformType::Mat4, &viewMatrix);
		shaderProgramme->AddUniform("u_Projection", UniformType::Mat4, &projectionMatrix);

		glDrawElements(GL_TRIANGLES, mesh->GetIndicesCount(), GL_UNSIGNED_INT, (void*)0);

		mesh->Unbind();

		shaderProgramme->Stop();
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

		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(0);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_EBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(uint32_t), indices.data(), GL_STATIC_DRAW);

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

	OpenGLShaderProgramme::OpenGLShaderProgramme(ShaderProgrammeCreateArgs shaderProgrammeCreateArgs)
	{
		std::string vertexSource = ReadFile(shaderProgrammeCreateArgs.openGLVertexShaderPath);
		std::string fragmentSource = ReadFile(shaderProgrammeCreateArgs.openGLFragmentShaderPath);

		KW_ASSERT("Shader source is empty", !(vertexSource.empty() || fragmentSource.empty()));

		uint32_t vertexShader = CompileShader(GL_VERTEX_SHADER, vertexSource);
		uint32_t fragmentShader = CompileShader(GL_FRAGMENT_SHADER, fragmentSource);

		m_ShaderProgramme = glCreateProgram();
		glAttachShader(m_ShaderProgramme, vertexShader);
		glAttachShader(m_ShaderProgramme, fragmentShader);

		glLinkProgram(m_ShaderProgramme);

		GLint linkStatus = 0;
		glGetProgramiv(m_ShaderProgramme, GL_LINK_STATUS, &linkStatus);
		if (linkStatus == GL_FALSE)
		{
			GLint maxLength = 0;
			glGetProgramiv(m_ShaderProgramme, GL_INFO_LOG_LENGTH, &maxLength);

			std::string errorLog = std::string(maxLength, ' ');
			glGetProgramInfoLog(m_ShaderProgramme, maxLength, &maxLength, &errorLog[0]);

			KW_LOG(errorLog);
			KW_ASSERT("Shader linking failed. ", false);

			glDeleteProgram(m_ShaderProgramme);
			glDeleteShader(vertexShader);
			glDeleteShader(fragmentShader);
		}

		glDetachShader(m_ShaderProgramme, vertexShader);
		glDetachShader(m_ShaderProgramme, fragmentShader);
		glDeleteShader(vertexShader);
		glDeleteShader(fragmentShader);
	}

	OpenGLShaderProgramme::~OpenGLShaderProgramme()
	{
		glDeleteProgram(m_ShaderProgramme);
	}

	void OpenGLShaderProgramme::Start()
	{
		glUseProgram(m_ShaderProgramme);
	}

	void OpenGLShaderProgramme::Stop()
	{
		glUseProgram(null);
	}


	void OpenGLShaderProgramme::AddUniform(std::string_view uniformName, UniformType uniformType, void* value)
	{
		GLint location = glGetUniformLocation(m_ShaderProgramme, uniformName.data());
		if (location == -1)
		{
			return;
		}

		switch (uniformType)
		{
			case UniformType::Float:
				glUniform1f(location, *static_cast<float*>(value));
				break;

			case UniformType::Vec2:
				glUniform2fv(location, 1, glm::value_ptr(*static_cast<glm::vec2*>(value)));
				break;

			case UniformType::Vec3:
				glUniform3fv(location, 1, glm::value_ptr(*static_cast<glm::vec3*>(value)));
				break;

			case UniformType::Vec4:
				glUniform4fv(location, 1, glm::value_ptr(*static_cast<glm::vec4*>(value)));
				break;

			case UniformType::Int:
				glUniform1i(location, *static_cast<int*>(value));
				break;

			case UniformType::UInt:
				glUniform1ui(location, *static_cast<unsigned int*>(value));
				break;

			case UniformType::Bool:
				glUniform1i(location, *static_cast<bool*>(value) ? 1 : 0);
				break;

			case UniformType::Mat2:
				glUniformMatrix2fv(location, 1, GL_FALSE, glm::value_ptr(*static_cast<glm::mat2*>(value)));
				break;

			case UniformType::Mat3:
				glUniformMatrix3fv(location, 1, GL_FALSE, glm::value_ptr(*static_cast<glm::mat3*>(value)));
				break;

			case UniformType::Mat4:
				glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(*static_cast<glm::mat4*>(value)));
				break;

			default:
				break;
		}
	}

	uint32_t OpenGLShaderProgramme::CompileShader(GLenum shaderType, const std::string& source)
	{
		uint32_t shader = glCreateShader(shaderType);
		const char* src = source.c_str();
		glShaderSource(shader, 1, &src, nullptr);
		glCompileShader(shader);

		int32_t compileStatus = 0;
		glGetShaderiv(shader, GL_COMPILE_STATUS, &compileStatus);
		if (compileStatus == GL_FALSE)
		{
			int32_t maxLength = 0;
			glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &maxLength);

			std::string errorLog = std::string(maxLength, ' ');
			glGetShaderInfoLog(shader, maxLength, &maxLength, &errorLog[0]);

			KW_LOG(errorLog);
			KW_ASSERT("Shader compilation failed", false);

			glDeleteShader(shader);

			return 0;
		}

		return shader;
	}

}
