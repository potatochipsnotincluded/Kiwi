#pragma once
#include <Core/Kiwi.h>

#include <Application/Application.h>

#include <imgui.h>

class SandboxApplication : public Kiwi::Application
{
public:
	SandboxApplication();

	virtual ~SandboxApplication() override;

	virtual bool Run() override;

private:
	Kiwi::Window m_Window;

	Ref<Kiwi::Renderer> m_Renderer;
};