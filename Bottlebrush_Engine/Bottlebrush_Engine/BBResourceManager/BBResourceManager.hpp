//
// Created by Marco on 17/04/24.
//
#pragma once

#include "ECS.h"
#include "GraphicsFactory.h"
#include "Terrain.h"
#include <unordered_map>
#include <BBMD2.h>
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

    /**
    *@return A reference map strcture
    */
    const std::unordered_map<std::string, Terrain> & getSceneTerrain() const;
    
    /**
    *@return A reference map structure contain all the terrain data stored for the scene (write usage)
    */
    std::unordered_map<std::string, Terrain> & getSceneTerrain();

     /**
     *@return A reference map structure contain all the MD2 model data stored for the scene (write usage)
     */
    const std::unordered_map<std::string, BBMD2>& getSceneMD2Models() const;

    /**
     *@return A reference map structure contain all the MD2 model data stored for the scene (write usage)
     */
    std::unordered_map<std::string, BBMD2>& getSceneMD2Models();

private:
    std::unordered_map<std::string, std::unique_ptr<Model>> sceneModels; ///The models stored in a scene

    std::unordered_map <std::string, std::unique_ptr<BBMD2>> sceneMD2Models; //The MD2 models stored in a scene

    std::unordered_map<std::string, Terrain> sceneTerrain; //The terrain stored in a scene
};