//
// Created by niamh on 7/04/2024.
//

#ifndef BOTTLEBRUSH_ENGINE_OPENGLMODEL_H
#define BOTTLEBRUSH_ENGINE_OPENGLMODEL_H

#include "Model.h"

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

class OpenGLModel : public Model {
public:
    OpenGLModel(const std::string &fileName);
    bool LoadModel(const std::string& filePath) override;
private:
    std::vector<Mesh> mSubMeshes;
    OpenGLVertexArray VAO;
};


#endif //BOTTLEBRUSH_ENGINE_OPENGLMODEL_H
