#include "Window.h"

namespace Kiwi {

	void Window::Initialise(std::string_view title, uint32_t width, uint32_t height)
	{
		SetConfigFlags(FLAG_WINDOW_RESIZABLE);

		InitWindow(width, height, title.data());
	}

	bool Window::ShouldClose()
	{
		return WindowShouldClose();
	}

	void Window::Shutdown()
	{
		CloseWindow();
	}

	bool Input::GetKeyDown(uint32_t key)
	{
		return IsKeyDown(key);
	}

	bool Input::GetMouseButtonDown(uint32_t button)
	{
		return IsMouseButtonDown(button);
	}

}


