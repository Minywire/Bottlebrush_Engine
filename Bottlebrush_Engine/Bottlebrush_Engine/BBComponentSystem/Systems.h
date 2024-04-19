//
// Created by Marco on 14/04/24.
//

#pragma once

#include <ECS.h>
#include <Entity.h>
#include <Components.h>
#include <GraphicsFactory.h>

class Systems {
public:
    void generateModelFromComponent(const ModelComponent & modelComp, std::unordered_map<std::string, std::unique_ptr<Model>> & sceneModels);

    void createModelComponents(ECS &ecs, std::unordered_map<std::string, std::unique_ptr<Model>>& sceneModels);

    void updateTransformComponent(ECS &ecs, const std::string& tag, glm::vec3 trans, glm::vec3 rot);
};