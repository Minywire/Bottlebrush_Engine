//
// Created by niamh on 7/04/2024.
//

#ifndef BOTTLEBRUSH_ENGINE_MODEL_H
#define BOTTLEBRUSH_ENGINE_MODEL_H

#include "../BBAssetImporter/Mesh.h"

#include <string>

class Model {
public:
    Model() {};
    virtual bool LoadModel(const std::string& filePath) = 0;
};


#endif //BOTTLEBRUSH_ENGINE_MODEL_H
