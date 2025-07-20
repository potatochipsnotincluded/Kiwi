#pragma once
#include "Common.h"

#include "Debug.h"

#include <glm/glm.hpp>

#include <glad/glad.h> // TODO: Make this renderer-dependent
#include <GLFW/glfw3.h>

#include <imgui.h>

namespace Kiwi {

	class Window
	{
	public:
		Window(std::string_view title, uint32_t width, uint32_t height);
		~Window();

	public:
		bool ShouldClose();

		void FrameBegin();

		void Present();

		void BecomeCurrent();

		GLFWwindow* GetGLFWWindow();

		uint32_t GetWidth();

		uint32_t GetHeight();

		double GetDeltaTime();

	private:
		GLFWwindow* m_Window = nullptr;

		double m_Delta = 0;
		double m_StartTime = 0;
		double m_EndTime = 0;
	};

	inline Window* g_CurrentWindow;

	namespace Input {

		bool GetKeyDown(ImGuiKey key);

		bool GetKeyPressed(ImGuiKey key);

		bool GetMouseButtonPressed(ImGuiMouseButton button);

		glm::vec2 GetMousePosition();

		inline glm::vec2 g_MousePosition;

		inline bool g_Focused = false;

	}

}
