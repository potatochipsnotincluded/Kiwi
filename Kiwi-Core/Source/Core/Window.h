#pragma once
#include "Common.h"

#include "Debug.h"

#include <glm/glm.hpp>

#include <glad/glad.h> // TODO: Make this renderer-dependent
#include <GLFW/glfw3.h>

namespace Kiwi {

	class Window
	{
	public:
		Window(std::string_view title, uint32_t width, uint32_t height);
		~Window();

	public:
		bool ShouldClose();

		void Present();

		void BecomeCurrent();

		GLFWwindow* GetGLFWWindow();

		uint32_t GetWidth();

		uint32_t GetHeight();

	private:
		GLFWwindow* m_Window = nullptr;
	};

	inline Window* g_CurrentWindow;

	namespace Input {

		bool IsKeyPressed(uint32_t key);

		bool IsMouseButtonPressed(uint32_t button);

		glm::vec2 GetMousePosition();

	}

}