//
// Created by Marco on 14/04/24.
//

#include "Systems.h"
#include "BBScript.h"
#include "RegisterAIScripts.h"
#include "EventDispatcher.h"
#include "Singleton.h"

void Systems::RegisterAIFunctions(ECS& ecs, sol::state & lua_state, const Camera& player) 
{
    AIScripts::registerScriptedFSM(lua_state);
    AIScripts::registerScriptedNPC(lua_state, ecs, player, endGame);
    AIScripts::registerScriptedGLM(lua_state);
    AIScripts::registerScriptedAnimation(lua_state, ecs);
    AIScripts::registerScriptedMessage(lua_state);
}

void Systems::setLight(RenderEngine & renderEngine, const ShaderType & shaderType, glm::mat4 view)
{
    // we can ignore this given we're handling a direction instead of a pos - nvm its needed for specular
    // Inverse of the view matrix gives the world-to-camera transformation
    glm::mat4 inverseViewMatrix = glm::inverse(view);

    // The camera's position is the translation part of the inverse view matrix
    glm::vec3 cameraPosition = glm::vec3(inverseViewMatrix[3]);

    renderEngine.GetShader(shaderType)->SetUniform3f("lightColour", 1.0f, 1.0f, 1.0f);
    renderEngine.GetShader(shaderType)->SetUniform3f("direction", 0.2f, -0.7f, 0.4f);
    renderEngine.GetShader(shaderType)->SetUniform3f("viewPos", cameraPosition.x, cameraPosition.y, cameraPosition.z);
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
            //set uniforms for model
            renderEngine.GetShader(shaderType)->SetUniformMatrix4fv("projection", projection);
            renderEngine.GetShader(shaderType)->SetUniformMatrix4fv("view", view);
            renderEngine.GetShader(shaderType)->SetUniformMatrix4fv("model", transform);

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

void Systems::drawMD2Models(const ECS& ecs, const ShaderType& shaderType, RenderEngine& renderEngine, std::unordered_map<std::string, BBMD2> & MD2s, glm::mat4 projection, glm::mat4 view)
{
    auto group = ecs.GetAllEntitiesWith<MD2Component, TransformComponent>();

    for (auto entity : group)
    {
        auto& currentMD2Component = group.get<MD2Component>(entity);
        auto& currentTransformComponent = group.get<TransformComponent>(entity);

        auto& MD2Model = MD2s.at(currentMD2Component.model_path);
        
        int anim = MD2Model.getSpecificAnim(currentMD2Component.current_animation);
         
        glm::mat4 transform = {1};
        transform = glm::translate(transform, currentTransformComponent.position);
        transform = glm::rotate(transform, glm::radians(currentTransformComponent.rotation.x), glm::vec3(1,0,0));
        transform = glm::rotate(transform, glm::radians(currentTransformComponent.rotation.y), glm::vec3(0,1,0));
        transform = glm::rotate(transform, glm::radians(currentTransformComponent.rotation.z), glm::vec3(0,0,1));
        //MD2 standard rotations last
        transform = glm::rotate(transform, glm::radians(-90.f), glm::vec3(0,1,0));
        transform = glm::rotate(transform, glm::radians(-90.f), glm::vec3(1,0,0));
        transform = glm::scale(transform, currentTransformComponent.scale);

        renderEngine.GetShader(shaderType)->SetUniformMatrix4fv("projection", projection);
        renderEngine.GetShader(shaderType)->SetUniformMatrix4fv("view", view);
        renderEngine.GetShader(shaderType)->SetUniformMatrix4fv("model", transform);
        renderEngine.GetShader(shaderType)->SetUniform1f("interpolation", currentMD2Component.interpolation);
        renderEngine.GetShader(shaderType)->SetUniform1i("texSampler1", 0);

        MD2Model.setTexture();
        renderEngine.Draw(shaderType, MD2Model.getVecArrays().at(currentMD2Component.current_frame), MD2Model.getModelSize());
    }
}

void Systems::updateMD2Interpolation(ECS& ecs, std::unordered_map<std::string, BBMD2>& MD2s, float deltaTime)
{
    auto group = ecs.GetAllEntitiesWith<MD2Component>();

    for (auto entity : group)
    {
        auto& currentMD2Component = group.get<MD2Component>(entity);

        auto& anim = MD2s.at(currentMD2Component.model_path).getAnimations();

        auto& interp = currentMD2Component.interpolation;
        auto& currentFrame = currentMD2Component.current_frame;
        auto& animName = currentMD2Component.current_animation;

        if (currentFrame > anim[animName].endIndex || currentFrame < anim[animName].startIndex)
            currentFrame = anim[animName].startIndex;

        if (interp >= 1.0f) {
            interp = 0.f;
            if (currentFrame <= anim[animName].endIndex) currentFrame++;
        } else {
            interp += deltaTime * currentMD2Component.anim_speed;
        }
    }

}

void Systems::drawTerrain(const ECS& ecs, const ShaderType& terrainShader, RenderEngine& renderEngine, std::unordered_map<std::string, Terrain> & sceneTerrain, bool grayscale, glm::mat4 projection, glm::mat4 view)
{
    auto group = ecs.GetAllEntitiesWith<TerrainComponent, TransformComponent>(); //the container with all the matching entities

    for(auto entity : group)
    {

        auto& currentTerrainComponent = group.get<TerrainComponent>(entity);
        auto& currentTransformComponent = group.get<TransformComponent>(entity);

        auto& terrain = sceneTerrain.at(currentTerrainComponent.terrain_path);

        glm::mat4 transform = {1};

        // Vert Uniforms
        renderEngine.GetShader(terrainShader)
            ->SetUniformMatrix4fv("gModel", transform);
        renderEngine.GetShader(terrainShader)
            ->SetUniformMatrix4fv("gView", view);
        renderEngine.GetShader(terrainShader)
            ->SetUniformMatrix4fv("gProjection", projection);
        renderEngine.GetShader(terrainShader)
            ->SetUniform1f("gMinHeight", terrain.GetMinHeight());
        renderEngine.GetShader(terrainShader)
            ->SetUniform1f("gMaxHeight", terrain.GetMaxHeight());

        // Frag Uniforms
        renderEngine.GetShader(terrainShader)
            ->SetUniform1i("gGrayscale", grayscale);
        renderEngine.GetShader(terrainShader)->SetUniform1i("gTex", 0);
        renderEngine.GetShader(terrainShader)
            ->SetUniform3fv("gReversedLightDir", {-0.2f, 0.7f, -0.4f});

        // draw
        terrain.GetMesh()->SetTexture(0);
        renderEngine.Draw(terrainShader, *terrain.GetMesh()->GetVertexArray(),
                          terrain.GetElements().size());
    }
}

void Systems::updateAIMovements(ECS& ecs, float deltaTime, std::unordered_map<std::string, Terrain> & sceneTerrain)
{
    auto group = ecs.GetAllEntitiesWith<TransformComponent, AIControllerComponent>();

    for (auto entity : group)
    {
        auto& aic = group.get<AIControllerComponent>(entity);
        auto& transform = group.get<TransformComponent>(entity);
        auto& npc = aic.npc;

        // check if we need to decelerate
        if (!npc.IsMoving()) {
            // stopped moving, leave this entity
            if (npc.GetCurrentSpeed() <= 0) continue;

            npc.GetCurrentSpeed() -= npc.GetDecceleration();
        } else { // accelerate to max speed
            if (npc.GetCurrentSpeed() <= npc.GetMaxSpeed()) 
                npc.GetCurrentSpeed() += npc.GetAcceleration();
        }

        // move in its current direction by its current speed
        transform.position.x += npc.GetDirection().x * deltaTime * npc.GetCurrentSpeed();
        transform.position.z += npc.GetDirection().y * deltaTime * npc.GetCurrentSpeed();
        // rotate the character to face the direction, currently given in radians
        transform.rotation.y = glm::degrees(std::atan2(npc.GetDirection().x, npc.GetDirection().y));

        //change the NPC's y position to the terrain height
        auto terrainGroup = ecs.GetAllEntitiesWith<TerrainComponent>();
        for (auto terrainEnitity : terrainGroup)
        {
            auto& terrainComp = terrainGroup.get<TerrainComponent>(terrainEnitity);
            auto& terrain = sceneTerrain.at(terrainComp.terrain_path);

            // Optional returns if its out of bounds. 
            // Avoids collision with other terrains, if there were more than 1.
            auto heightOpt = terrain.GetHeight(transform.position.x, transform.position.z);
            if (!heightOpt.has_value()) continue;

            // set the new y position
            transform.position.y = heightOpt.value() + 20 * transform.scale.y; // plus an offset, should be taken out once other physics is implemented
        }
    }
}

void Systems::updateAI(ECS& ecs, sol::state& lua_state, float deltaTime) {
    auto group = ecs.GetAllEntitiesWith<AIControllerComponent>();

    for (auto entity : group)
    {
      auto& aic = group.get<AIControllerComponent>(entity);
      lua_state.script_file(aic.npc.GetFSM().GetStatePath().string());

      aic.npc.Update(lua_state, deltaTime);
    }

    // dispatch any delayed messages
    Singleton<EventDispatcher>::Instance().DispatchDelayedMessages(lua_state, deltaTime);
}

void Systems::updateCameraTerrainHeight(const ECS& ecs, const std::unordered_map<std::string, Terrain> & terrains, Camera & camera,  float offset_y)
{
    auto group = ecs.GetAllEntitiesWith<TerrainComponent, TransformComponent>();

    for (auto entity : group)
    {
        const auto& currentTerrainComp = group.get<TerrainComponent>(entity);
        const auto& terrainTransform = group.get<TransformComponent>(entity);
        const auto& currentTerrain = terrains.at(currentTerrainComp.terrain_path);

        const std::optional<float> terrain_height =
            currentTerrain.GetHeight(camera.GetPosition().x, camera.GetPosition().z);

        if (terrain_height.has_value())
        {
            camera.SetPositionY(terrain_height.value() + offset_y);
        } 
    }
}

const std::optional<float> Systems::getTerrainHeight(const ECS& ecs, const std::unordered_map<std::string, Terrain>& terrains, float x, float z)
{
    auto group = ecs.GetAllEntitiesWith<TerrainComponent>();

    for (auto entity : group) 
    {
        const auto& currentTerrainComp = group.get<TerrainComponent>(entity);
        const auto& currentTerrain = terrains.at(currentTerrainComp.terrain_path);

        const std::optional<float> terrain_height = currentTerrain.GetHeight(x, z);

        if (terrain_height.has_value()) 
        {
            return terrain_height;
        }
    }
    return std::nullopt;
}   