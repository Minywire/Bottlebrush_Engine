//
// Created by Marco on 14/04/24.
//

#include "Systems.h"

void Systems::generateModelFromComponent(const ModelComponent & modelComp, std::unordered_map<std::string, std::unique_ptr<Model>> & sceneModels)
{
    if(sceneModels.find(modelComp.model_path) == sceneModels.end())
    {
        sceneModels.emplace(std::pair<std::string, std::unique_ptr<Model>>(modelComp.model_path, GraphicsFactory<GraphicsAPI::OpenGL>::CreateModel(modelComp.model_path, modelComp.material_path)));
    }
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

void Systems::drawModels(const ECS &ecs, const ShaderType & shaderType, RenderEngine & renderEngine, const std::unordered_map<std::string, std::unique_ptr<Model>> & sceneModels, glm::mat4 projection, glm::mat4 view)
{
    auto group = ecs.GetAllEntitiesWith<ModelComponent, TransformComponent>(); //the container with all the matching entities

    for(auto entity : group)
    {
        auto& currentModelComponent = group.get<ModelComponent>(entity);
        auto& currentTransformComponent = group.get<TransformComponent>(entity);

        glm::mat4 transform = {1};
        transform = glm::translate(transform, currentTransformComponent.position);
        transform = glm::rotate(transform, currentTransformComponent.rotation.x, glm::vec3(1,0,0));
        transform = glm::rotate(transform, currentTransformComponent.rotation.y, glm::vec3(0,1,0));
        transform = glm::rotate(transform, currentTransformComponent.rotation.z, glm::vec3(0,0,1));
        transform = glm::scale(transform, currentTransformComponent.scale);

        if(sceneModels.count(currentModelComponent.model_path) != 0)
        {
            renderEngine.GetShader(shaderType)->SetUniformMatrix4fv("projection", projection);
            renderEngine.GetShader(shaderType)->SetUniformMatrix4fv("view", view);
            renderEngine.GetShader(shaderType)->SetUniformMatrix4fv("model", transform);

            // Inverse of the view matrix gives the world-to-camera transformation
            glm::mat4 inverseViewMatrix = glm::inverse(view);

            // The camera's position is the translation part of the inverse view matrix
            glm::vec3 cameraPosition = glm::vec3(inverseViewMatrix[3]);

            renderEngine.GetShader(shaderType)->SetUniform3f("lightColour", 1.0f, 1.0f, 1.0f);
            renderEngine.GetShader(shaderType)->SetUniform3f("lightPos", 100.0f, 0.0f, 0.0f);
            renderEngine.GetShader(shaderType)->SetUniform3f("viewPos", cameraPosition.x, cameraPosition.y, cameraPosition.z);
            //draw model
            for (unsigned int i = 0; i < sceneModels.at(currentModelComponent.model_path)->GetSubMeshes().size(); i++) {
                sceneModels.at(currentModelComponent.model_path)->GetSubMeshes()[i]->SetTexture();
                renderEngine.Draw(shaderType,
                                   *sceneModels.at(currentModelComponent.model_path)->GetSubMeshes()[i]->GetVertexArray(),
                                   sceneModels.at(currentModelComponent.model_path)->GetSubMeshes()[i]->GetIndexCount());
            }
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
