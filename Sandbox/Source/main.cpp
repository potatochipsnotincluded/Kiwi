#include "SandboxApplication.h"

#include <Application/Application.h>

Kiwi::Application* CreateApplication()
{
	return new SandboxApplication();
}

#include <Application/EntryPoint.h>