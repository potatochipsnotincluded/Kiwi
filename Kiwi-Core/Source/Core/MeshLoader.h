#pragma once
#include "Common.h"
#include "MasterRenderer.h"

#include "Debug.h"

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

namespace Kiwi {

	Ref<Mesh> LoadMesh(std::filesystem::path filePath);

}