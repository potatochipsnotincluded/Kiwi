#include "SandboxApplication.h"

SandboxApplication::SandboxApplication() {}

SandboxApplication::~SandboxApplication() {}

bool SandboxApplication::Run()
{
	Kiwi::Window::Initialise("Sandbox", 1260, 720);
	
	Kiwi::Transform cameraTransform = Kiwi::Transform();
	cameraTransform.position = Kiwi::Vec3(0, 1, -20);
	cameraTransform.rotation = Kiwi::Vec3(0, 0, 0);
	cameraTransform.scale = Kiwi::Vec3(1, 1, 1);

	Kiwi::g_MainCamera = &cameraTransform;
	
	Kiwi::SunLight sunLight = Kiwi::SunLight(Kiwi::Vec3(0, 10, -10), Kiwi::Colour(255, 255, 255, 255), 0.45f);

	Kiwi::g_SunLight = &sunLight;

	Kiwi::Renderer::ShaderManager shaderManager;

	Kiwi::Mesh mesh = Kiwi::LoadMesh("Assets/stall.glb", Kiwi::TextureHelpers::LoadImage("Assets/stallTexture.png"), &shaderManager);
	
	Kiwi::Transform transform;
	transform.position = Kiwi::Vec3(0, 0, 0);
	transform.rotation = Kiwi::Vec3(0, 0, 0);
	transform.scale = Kiwi::Vec3(1, 1, 1);

	Kiwi::Colour colour = Kiwi::Colour(15, 20, 25, 255);

	while (!Kiwi::Window::ShouldClose())
	{
		transform.rotation.y += 0.01f;

		Kiwi::Renderer::Clear(colour);

		Kiwi::Renderer::DrawMesh(mesh, transform, &shaderManager);

		Kiwi::Renderer::End3DRender();

		Kiwi::Renderer::Present();
	}

	Kiwi::Window::Shutdown();

	return true;
}
