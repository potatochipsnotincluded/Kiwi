#include "SandboxApplication.h"

SandboxApplication::SandboxApplication() {}

SandboxApplication::~SandboxApplication() {}

bool SandboxApplication::Run()
{
	Kiwi::Window::Init("Sandbox", 1260, 720);

	m_Renderer.Init();

	while (!Kiwi::Window::ShouldClose())
	{
		m_Renderer.Clear(glm::vec4(0.02f, 0.02f, 0.05f, 1.0f));

		m_Renderer.Present();

		Kiwi::Window::Update();
	}

	Kiwi::Window::Shutdown();

	return true;
}
