//
// Created by Marco on 14/04/24.
//

#pragma once

#include <ECS.h>
#include <Entity.h>
#include <Components.h>
#include <GraphicsFactory.h>
#include "glm/gtc/matrix_transform.hpp"
/**
 * @class systems
 * @Author Marco Garzon Lara
 * @brief An interfave which updates all the entities in a scene registry
 */
class Systems {
public:
    /**
     * Generates a model from an existing component into a map structure holding model render data
     * @param modelComp The model component to generate the model from
     * @param sceneModels The scene structure holding all of the model data
     */
    static void generateModelFromComponent(const ModelComponent & modelComp, std::unordered_map<std::string, std::unique_ptr<Model>> & sceneModels);

    /**
     *
     * @param ecs The registry for which to create the model components onto the entity
     * @param sceneModels The structure containing the models in a scene
     */
    void createModelComponents(ECS &ecs, std::unordered_map<std::string, std::unique_ptr<Model>>& sceneModels);

    /**
     * @author Alan
     * @brief Loads the AI scripts onto the lua_state in preparation for the update call
     * @param ecs The registry to load all components with AIControllerComponent in it
     * @param lua_state to read in the AI scripts to the state
     */
    void ReadAIScripts(ECS &ecs, sol::state &lua_state);

    /**
     *
     * @param renderEngine
     * @param shaderType
     * @param view
     */
    void setLight(RenderEngine & renderEngine, const ShaderType & shaderType, glm::mat4 view);

    /**
     *
     * @param ecs The registry containing all the entities from which to grab the rendearbles from
     * @param shaderType The type of shader that is used for rendering this model
     * @param renderEngine The specified render engine to use for rendering this model
     * @param sceneModels The structure from which to grab this renderable's data
     * @param projection The specified projection matrix used
     * @param view The specified view matrix used
     */
    static void drawModels(const ECS &ecs, const ShaderType & shaderType, RenderEngine & renderEngine, const std::unordered_map<std::string, std::unique_ptr<Model>> & sceneModels, glm::mat4 projection, glm::mat4 view);

    /**
     *
     * @param ecs The registry for which to update the transform components to
     * @param tag The tag component used for entity comparison
     * @param trans The translate to be applied
     * @param rot The rotation to be applied
     */
    void updateTransformComponent(ECS &ecs, const std::string& tag, glm::vec3 trans, glm::vec3 rot);

    /**
     * @author Alan
     * @param ecs The registry for which to update components to
     * @param deltaTime to translate in accordance to FPS
     */
    static void updateAIMovements(ECS &ecs, float deltaTime);

    /**
     * @author Alan
     * @brief update AI call
     * @param sceneNPCs vector of all npcs to iterate through
     * @param lua_state AI script to read for FSM in NPCs
     * @param AIUpdateIntervalTime this is the time representing the time for the ai to be called
     */
    static void updateAI(ECS &ecs, sol::state &lua_state, float AIUpdateIntervalTime);
};