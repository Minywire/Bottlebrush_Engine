//
// Created by Marco on 17/04/24.
//
#pragma once

#include "ECS.h"
#include "BBMD2.h"
#include "GraphicsFactory.h"
#include <unordered_map>
/**
 * @class BBResourceManager
 * @brief Stores data generated from ECS systems which utilise metadata that is saved into the ECS Entities.
 */


class BBResourceManager {
public:
    /**
     *
     * @return A reference map structure contain all the model data stored for the scene (read usage)
     */
    const std::unordered_map<std::string, std::unique_ptr<Model>> & getSceneModels() const;

    /**
     *
     * @return A reference map structure contain all the model data stored for the scene (write usage)
     */
    std::unordered_map<std::string, std::unique_ptr<Model>> & getSceneModels();

private:
    std::unordered_map<std::string, std::unique_ptr<Model>> sceneModels; ///The models stored in a scene
    std::unordered_map <std::string, std::unique_ptr<BBMD2>> sceneMD2Models; //The MD2 models stored in a scene
};