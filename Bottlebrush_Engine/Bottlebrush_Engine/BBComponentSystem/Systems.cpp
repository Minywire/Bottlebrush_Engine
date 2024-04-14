//
// Created by Marco on 14/04/24.
//

#include "Systems.h"

void Systems::createModelComponents(ECS &ecs, std::vector<OpenGLModel> & sceneModels)
{
    auto group = ecs.GetAllEntitiesWith<ModelComponent>(); //the container with all the matching entities

    for(auto entity : group)
    {
        auto& currentModelComponent = group.get<ModelComponent>(entity);

        OpenGLModel modelBuffer(currentModelComponent.model_path);

        //sceneModels.push_back(modelBuffer); //Template specification problems here with OpenGLMesh constructor, needs to be sorted out by renderengine experts :O.
        //do model creation stuff here for the current group entity.
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