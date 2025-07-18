#include "SandboxApplication.h"

SandboxApplication::SandboxApplication() :
	m_Window("Sandbox", 1260, 720), m_Renderer(Kiwi::CreateRenderer(Kiwi::RendererType::OpenGL)) {}

SandboxApplication::~SandboxApplication() {}

bool SandboxApplication::Run()
{
	Kiwi::ShaderProgrammeCreateArgs createArgs;
	createArgs.openGLFragmentShaderPath = "../Shaders/test_triangle_frag.glsl";
	createArgs.openGLVertexShaderPath = "../Shaders/test_triangle_vert.glsl";

	Ref<Kiwi::ShaderProgramme> shaderProgramme = Kiwi::CreateShaderProgramme(createArgs);
	Ref<Kiwi::Mesh> mesh = Kiwi::LoadMesh("Assets/stall.glb");

	Kiwi::Material material = Kiwi::Material(Kiwi::LoadTexture("Assets/stallTexture.png", true));
	
	Kiwi::Transform transform;
	transform.rotation.y = 0;

	Kiwi::g_MainCamera->transform.position.y = 1;
	Kiwi::g_MainCamera->transform.position.z = -20;

	while (!m_Window.ShouldClose())
	{
		transform.rotation.y += 0.1f;
		m_Window.FrameBegin();

		m_Renderer->Clear(glm::vec4(0.00f, 0.00f, 0.00f, 1.00f));

		m_Renderer->PushMesh(mesh, shaderProgramme, transform, material);

		m_Renderer->Render();

		m_Window.Present();
	}

	return true;
}
