#include "Renderer.h"

namespace Kiwi {

	Camera UpdateCamera()
	{
		Camera camera = { 0 };
		camera.position = mainCamera->position;

		float yawRadians = mainCamera->rotation.y * DEG2RAD;

		Vector3 forward = {
			sinf(yawRadians),
			0.0f,
			cosf(yawRadians)
		};

		camera.target = Vector3Add(mainCamera->position, forward);

		camera.up = { 0.0f, 1.0f, 0.0f };

		camera.fovy = FOV;

		camera.projection = isPerspective ? CAMERA_PERSPECTIVE : CAMERA_ORTHOGRAPHIC;

		return camera;
	}

	void Renderer::Clear(Colour colour)
	{
		BeginDrawing();
		ClearBackground(colour);

		BeginMode3D(UpdateCamera());
	}

	void Renderer::End3DRender()
	{
		EndMode3D();
	}

	void Renderer::Present()
	{
		EndDrawing();
	}

}


