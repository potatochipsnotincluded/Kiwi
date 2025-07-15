#include "SandboxApplication.h"

#include <Application/Application.h>

Ref<Kiwi::Application> CreateApplication()
{
	return MakeRef<SandboxApplication>();
}

#include <Application/EntryPoint.h>