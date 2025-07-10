#include "SandboxApplication.h"

SandboxApplication::SandboxApplication() {}

SandboxApplication::~SandboxApplication() {}

bool SandboxApplication::Run()
{
	Kiwi::Window::Initialise("Sandbox", 1260, 720);

	while (!Kiwi::Window::ShouldClose())
	{
		
	}

	Kiwi::Window::Shutdown();
	return true;
}
