#include "MasterRenderer.h"

#include "OpenGL/OpenGLRenderer.h"

namespace Kiwi {

	Renderer* CreateRenderer(RendererType rendererType)
	{
		if (rendererType == RendererType::OpenGL)
			return new OpenGLRenderer();
		else if (rendererType == RendererType::None)
			return nullptr;
		else
			return nullptr;
	}

}