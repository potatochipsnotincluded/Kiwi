#include "SandboxApplication.h"

SandboxApplication::SandboxApplication() : m_Window("Sandbox", 1260, 720) {}

SandboxApplication::~SandboxApplication() {}

bool SandboxApplication::Run()
{
	while (!m_Window.ShouldClose())
	{
		m_Window.Present();
	}

	return true;
}
