//
// Created by niamh, alan on 7/04/2024.
//

#ifndef BOTTLEBRUSH_ENGINE_OPENGLMODEL_H
#define BOTTLEBRUSH_ENGINE_OPENGLMODEL_H

#include "Model.h"
#include "OpenGLMesh.h"

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <glm/glm.hpp>

class OpenGLModel : public Model {
public:
    OpenGLModel(const std::filesystem::path &modelPath, const std::filesystem::path& texturePath);
    bool LoadModel(const std::filesystem::path& modelPath, const std::filesystem::path &texturePath) override;

    inline std::vector<std::unique_ptr<Mesh>>& GetSubMeshes() override { return mSubMeshes; }

    void UnbindModel() override;

private:
    std::unique_ptr<OpenGLMesh> InitMesh(const aiMesh* paiMesh, const std::filesystem::path &texturePath);

    std::vector<std::unique_ptr<Mesh>> mSubMeshes;

//    OpenGLTexture loadMaterialTextures(aiMaterial* material, aiTextureType textureType, std::string typeName);
};


#endif //BOTTLEBRUSH_ENGINE_OPENGLMODEL_H
