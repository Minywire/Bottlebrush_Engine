#include "OpenGLModel.h"
//
// Created by niamh on 7/04/2024.
//

#include "OpenGLModel.h"

#include <iostream>
#include <cassert>
#include <fstream>
#include <stdexcept>

bool OpenGLModel::LoadModel(const std::filesystem::path& modelPath, const std::filesystem::path &texturePath) {
    Assimp::Importer import;

    std::ifstream file(modelPath);

    if(file) {
        std::cout << modelPath << " opened successfully" << std::endl;
    } else {
        throw std::invalid_argument(modelPath.string() + " could not open");
    }

    file.close();

    const aiScene* scene = import.ReadFile(modelPath.string(), aiProcess_Triangulate | aiProcess_JoinIdenticalVertices);

    if(!scene) {
        return false;
    }

    for(unsigned int i = 0; i < scene->mNumMeshes; i++) {
        mSubMeshes.push_back(InitMesh(scene->mMeshes[i], texturePath));
    }

    // NOTE This might be able to be made static when all is said and done.
    // If the scene exists, then return true, otherwise return false

    // Set buffers

    return true;
}

OpenGLModel::OpenGLModel(const std::filesystem::path &modelPath, const std::filesystem::path &texturePath) {
    LoadModel(modelPath, texturePath);
}

void OpenGLModel::UnbindModel() {
  for (unsigned int i = 0; i < mSubMeshes.size(); i++) {
    mSubMeshes[i]->UnbindMesh();
  }
}
std::unique_ptr<OpenGLMesh> OpenGLModel::InitMesh(const aiMesh* paiMesh, const std::filesystem::path &texturePath) {
    std::vector<float> meshVerts;
    std::vector<unsigned int> meshInts;
    std::vector<float> meshTextures;

    const aiVector3D Zero3D(0.0f, 0.0f, 0.0f);

    // Populate vertex positions
    for(unsigned int i = 0; i < paiMesh->mNumVertices; i++) {
        const aiVector3D& pPos = paiMesh->mVertices[i];

        meshVerts.push_back(pPos.x);
        meshVerts.push_back(pPos.y);
        meshVerts.push_back(pPos.z);

        // Process TexCoords
        if(paiMesh->mTextureCoords[0]) {
            glm::vec2 vec;
            vec.x = paiMesh->mTextureCoords[0][i].x;
            vec.y = paiMesh->mTextureCoords[0][i].y;

            meshVerts.push_back(vec.x);
            meshVerts.push_back(vec.y);
        }
    }

    // Populate index buffer
    for(unsigned int i = 0; i < paiMesh->mNumFaces; i++) {
        const aiFace& Face = paiMesh->mFaces[i];
        assert(Face.mNumIndices == 3);
        meshInts.push_back(Face.mIndices[0]);
        meshInts.push_back(Face.mIndices[1]);
        meshInts.push_back(Face.mIndices[2]);
    }

    std::vector<unsigned int> layout;
    layout.push_back(5); // 3 elements for position, 2 elements for texture

    std::unique_ptr<OpenGLMesh> mesh = std::make_unique<OpenGLMesh>();
    mesh->CreateMesh(meshVerts, meshInts, texturePath, layout);

    return mesh;
}
