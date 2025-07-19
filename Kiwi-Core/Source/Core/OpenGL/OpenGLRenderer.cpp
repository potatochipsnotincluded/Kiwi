#include "OpenGLRenderer.h"

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

namespace Kiwi {

	OpenGLRenderer::OpenGLRenderer()
	{
		if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
			KW_ASSERT("Could not load OpenGL", false);

		IMGUI_CHECKVERSION();
		ImGui::CreateContext();
		ImGuiIO& io = ImGui::GetIO(); (void)io;
		io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
		io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls
		io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
		io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;

		ImGui::StyleColorsDark();
		
		ImGui_ImplGlfw_InitForOpenGL(g_CurrentWindow->GetGLFWWindow(), true);
		ImGui_ImplOpenGL3_Init("#version 460");
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

		m_DrawQueue.clear();
	}

	void OpenGLRenderer::ImGuiStartFrame()
	{
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();
	}

	void OpenGLRenderer::ImGuiEndFrame()
	{
		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

		ImGui::UpdatePlatformWindows();
		ImGui::RenderPlatformWindowsDefault();
		g_CurrentWindow->BecomeCurrent();
	}

	void OpenGLRenderer::MainRenderPass()
	{
		for (DrawCallData data : m_DrawQueue)
		{
			RenderMesh(data.mesh, data.shaderProgramme, data.transform, data.material);
		}
	}

	void OpenGLRenderer::RenderMesh(Ref<Mesh> mesh, Ref<ShaderProgramme> shaderProgramme, Transform transform, Material material)
	{
		shaderProgramme->Start();

		mesh->Bind();

		material.albedoMap->Bind();

		glm::vec3 sunPos = g_SunLight->sunPosition;
		glm::vec3 sunCol = g_SunLight->sunColour * g_SunLight->intensity;
		float sunAmb = g_SunLight->ambient;

		shaderProgramme->AddUniform("u_SunPosition", UniformType::Vec3, &sunPos);
		shaderProgramme->AddUniform("u_SunColour", UniformType::Vec3, &sunCol);
		shaderProgramme->AddUniform("u_Ambient", UniformType::Float, &sunAmb);

		int width = g_CurrentWindow->GetWidth();
		int height = g_CurrentWindow->GetHeight();

		glm::mat4 modelMatrix = CreateModelMatrix(transform);
		glm::mat4 viewMatrix = CreateViewMatrix(*g_MainCamera);

		glm::mat4 projectionMatrix = CreateProjectionMatrix(*g_MainCamera, width, height);
		shaderProgramme->AddUniform("u_Model", UniformType::Mat4, &modelMatrix);
		shaderProgramme->AddUniform("u_View", UniformType::Mat4, &viewMatrix);
		shaderProgramme->AddUniform("u_Projection", UniformType::Mat4, &projectionMatrix);

		float metallic = material.metallic;
		float roughness = material.roughness;

		shaderProgramme->AddUniform("u_Metallic", UniformType::Float, &metallic);
		shaderProgramme->AddUniform("u_Roughness", UniformType::Float, &roughness);

		int32_t textureIndex = 0;
		shaderProgramme->AddUniform("u_AlbedoMap", UniformType::Texture, &textureIndex);

		glDrawElements(GL_TRIANGLES, mesh->GetIndicesCount(), GL_UNSIGNED_INT, (void*)0);

		material.albedoMap->Unbind();

		mesh->Unbind();

		shaderProgramme->Stop();
	}

	OpenGLMesh::OpenGLMesh(std::vector<float> vertices, std::vector<float> texCoords, std::vector<float> normals, std::vector<uint32_t> indices)
	{
		m_IndicesCount = indices.size();

		glGenVertexArrays(1, &m_VAO);
		glGenBuffers(1, &m_VBO);
		glGenBuffers(1, &m_TBO);
		glGenBuffers(1, &m_NBO);
		glGenBuffers(1, &m_EBO);

		glBindVertexArray(m_VAO);

		glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
		glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), vertices.data(), GL_STATIC_DRAW);

		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(0);

		glBindBuffer(GL_ARRAY_BUFFER, m_TBO);
		glBufferData(GL_ARRAY_BUFFER, texCoords.size() * sizeof(float), texCoords.data(), GL_STATIC_DRAW);

		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(1);

		glBindBuffer(GL_ARRAY_BUFFER, m_NBO);
		glBufferData(GL_ARRAY_BUFFER, normals.size() * sizeof(float), normals.data(), GL_STATIC_DRAW);

		glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(2);

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

			KW_LOG("OpenGL error: {}", errorLog);
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

			case UniformType::Texture:
				glUniform1i(location, *static_cast<int32_t*>(value));
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

			KW_LOG("OpenGL error: {}", errorLog);
			KW_ASSERT("Shader compilation failed", false);

			glDeleteShader(shader);

			return 0;
		}

		return shader;
	}

	OpenGLTexture::OpenGLTexture(std::filesystem::path filePath, bool linear)
	{
		int width, height, channels;

		stbi_set_flip_vertically_on_load(true);
		unsigned char* data = stbi_load(filePath.string().c_str(), &width, &height, &channels, STBI_rgb_alpha);
		KW_ASSERT("Failed to load texture.", data);

		glGenTextures(1, &m_ID);
		glBindTexture(GL_TEXTURE_2D, m_ID);

		glTexImage2D(
			GL_TEXTURE_2D, 0, GL_RGBA8,
			width, height, 0,
			GL_RGBA, GL_UNSIGNED_BYTE, data
		);

		glGenerateMipmap(GL_TEXTURE_2D);

		if (!linear)
		{
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_NEAREST);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		}
		else
		{
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		}

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

		glBindTexture(GL_TEXTURE_2D, null);
		stbi_image_free(data);
	}

	OpenGLTexture::~OpenGLTexture() {}

	void OpenGLTexture::Bind()
	{
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, m_ID);
	}

	void OpenGLTexture::Unbind()
	{
		glBindTexture(GL_TEXTURE_2D, null);
	}

}
