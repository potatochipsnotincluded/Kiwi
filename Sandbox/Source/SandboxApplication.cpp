#include "SandboxApplication.h"

SandboxApplication::SandboxApplication() {}

SandboxApplication::~SandboxApplication() {}

bool SandboxApplication::Run()
{
	Kiwi::Window::Initialise("Sandbox", 1260, 720);
	
	Kiwi::mainCamera = new Kiwi::Transform();

	Kiwi::Colour colour = Kiwi::Colour(15, 20, 25, 255);

	while (!Kiwi::Window::ShouldClose())
	{
		Kiwi::Renderer::Clear(colour);

		Kiwi::Renderer::End3DRender();

		Kiwi::Renderer::Present();
	}

	delete Kiwi::mainCamera;
	Kiwi::Window::Shutdown();

	return true;
}
