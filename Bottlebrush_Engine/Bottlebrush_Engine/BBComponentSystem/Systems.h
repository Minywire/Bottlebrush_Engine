//
// Created by Marco on 14/04/24.
//

#pragma once

#include <ECS.h>
#include <Entity.h>
#include <Components.h>
#include <GraphicsFactory.h>
#include "glm/gtc/matrix_transform.hpp"

class Systems {
public:
    static void generateModelFromComponent(const ModelComponent & modelComp, std::unordered_map<std::string, std::unique_ptr<Model>> & sceneModels);

    void createModelComponents(ECS &ecs, std::unordered_map<std::string, std::unique_ptr<Model>>& sceneModels);

    static void drawModels(const ECS &ecs, const ShaderType & shaderType, RenderEngine & renderEngine, const std::unordered_map<std::string, std::unique_ptr<Model>> & sceneModels, glm::mat4 projection, glm::mat4 view);

    void updateTransformComponent(ECS &ecs, const std::string& tag, glm::vec3 trans, glm::vec3 rot);
};