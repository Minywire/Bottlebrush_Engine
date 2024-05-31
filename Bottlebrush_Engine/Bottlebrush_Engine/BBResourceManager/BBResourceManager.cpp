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

const std::unordered_map<std::string, Terrain> & BBResourceManager::getSceneTerrain() const
{
    return sceneTerrain;
}

std::unordered_map<std::string, Terrain> & BBResourceManager::getSceneTerrain()
{
    return sceneTerrain;
}

std::unordered_map<std::string, std::unique_ptr<Texture>> &BBResourceManager::getSceneTextures() {
    return sceneTextures;
}
