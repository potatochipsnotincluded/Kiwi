#pragma once
#include "../Common.h"

#include "../Maths.h"

#include <raylib.h>
#include <raymath.h>

namespace Kiwi {

	struct SunLight
	{
		Vec3 position;
		Colour colour;

		float intensity;
	};

	struct Image2D
	{
		Texture2D raylibTexture;
		std::filesystem::path filePath;
	};

	struct Material
	{
		float roughness = 1.0f;
		float metalness = 0.0f;
		
		Colour diffuseColour;

		Image2D texture;
	};

	struct Mesh
	{
		Model raylibModel;

		Material material;
	};

	inline Transform* g_MainCamera;
	inline float g_FOV = 45;
	inline bool g_IsPerspective = true;

	inline SunLight* g_SunLight;

	inline float g_Ambient = 0.1f;

	Camera UpdateCamera();
	
	namespace TextureHelpers {

		Image2D LoadImage(std::filesystem::path filePath);

	}

	namespace Renderer {

		class ShaderManager
		{
		public:
			ShaderManager();
			~ShaderManager();

			void SetShaderParams(Material material);

			Shader GetShader();
			
		private:
			Shader m_Shader;
		};

		void Clear(Colour colour);

		void DrawMesh(Mesh& mesh, Transform transform, ShaderManager* shaderManager);

		void End3DRender();

		void Present();

	}

	Mesh LoadMesh(std::filesystem::path filePath, Image2D texture, Renderer::ShaderManager* shaderManager);

}