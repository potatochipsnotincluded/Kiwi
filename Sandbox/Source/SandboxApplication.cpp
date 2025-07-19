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

	float metallic = 0.75f;
	float roughness = 0.3f;

	//float metallic = 0.0f;
	//float roughness = 1.0f;

	Kiwi::Material material = Kiwi::Material(Kiwi::LoadTexture("Assets/stallTexture.png", true), metallic, roughness);
	
	Kiwi::Transform transform;
	transform.rotation.y = 180;

	Kiwi::g_MainCamera->transform.position.y = 1;
	Kiwi::g_MainCamera->transform.position.z = -20;

	float rotateSpeed = 96;
	float moveSpeed = 16;

	while (!m_Window.ShouldClose())
	{
		m_Window.FrameBegin();

		//transform.rotation.y += 64.0f*m_Window.GetDeltaTime();
		
		if (Kiwi::Input::IsKeyPressed(KIWI_KEY_A))
			Kiwi::g_MainCamera->transform.rotation.y += rotateSpeed * m_Window.GetDeltaTime();
		if (Kiwi::Input::IsKeyPressed(KIWI_KEY_D))
			Kiwi::g_MainCamera->transform.rotation.y -= rotateSpeed * m_Window.GetDeltaTime();

		glm::vec3 forward = Kiwi::GetForwardVector(Kiwi::g_MainCamera->transform);

		if (Kiwi::Input::IsKeyPressed(KIWI_KEY_W))
			Kiwi::g_MainCamera->transform.position += (forward * moveSpeed) * (float)m_Window.GetDeltaTime();
		if (Kiwi::Input::IsKeyPressed(KIWI_KEY_S))
			Kiwi::g_MainCamera->transform.position -= (forward * moveSpeed) * (float)m_Window.GetDeltaTime();

		if (Kiwi::Input::IsKeyPressed(KIWI_KEY_Q))
			Kiwi::g_MainCamera->transform.position.y += moveSpeed * m_Window.GetDeltaTime();
		if (Kiwi::Input::IsKeyPressed(KIWI_KEY_E))
			Kiwi::g_MainCamera->transform.position.y -= moveSpeed * m_Window.GetDeltaTime();

		if (Kiwi::Input::IsKeyPressed(KIWI_KEY_SPACE))
			KW_LOG("Ms/f {}", m_Window.GetDeltaTime() * 1000);

		m_Renderer->Clear(glm::vec4(0.00f, 0.00f, 0.00f, 1.00f));

		m_Renderer->PushMesh(mesh, shaderProgramme, transform, material);

		m_Renderer->Render();

		m_Window.Present();
	}

	return true;
}
