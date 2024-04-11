//
// Created by niamh on 7/04/2024.
//

#ifndef BOTTLEBRUSH_ENGINE_MODEL_H
#define BOTTLEBRUSH_ENGINE_MODEL_H

#include <string>
#include <filesystem>
class Model {
public:
    virtual bool LoadModel(const std::filesystem::path& filePath) = 0;
    virtual void Draw() = 0;
};


#endif //BOTTLEBRUSH_ENGINE_MODEL_H
