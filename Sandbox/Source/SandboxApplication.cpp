#include "SandboxApplication.h"
#undef PERF_TEST

SandboxApplication::SandboxApplication() {}

SandboxApplication::~SandboxApplication() {}

bool SandboxApplication::Run()
{
	Kiwi::Window::Initialise("Sandbox", 1260, 720);
	
	Kiwi::Renderer::MasterRenderer masterRenderer;

	Kiwi::Transform cameraTransform = Kiwi::Transform();

#ifndef PERF_TEST
	cameraTransform.position = Kiwi::Vec3(0, 1, -20);
#else
	cameraTransform.position = Kiwi::Vec3(0, 1, -100);
#endif

	cameraTransform.rotation = Kiwi::Vec3(0, 0, 0);
	cameraTransform.scale = Kiwi::Vec3(1, 1, 1);

	Kiwi::g_MainCamera = &cameraTransform;
	
	Kiwi::SunLight sunLight = Kiwi::SunLight(Kiwi::Vec3(0, 10, -10), Kiwi::Colour(255, 255, 255, 255), 0.25f);

	Kiwi::g_SunLight = &sunLight;

	Kiwi::Renderer::ShaderManager* shaderManager = new Kiwi::Renderer::PBRShader();
	
	Kiwi::Image2D image = Kiwi::TextureHelpers::LoadImage("Assets/stallTexture.png");
	Kiwi::Mesh mesh = Kiwi::LoadMesh("Assets/stall.glb", &image, shaderManager);
	
	//mesh.material.metalness = 0.25;
	//mesh.material.roughness = 0.00f;

	Kiwi::Transform transform;
	transform.position = Kiwi::Vec3(0, 0, 0);
	transform.rotation = Kiwi::Vec3(0, 0, 0);
	transform.scale = Kiwi::Vec3(1, 1, 1);

#ifdef PERF_TEST
	std::vector<Kiwi::Transform> transforms;
	transforms.reserve(1000);

	const int AMOUNT = 8192;
	for (int x = 0; x < AMOUNT; x++)
	{
		Kiwi::Transform t;
		t.position = Kiwi::Vec3(Kiwi::Maths::Random(-40.0f, 40.0f), Kiwi::Maths::Random(-20.0f, 20.0f), Kiwi::Maths::Random(-40.0f, 40.0f));
		t.rotation = Kiwi::Vec3(0, 0, 0);
		t.scale = Kiwi::Vec3(0.25f, 0.25f, 0.25f);
		transforms.push_back(t);
	}
#endif

	Kiwi::Colour colour = Kiwi::Colour(15, 20, 25, 255);

	while (!Kiwi::Window::ShouldClose())
	{
		transform.rotation.y += 0.02f;

		masterRenderer.Clear(colour);

#ifndef PERF_TEST
		transform.rotation.y += 0.02f;
		masterRenderer.QueueMesh(&mesh, transform, shaderManager);
#else
		for (size_t i = 0; i < transforms.size(); ++i)
		{
			transforms[i].rotation.y += 0.01f;
			masterRenderer.QueueMesh(&mesh, transforms[i], &shaderManager);
		}
#endif

		masterRenderer.Render3D();

		masterRenderer.Present();
	}

	delete shaderManager;

	Kiwi::Window::Shutdown();

	return true;
}
