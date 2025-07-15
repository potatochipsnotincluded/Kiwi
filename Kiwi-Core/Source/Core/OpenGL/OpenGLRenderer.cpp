#include "OpenGLRenderer.h"

namespace Kiwi {

	OpenGLRenderer::OpenGLRenderer()
	{
		if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
			KW_ASSERT(false);
	}

	OpenGLRenderer::~OpenGLRenderer() {}

	void OpenGLRenderer::Clear(glm::vec4 colour)
	{
		glViewport(0, 0, g_CurrentWindow->GetWidth(), g_CurrentWindow->GetHeight());

		glClearColor(colour.r, colour.g, colour.b, colour.a);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}

}
