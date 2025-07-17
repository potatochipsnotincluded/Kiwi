#include "SandboxApplication.h"
#undef PERF_TEST

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

	Kiwi::ShaderProgrammeCreateArgs createArgs;
	createArgs.openGLFragmentShaderPath = "../Shaders/test_triangle_frag.glsl";
	createArgs.openGLVertexShaderPath = "../Shaders/test_triangle_vert.glsl";

	Ref<Kiwi::ShaderProgramme> shaderProgramme = Kiwi::CreateShaderProgramme(createArgs);
	Ref<Kiwi::Mesh> mesh = Kiwi::CreateMesh(vertices, indices);
	
	Kiwi::Transform transform;

#ifdef PERF_TEST
	std::vector<Kiwi::Transform> triangles;
	triangles.push_back(transform);

	float time = 0;
#endif

	while (!m_Window.ShouldClose())
	{
		m_Window.FrameBegin();

#ifdef PERF_TEST
		time += m_Window.GetDeltaTime();

		if (time > 0.125f)
		{
			time = 0;

			Kiwi::Transform newTransform;
			newTransform.position = glm::vec3(Kiwi::RandomFloat(-5, 5), Kiwi::RandomFloat(-5, 5), Kiwi::RandomFloat(-5, 5));
			newTransform.rotation = glm::vec3(Kiwi::RandomFloat(0, 360), Kiwi::RandomFloat(0, 360), Kiwi::RandomFloat(0, 360));
			triangles.push_back(newTransform);
		}
#endif
		m_Renderer->Clear(glm::vec4(1.00f, 0.00f, 0.45f, 1.00f));
#ifndef PERF_TEST
		m_Renderer->PushMesh(mesh, shaderProgramme, transform);
#else
		for (int i = 0; i < triangles.size(); i++)
		{
			m_Renderer->PushMesh(mesh, shaderProgramme, triangles[i]);
		}
#endif
		m_Renderer->Render();

		m_Window.Present();
	}

	return true;
}
