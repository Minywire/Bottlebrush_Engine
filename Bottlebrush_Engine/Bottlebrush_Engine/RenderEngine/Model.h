//
// Created by niamh on 7/04/2024.
//

#ifndef BOTTLEBRUSH_ENGINE_MODEL_H
#define BOTTLEBRUSH_ENGINE_MODEL_H

#include <string>
#include <memory>

#include "Mesh.h"

class Model {
public:
    virtual bool LoadModel(const std::string& filePath) = 0;
    //virtual void Draw() = 0;

    virtual inline std::vector<std::unique_ptr<Mesh>>& GetSubMeshes() = 0;
};


#endif //BOTTLEBRUSH_ENGINE_MODEL_H
