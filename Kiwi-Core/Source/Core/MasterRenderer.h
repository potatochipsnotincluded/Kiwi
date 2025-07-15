#pragma once
#include "Common.h"

#include <glm/glm.hpp>

namespace Kiwi {

	class OpenGLRenderer;

	enum class RendererType
	{
		OpenGL,
		None
	};

	class Renderer
	{
	public:
		virtual ~Renderer() {};

		virtual void Clear(glm::vec4 colour) = 0;
	};

	Renderer* CreateRenderer(RendererType rendererType);

}