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

		glfwMakeContextCurrent(m_Window);

		BecomeCurrent();
		
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

	bool Input::IsKeyPressed(uint32_t key)
	{
		return glfwGetKey(g_CurrentWindow->GetGLFWWindow(), key) == GLFW_PRESS;
	}

	bool Input::IsMouseButtonPressed(uint32_t button)
	{
		return glfwGetMouseButton(g_CurrentWindow->GetGLFWWindow(), button) == GLFW_PRESS;
	}

	glm::vec2 Input::GetMousePosition()
	{
		double x;
		double y;

		glfwGetCursorPos(g_CurrentWindow->GetGLFWWindow(), &x, &y);

		return glm::vec2(x, y);
	}


}

// References
// GLFW Documentation, Retrieved 2025, https://www.glfw.org/documentation.html
