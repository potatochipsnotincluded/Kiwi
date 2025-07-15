#include "SandboxApplication.h"

SandboxApplication::SandboxApplication() :
	m_Window("Sandbox", 1260, 720), m_Renderer(Kiwi::CreateRenderer(Kiwi::RendererType::OpenGL)) {}

SandboxApplication::~SandboxApplication() {}

bool SandboxApplication::Run()
{
	std::vector<float> vertices =
	{
		0.0f,  0.5f, 0.0f,
	   -0.5f, -0.5f, 0.0f,
		0.5f, -0.5f, 0.0f
	};

	std::vector<uint32_t> indices =
	{
		0, 1, 2
	};

	Ref<Kiwi::Mesh> mesh = Kiwi::CreateMesh(vertices, indices);

	while (!m_Window.ShouldClose())
	{
		m_Renderer->Clear(glm::vec4(1.00f, 0.00f, 0.45f, 1.00f));

		m_Renderer->RenderMesh(mesh);

		m_Window.Present();
	}

	return true;
}
