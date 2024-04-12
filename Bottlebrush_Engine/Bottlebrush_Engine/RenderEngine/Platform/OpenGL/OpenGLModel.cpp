//
// Created by niamh on 7/04/2024.
//

#include "OpenGLModel.h"

#include <iostream>
#include <cassert>
#include <fstream>
#include <stdexcept>

bool OpenGLModel::LoadModel(const std::filesystem::path& filePath) {
    Assimp::Importer import;

    std::ifstream file(filePath);

    if(file) {
        std::cout << filePath << " opened successfully" << std::endl;
    } else {
        throw std::invalid_argument(filePath.string() + " could not open");
    }

    file.close();

    const aiScene* scene = import.ReadFile(filePath.string(), aiProcess_Triangulate | aiProcess_JoinIdenticalVertices);

    if(!scene) {
        return false;
    }

    for(unsigned int i = 0; i < scene->mNumMeshes; i++) {
        mSubMeshes.push_back(InitMesh(scene->mMeshes[i]));
    }

    std::cout << "The model has " << mSubMeshes.size() << " submeshes" << std::endl;
    // NOTE This might be able to be made static when all is said and done.
    // If the scene exists, then return true, otherwise return false

    // Set buffers

    return true;
}

OpenGLModel::OpenGLModel(const std::filesystem::path &fileName) {
    LoadModel(fileName);
}

std::unique_ptr<Mesh> OpenGLModel::InitMesh(const aiMesh *paiMesh) {
    std::vector<float> meshVerts;
    std::vector<unsigned int> meshInts;

    const aiVector3D Zero3D(0.0f, 0.0f, 0.0f);

    // Populate vertex positions
    for(unsigned int i = 0; i < paiMesh->mNumVertices; i++) {
        const aiVector3D& pPos = paiMesh->mVertices[i];

        meshVerts.push_back(pPos.x);
        meshVerts.push_back(pPos.y);
        meshVerts.push_back(pPos.z);
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
    layout.push_back(3);

    std::unique_ptr<Mesh> mesh = std::make_unique<OpenGLMesh>();
    mesh->CreateMesh(meshVerts, 3, meshInts, layout);

    return mesh;
}