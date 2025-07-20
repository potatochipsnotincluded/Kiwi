#pragma once
#include "../Common.h"

#include "../MasterRenderer.h"

#include "../Window.h"

#include "../FileUtils.h"

#include "../Debug.h"

#include <glad/glad.h>

#include <glm/gtc/type_ptr.hpp>

#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

namespace Kiwi {

	class OpenGLMesh : public Mesh
	{
	public:
		OpenGLMesh(std::vector<float> vertices, std::vector<float> texCoords, std::vector<float> normals, std::vector<uint32_t> indices);

		virtual ~OpenGLMesh() override;

		virtual void Bind() override;

		virtual void Unbind() override;

		virtual int32_t GetIndicesCount() override;

	private:
		uint32_t m_VBO = null;
		uint32_t m_EBO = null;
		uint32_t m_VAO = null;

		// Texture Coordinates VBO
		uint32_t m_TBO = null;

		// Normals VBO
		uint32_t m_NBO = null;

		int32_t m_IndicesCount = null;
	};

	class OpenGLShaderProgramme : public ShaderProgramme
	{
	public:
		OpenGLShaderProgramme(ShaderProgrammeCreateArgs shaderProgrammeCreateArgs);

		virtual ~OpenGLShaderProgramme() override;

		virtual void Start() override;
		
		virtual void Stop() override;

		virtual void AddUniform(std::string_view uniformName, UniformType uniformType, void* value) override;

	private:
		uint32_t CompileShader(GLenum shaderType, const std::string& source);

	private:
		uint32_t m_ShaderProgramme = null;
	};

	class OpenGLTexture : public Texture
	{
	public:
		OpenGLTexture(std::filesystem::path filePath, bool linear);

		virtual ~OpenGLTexture() override;

		virtual void Bind() override;

		virtual void Unbind() override;
	private:
		uint32_t m_ID = null;
	};

	class OpenGLRenderer : public Renderer
	{
	public:
		OpenGLRenderer();

		virtual ~OpenGLRenderer() override;

		virtual void Clear(glm::vec4 colour) override;

		virtual void Render() override;

		virtual void ImGuiStartFrame() override;
		virtual void ImGuiEndFrame() override;

		virtual void ImGuiShutdown() override;

		virtual void DrawImGuiViewport() override;

		virtual ImTextureID GetFramebufferImGuiTexture() override;

		virtual uint32_t GetFramebufferWidth() override;
		virtual uint32_t GetFramebufferHeight() override;

		virtual void SetFramebufferWidth(uint32_t width) override;
		virtual void SetFramebufferHeight(uint32_t height) override;

		virtual void UpdateFramebufferSize() override;

	private:
		void MainRenderPass();

		void RenderMesh(Ref<Mesh> mesh, Ref<ShaderProgramme> shaderProgramme, Transform transform, Material material);
	
	private:
		uint32_t m_Framebuffer = null;
		uint32_t m_FramebufferTexture = null;
		uint32_t m_FramebufferDepth = null;

		uint32_t m_FrameWidth = 640;
		uint32_t m_FrameHeight = 480;

		bool m_Resized = false;
	};

}