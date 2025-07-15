#include "MasterRenderer.h"

#include "OpenGL/OpenGLRenderer.h"

namespace Kiwi {

	Ref<Kiwi::Renderer> CreateRenderer(RendererType rendererType)
	{
		if (rendererType == RendererType::OpenGL)
			return MakeRef<Kiwi::OpenGLRenderer>();
		else if (rendererType == RendererType::None)
			return nullptr;
		else
			return nullptr;
	}

}