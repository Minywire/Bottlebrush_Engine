//
// Created by Marco on 17/04/24.
//
#pragma once

#include <ECS.h>
#include <GraphicsFactory.h>
#include <unordered_map>

class BBResourceManager {
public:
    /**
     *
     * @param modelComp
     */
    void generateModelFromComponent(const ModelComponent & modelComp);

    /**
     *
     * @return
     */
    const std::unordered_map<std::string, std::unique_ptr<Model>> & getSceneModels() const;

    /**
     *
     * @return
     */
    std::unordered_map<std::string, std::unique_ptr<Model>> & getSceneModels();

private:
    std::unordered_map<std::string, std::unique_ptr<Model>> sceneModels; ///The models stored in a scene

};