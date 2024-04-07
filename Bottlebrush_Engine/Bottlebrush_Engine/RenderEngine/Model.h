//
// Created by niamh on 7/04/2024.
//

#ifndef BOTTLEBRUSH_ENGINE_MODEL_H
#define BOTTLEBRUSH_ENGINE_MODEL_H

#include "../BBAssetImporter/Mesh.h"

#include <string>

class Model {
virtual void LoadModel(std::string fileName) = 0;
};


#endif //BOTTLEBRUSH_ENGINE_MODEL_H
