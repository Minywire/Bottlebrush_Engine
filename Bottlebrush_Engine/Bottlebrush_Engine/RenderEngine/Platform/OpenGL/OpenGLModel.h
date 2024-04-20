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
    /// @author Niamh
    /// @brief constructor that loads the model and init it
    /// @param filePath is the object
    /// @param texturePath is the image to use as a texture
    OpenGLModel(const std::filesystem::path &modelPath, const std::filesystem::path& texturePath);

    /// @author Niamh
    /// @brief loads the model using assimp and init it
    /// @param filePath is the object
    /// @param texturePath is the image to use as a texture
    bool LoadModel(const std::filesystem::path& modelPath, const std::filesystem::path &texturePath) override;

    inline std::vector<std::unique_ptr<Mesh>>& GetSubMeshes() override { return mSubMeshes; }

    /// @author Alan
    /// @brief unbinds the model from openGL storage
    void UnbindModel() override;

private:
    /// @author Niamh
    /// @brief inits a loaded mesh into the vector of submeshes
    /// @param paiMesh is the info from the obj file, containing vertex data
    /// @param texturePath is the image used to texture the mesh
    /// @param textureSlot is used if we want to use multiple textures
    std::unique_ptr<OpenGLMesh> InitMesh(const aiMesh* paiMesh, const std::filesystem::path &texturePath, int textureSlot);

    std::vector<std::unique_ptr<Mesh>> mSubMeshes;

//    OpenGLTexture loadMaterialTextures(aiMaterial* material, aiTextureType textureType, std::string typeName);
};


#endif //BOTTLEBRUSH_ENGINE_OPENGLMODEL_H
