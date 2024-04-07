//
// Created by niamh on 7/04/2024.
//

#include "OpenGLModel.h"

bool OpenGLModel::LoadModel(const std::string& filePath) {
    Assimp::Importer import;

    const aiScene* scene = import.ReadFile(filePath, aiProcess_Triangulate | aiProcess_JoinIdenticalVertices);

    if(!scene) {
        return false;
    }
    // NOTE This might be able to be made static when all is said and done.
    // If the scene exists, then return true, otherwise return false
    return true;
}

OpenGLModel::OpenGLModel(const std::string &fileName) {

}
