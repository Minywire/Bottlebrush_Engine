//
// Created by Marco on 14/04/24.
//

#include "Systems.h"

void Systems::generateModelFromComponent(const ModelComponent & modelComp, std::unordered_map<std::string, std::unique_ptr<Model>> & sceneModels)
{
    sceneModels.emplace(std::pair<std::string, std::unique_ptr<Model>>(modelComp.model_path, GraphicsFactory<GraphicsAPI::OpenGL>::CreateModel(modelComp.model_path, modelComp.material_path)));
}

void Systems::createModelComponents(ECS &ecs, std::unordered_map<std::string, std::unique_ptr<Model>> & sceneModels)
{
    auto group = ecs.GetAllEntitiesWith<ModelComponent>(); //the container with all the matching entities

    for(auto entity : group)
    {
        auto& currentModelComponent = group.get<ModelComponent>(entity);

        generateModelFromComponent(currentModelComponent, sceneModels);
    }
}

void Systems::drawModels(ECS &ecs, const std::unordered_map<std::string, std::unique_ptr<Model>> & sceneModels)
{
    auto group = ecs.GetAllEntitiesWith<ModelComponent>(); //the container with all the matching entities

    for(auto entity : group)
    {
        auto& currentModelComponent = group.get<ModelComponent>(entity);

        if(sceneModels.count(currentModelComponent.model_path) != 0)
        {
            sceneModels.at(currentModelComponent.model_path);
        }
    }
}

void Systems::updateTransformComponent(ECS &ecs, const std::string& tag, glm::vec3 trans, glm::vec3 rot)
{
    auto group = ecs.GetAllEntitiesWith<TransformComponent, TagComponent>();

    for(auto entity : group)
    {
        auto& currentEntityComponent =  group.get<TransformComponent>(entity);
        if(group.get<TagComponent>(entity).tag == tag)
        {
//            currentEntityComponent.position = trans; //can't do this since the component passed in is a const reference so im currently trying to find a proper way to do it.
//            currentEntityComponent.rotation = rot;
        }
    }

}