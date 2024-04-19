//
// Created by Marco on 17/04/24.
//
#pragma once

#include <ECS.h>
#include <GraphicsFactory.h>
#include <unordered_map>
/**
 * @class BBResourceManager
 * @brief Stores data generated from ECS systems which utilise metadata that is saved into the ECS Entities.
 */
class BBResourceManager {
public:
    /**
     *
     * @param modelComp The Model component queried from an entity
     */
    void generateModelFromComponent(const ModelComponent & modelComp);

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

};