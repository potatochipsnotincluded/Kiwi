#include "MeshLoader.h"

namespace Kiwi {

	Ref<Mesh> LoadMesh(std::filesystem::path filePath)
	{
        std::vector<float> positions;
        std::vector<uint32_t> indices;
        std::vector<float> texcoords;
        std::vector<float> normals;

        Assimp::Importer importer;

        const aiScene* scene = importer.ReadFile(filePath.string().c_str(),
            aiProcess_Triangulate |
            aiProcess_JoinIdenticalVertices |
            aiProcess_GenSmoothNormals |
            aiProcess_CalcTangentSpace |
            aiProcess_ImproveCacheLocality);

        KW_ASSERT("Mesh failed to load", scene && scene->HasMeshes());

        uint32_t indexOffset = 0;

        for (unsigned int m = 0; m < scene->mNumMeshes; ++m)
        {
            const aiMesh* mesh = scene->mMeshes[m];

            for (unsigned int i = 0; i < mesh->mNumVertices; ++i)
            {
                const aiVector3D& pos = mesh->mVertices[i];
                positions.push_back(pos.x);
                positions.push_back(pos.y);
                positions.push_back(pos.z);

                if (mesh->HasNormals())
                {
                    const aiVector3D& n = mesh->mNormals[i];
                    normals.push_back(n.x);
                    normals.push_back(n.y);
                    normals.push_back(n.z);
                }
                else
                {
                    normals.insert(normals.end(), { 0.0f, 0.0f, 1.0f });
                }

                if (mesh->HasTextureCoords(0))
                {
                    const aiVector3D& uv = mesh->mTextureCoords[0][i];
                    texcoords.push_back(uv.x);
                    texcoords.push_back(uv.y);
                }
                else
                {
                    texcoords.insert(texcoords.end(), { 0.0f, 0.0f });
                }
            }

            for (unsigned int f = 0; f < mesh->mNumFaces; ++f)
            {
                const aiFace& face = mesh->mFaces[f];
                if (face.mNumIndices != 3)
                    continue;

                for (unsigned int j = 0; j < 3; ++j)
                {
                    indices.push_back(indexOffset + face.mIndices[j]);
                }
            }

            indexOffset += mesh->mNumVertices;
        }

        return CreateMesh(positions, texcoords, normals, indices);
    }

}
