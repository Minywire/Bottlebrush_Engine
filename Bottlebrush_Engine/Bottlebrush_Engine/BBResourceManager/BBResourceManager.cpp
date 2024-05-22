//
// Created by Marco on 17/04/24.
//

#include "BBResourceManager.hpp"

const std::unordered_map<std::string, std::unique_ptr<Model>> & BBResourceManager::getSceneModels() const
{
  return sceneModels;
}

std::unordered_map<std::string, std::unique_ptr<Model>> & BBResourceManager::getSceneModels()
{
  return sceneModels;
}
