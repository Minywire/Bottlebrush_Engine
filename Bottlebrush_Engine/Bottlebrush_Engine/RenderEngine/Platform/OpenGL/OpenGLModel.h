//
// Created by niamh on 7/04/2024.
//

#ifndef BOTTLEBRUSH_ENGINE_OPENGLMODEL_H
#define BOTTLEBRUSH_ENGINE_OPENGLMODEL_H

#include "Model.h"
#include "OpenGLRenderer.h"
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

class OpenGLModel : public Model {
public:
    OpenGLModel(const std::filesystem::path &fileName);
    bool LoadModel(const std::filesystem::path& filePath) override;
    void Draw() override;
private:
    std::unique_ptr<OpenGLRenderer> InitMesh(const aiMesh* paiMesh);

    std::vector<std::unique_ptr<OpenGLRenderer>> mSubMeshes;
};


#endif //BOTTLEBRUSH_ENGINE_OPENGLMODEL_H
