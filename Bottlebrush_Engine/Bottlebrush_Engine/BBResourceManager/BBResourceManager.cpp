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

const std::unordered_map<std::string, BBMD2> & BBResourceManager::getSceneMD2Models() const
{
    return sceneMD2Models;
}

std::unordered_map<std::string, BBMD2> & BBResourceManager::getSceneMD2Models()
{
    return sceneMD2Models;
}

const std::unordered_set<std::string>& BBResourceManager::getSceneAIStates() const
{
    return sceneAIStates;
}

std::unordered_set<std::string>& BBResourceManager::getSceneAIStates()
{
    return sceneAIStates;
}