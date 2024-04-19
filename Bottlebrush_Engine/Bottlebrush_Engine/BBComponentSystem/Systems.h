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
    static void generateModelFromComponent(const ModelComponent & modelComp, std::unordered_map<std::string, std::unique_ptr<Model>> & sceneModels);

    void createModelComponents(ECS &ecs, std::unordered_map<std::string, std::unique_ptr<Model>>& sceneModels);

    static void drawModels(const ECS &ecs, const ShaderType & shaderType, std::unique_ptr<RenderEngine> renderEngine, const std::unordered_map<std::string, std::unique_ptr<Model>> & sceneModels);

    void updateTransformComponent(ECS &ecs, const std::string& tag, glm::vec3 trans, glm::vec3 rot);
};