#pragma once
#include <Core/Kiwi.h>

#include <Application/Application.h>

class SandboxApplication : public Kiwi::Application
{
public:
	SandboxApplication();

	virtual ~SandboxApplication() override;

	virtual bool Run() override;

private:
	Kiwi::Renderer m_Renderer;
};