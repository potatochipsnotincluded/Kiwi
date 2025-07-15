#pragma once
#include "../Common.h"

#include "../MasterRenderer.h"

#include "../Window.h"

#include <glad/glad.h>

namespace Kiwi {

	class OpenGLRenderer : public Renderer
	{
	public:
		OpenGLRenderer();

		virtual ~OpenGLRenderer() override;

		virtual void Clear(glm::vec4 colour) override;
	};

}