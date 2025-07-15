#include "SandboxApplication.h"

#include <Application/Application.h>

Ref<Kiwi::Application> CreateApplication()
{
	return Ref<Kiwi::Application>(new SandboxApplication());
}

#include <Application/EntryPoint.h>