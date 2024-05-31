//
// Created by Marco on 14/04/24.
//

#include "Systems.h"
#include "BBScript.h"
#include "RegisterAIScripts.h"

void Systems::generateModelFromComponent(const ModelComponent & modelComp, std::unordered_map<std::string, std::unique_ptr<Model>> & sceneModels)
{
    if(sceneModels.find(modelComp.model_path) == sceneModels.end())
    {
        sceneModels.emplace(std::pair<std::string, std::unique_ptr<Model>>(modelComp.model_path, GraphicsFactory<GraphicsAPI::OpenGL>::CreateModel(modelComp.model_path, modelComp.material_path)));
    }
}

void Systems::generateTerrainFromComponent(const TerrainComponent & terrainComp, const TransformComponent & terrainTransform, std::unordered_map<std::string, Terrain> & sceneTerrain) 
{
    if(!sceneTerrain.contains(terrainComp.terrain_path))
    {
        sceneTerrain.emplace(std::pair<std::string, Terrain>(terrainComp.terrain_path, Terrain(terrainComp.terrain_path, terrainComp.terrain_texture, terrainTransform.scale, terrainTransform.position)));
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

void Systems::createTerrainComponents(ECS &ecs, std::unordered_map<std::string, Terrain> & sceneTerrain)
{
    auto group = ecs.GetAllEntitiesWith<TransformComponent, TerrainComponent>(); //the container with all the matching entities

    for(auto entity : group)
    {
        auto& currentTerrainComponent = group.get<TerrainComponent>(entity);
        auto& currentTransform = group.get<TransformComponent>(entity);

        generateTerrainFromComponent(currentTerrainComponent, currentTransform, sceneTerrain);
    }
}

void Systems::ReadAIScripts(ECS& ecs, sol::state & lua_state) 
{
    auto group = ecs.GetAllEntitiesWith<AIControllerComponent>();

    for (auto entity : group)
    {
        auto& aic = group.get<AIControllerComponent>(entity);

        if(aic.npc.GetFSM().GetStatePath().extension() != ".lua") { throw std::runtime_error("Lua file is no lua file"); }
        lua_state.script_file(aic.npc.GetFSM().GetStatePath().string());
    }
    AIScripts::registerScriptedFSM(lua_state);
    AIScripts::registerScriptedNPC(lua_state, ecs);
    AIScripts::registerScriptedGLM(lua_state);
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
        
        // @Debug Line
        //std::cout << "speed: " << move.current_speed << std::endl;

        // move in its current direction by its current speed
        transform.position.x += npc.GetDirection().x * deltaTime * npc.GetCurrentSpeed();
        transform.position.z += npc.GetDirection().y * deltaTime * npc.GetCurrentSpeed();
        // rotate the character to face the direction, currently given in radians
        transform.rotation.y = std::atan2(npc.GetDirection().y, npc.GetDirection().x);

        //change the NPC's y position to the terrain height
        auto terrainGroup = ecs.GetAllEntitiesWith<TerrainComponent>();
        for (auto terrainEnitity : terrainGroup)
        {
            auto& terrainComp = terrainGroup.get<TerrainComponent>(terrainEnitity);
            auto& terrain = sceneTerrain.at(terrainComp.terrain_path);
            float newY = terrain.GetHeight(transform.position.x, transform.position.z);

            // as getHeight returns 0 if its out of bounds. Avoids collision
            // with other terrains, if there were more than 1.
            if (newY == 0) continue; 

            // set the new y position
            transform.position.y = newY + 10; // plus an offset, should be taken out once other physics is implemented
        }
    }
}

void Systems::updateAI(ECS& ecs, sol::state& lua_state, float deltaTime) {
    auto group = ecs.GetAllEntitiesWith<AIControllerComponent>();

    for (auto entity : group)
    {
      auto& aic = group.get<AIControllerComponent>(entity);

      aic.npc.Update(lua_state, deltaTime);
    }
}