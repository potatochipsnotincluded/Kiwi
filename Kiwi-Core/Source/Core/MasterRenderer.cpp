#include "MasterRenderer.h"

#include "OpenGL/OpenGLRenderer.h"

namespace Kiwi {

	Ref<Kiwi::Renderer> CreateRenderer(RendererType rendererType)
	{
		g_RendererType = rendererType;

		if (rendererType == RendererType::OpenGL)
			return MakeRef<OpenGLRenderer>();
		else if (rendererType == RendererType::None)
			return nullptr;
		else
			return nullptr;
	}

	Ref<Mesh> CreateMesh(std::vector<float> vertices, std::vector<uint32_t> indices)
	{
		if (g_RendererType == RendererType::OpenGL)
			return MakeRef<OpenGLMesh>(vertices, indices);
		else if (g_RendererType == RendererType::None)
			return nullptr;
		else
			return nullptr;
	}

}