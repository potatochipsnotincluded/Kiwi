#pragma once
#include "../Common.h"

#include "../Maths.h"

#include <raylib.h>
#include <raymath.h>

namespace Kiwi {

	struct SunLight
	{
		Vec3 position;
		Colour colour;
	};

	inline Transform* mainCamera;
	inline float FOV = 45;
	inline bool isPerspective;

	Camera UpdateCamera();

	namespace Renderer {

		void Clear(Colour colour);

		void End3DRender();

		void Present();

	}

}