#include "Window.h"

namespace Kiwi {

	Window::Window(std::string_view title, uint32_t width, uint32_t height)
	{
		if (!glfwInit())
			KW_ASSERT("Could not initialise GLFW", false);

		m_Window = glfwCreateWindow(width, height, title.data(), NULL, NULL);

		if (!m_Window)
		{
			glfwTerminate();
			KW_ASSERT("Could not create GLFW window", false);
		}

		BecomeCurrent();

		glfwSwapInterval(0);
		
		// (GLFW Documentation, 2025)
	}

	Window::~Window()
	{
		glfwTerminate();
	}

	bool Window::ShouldClose()
	{
		return glfwWindowShouldClose(m_Window);
	}

	void Window::FrameBegin()
	{
		m_StartTime = glfwGetTime();
	}

	void Window::Present()
	{
		glfwSwapBuffers(m_Window);
		glfwPollEvents();

		m_EndTime = glfwGetTime();

		m_Delta = m_EndTime - m_StartTime;

		// (GLFW Documentation, 2025)
	}

	void Window::BecomeCurrent()
	{
		glfwMakeContextCurrent(m_Window);

		g_CurrentWindow = this;
	}

	GLFWwindow* Window::GetGLFWWindow()
	{
		return m_Window;
	}

	uint32_t Window::GetWidth()
	{
		int width;
		glfwGetWindowSize(m_Window, &width, NULL);

		return width;
	}

	uint32_t Window::GetHeight()
	{
		int height;
		glfwGetWindowSize(m_Window, NULL, &height);

		return height;
	}

	double Window::GetDeltaTime()
	{
		return m_Delta;
	}

	namespace Input {

		bool GetKeyDown(ImGuiKey key)
		{
			if (!g_Focused)
				return false;
			return ImGui::IsKeyDown(key);
		}

		bool GetKeyPressed(ImGuiKey key)
		{
			if (!g_Focused)
				return false;
			return ImGui::IsKeyPressed(key);
		}

		bool GetMouseButtonPressed(ImGuiMouseButton button)
		{
			if (!g_Focused)
				return false;
			return ImGui::IsMouseClicked(button);
		}

		glm::vec2 Input::GetMousePosition()
		{
			return g_MousePosition;
		}

	}

}

// References
// GLFW Documentation, Retrieved 2025, https://www.glfw.org/documentation.html
