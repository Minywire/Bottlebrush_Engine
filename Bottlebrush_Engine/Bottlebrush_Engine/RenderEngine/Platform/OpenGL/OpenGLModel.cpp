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

    const aiScene* scene = import.ReadFile(modelPath.string(), aiProcess_Triangulate | aiProcess_JoinIdenticalVertices | aiProcess_GenSmoothNormals);

    if(!scene) {
        return false;
    }

    for(unsigned int i = 0; i < scene->mNumMeshes; i++) {
        mSubMeshes.push_back(InitMesh(scene->mMeshes[i], texturePath, 0));
    }

    // NOTE This might be able to be made static when all is said and done.
    // If the scene exists, then return true, otherwise return false

    return true;
}

OpenGLModel::OpenGLModel(const std::filesystem::path &modelPath, const std::filesystem::path &texturePath) {
    modelDirectory = modelPath.parent_path();
    LoadModel(modelPath, texturePath);
}

void OpenGLModel::UnbindModel() {
  for (unsigned int i = 0; i < mSubMeshes.size(); i++) {
    mSubMeshes[i]->UnbindMesh();
  }
}
std::unique_ptr<OpenGLMesh> OpenGLModel::InitMesh(const aiMesh* paiMesh, const std::filesystem::path &texturePath, int textureSlot) {
    std::vector<float> meshVerts;
    std::vector<unsigned int> meshInts;

    const aiVector3D Zero3D(0.0f, 0.0f, 0.0f);

    // Populate vertex positions
    for(unsigned int i = 0; i < paiMesh->mNumVertices; i++) {
        const aiVector3D& pPos = paiMesh->mVertices[i];

        meshVerts.push_back(pPos.x);
        meshVerts.push_back(pPos.y);
        meshVerts.push_back(pPos.z);

        // Process normal coordinates
        if(paiMesh->mNormals) {
            const aiVector3D& pNormals = paiMesh->mNormals[i];

            meshVerts.push_back(pNormals.x);
            meshVerts.push_back(pNormals.y);
            meshVerts.push_back(pNormals.z);
        }

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

    if(paiMesh->mMaterialIndex >= 0) {

    }

    std::vector<unsigned int> layout;
    layout.push_back(3); // 3 elements for position
    layout.push_back(3); // 3 elements for normals
    layout.push_back(2); // 2 elements for the texture
    std::unique_ptr<OpenGLMesh> mesh = std::make_unique<OpenGLMesh>(
        meshVerts, meshInts, texturePath, textureSlot, layout);

    return mesh;
}
