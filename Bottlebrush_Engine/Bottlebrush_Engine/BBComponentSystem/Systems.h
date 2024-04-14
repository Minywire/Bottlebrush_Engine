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
    void createModelComponents(ECS &ecs, std::vector<OpenGLModel> & sceneModels);

    void updateTransformComponent(ECS &ecs, const std::string& tag, glm::vec3 trans, glm::vec3 rot);
};