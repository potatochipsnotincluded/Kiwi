#pragma once
#include "Common.h"

#include <raylib.h>

namespace Kiwi {

	namespace Window {

		void Initialise(std::string_view title, uint32_t width, uint32_t height);

		bool ShouldClose();

		void Shutdown();

	}

	namespace Input {

		bool GetKeyDown(uint32_t key);

		bool GetMouseButtonDown(uint32_t button);

		// TODO: Add GetMousePosition once we have a custom Vector2 class.

	}

}