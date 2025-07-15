#include "SandboxApplication.h"

SandboxApplication::SandboxApplication() :
	m_Window("Sandbox", 1260, 720), m_Renderer(Kiwi::CreateRenderer(Kiwi::RendererType::OpenGL)) {}

SandboxApplication::~SandboxApplication()
{
	delete m_Renderer;
}

bool SandboxApplication::Run()
{
	while (!m_Window.ShouldClose())
	{
		m_Renderer->Clear(glm::vec4(1.00f, 0.00f, 0.45f, 1.00f));

		m_Window.Present();
	}

	return true;
}
