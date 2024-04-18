//
// Created by Marco on 17/04/24.
//

#include "BBResourceManager.hpp"

void BBResourceManager::generateModelFromComponent(const ModelComponent & modelComp)
{
    GraphicsFactory<GraphicsAPI::OpenGL>::CreateModel(modelComp.model_path);
    //sceneModels.emplace(std::pair<std::string, std::unique_ptr<Model>>(modelComp.model_path, GraphicsFactory<GraphicsAPI::OpenGL>::CreateModel(modelComp.model_path)));
}

const std::unordered_map<std::string, std::unique_ptr<Model>> & BBResourceManager::getSceneModels() const
{
    return sceneModels;
}

std::unordered_map<std::string, std::unique_ptr<Model>> & BBResourceManager::getSceneModels()
{
    return sceneModels;
}