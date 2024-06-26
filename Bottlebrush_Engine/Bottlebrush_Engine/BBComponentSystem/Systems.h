//
// Created by Marco on 14/04/24.
//

#pragma once

#include <ECS.h>
#include <Entity.h>
#include <Components.h>
#include <Terrain.h>
#include <GraphicsFactory.h>
#include "glm/gtc/matrix_transform.hpp"
#include "Camera.h"
#include <BBMD2.h>

#include "CollisionMgr.h"

/**
 * @class systems
 * @Author Marco Garzon Lara
 * @brief An interfave which updates all the entities in a scene registry
 */
class Systems {
public:
    /**
     * @author Alan
     * @brief Registers the appropriate AI functions to lua
     * @param ecs The registry to pass into the lua registers to dependencyinject into NPC
     * @param lua_state to read in the AI scripts to the state
     * @param endGame bool to end the game
     */
    void RegisterAIFunctions(ECS &ecs, sol::state &lua_state, const Camera &player, bool& endGame);

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
     * @param ecs The registry containing all the entities from which to grab
     * the rendearbles from
     * @param shaderType The type of shader that is used for rendering this
     * model
     * @param renderEngine The specified render engine to use for rendering this
     * model
     * @param sceneModels The structure from which to grab this renderable's
     * data
     * @param projection The specified projection matrix used
     * @param view The specified view matrix used
     * @param interpolation The MD2 animation 
     */
    static void drawMD2Models(const ECS &ecs, const ShaderType & shaderType, RenderEngine & renderEngine, std::unordered_map<std::string, BBMD2> & MD2s, glm::mat4 projection, glm::mat4 view);
    
    /**
    *@brief updates the interpolation value needed to transition between MD2 model animation frames
    * @param ecs The ECS registry
    * @param MD2s The resource map containing MD2 models
    * @param deltaTime The accumulated frame time between last frame and current frame
    */
    static void updateMD2Interpolation(ECS &ecs, std::unordered_map<std::string, BBMD2> &MD2s, float deltaTime);

    /**
     *
     * @param ecs The registry containing all the entities from which to grab
     * the rendearbles from
     * @param shaderType The type of shader that is used for rendering this
     * model
     * @param renderEngine The specified render engine to use for rendering this
     * model
     * @param sceneTerrain The structure from which to grab this renderable's
     * data
     * @param projection The specified projection matrix used
     * @param view The specified view matrix used
     */
    static void drawTerrain(const ECS& ecs, const ShaderType& terrainShader, RenderEngine& renderEngine, std::unordered_map<std::string, Terrain> & sceneTerrain, bool grayscale, glm::mat4 projection, glm::mat4 view);

    /**
     * @author Alan
     * @param ecs The registry for which to update components to
     * @param deltaTime to translate in accordance to FPS
     * @param sceneTerrain a map containing all terrains
     */
    static void updateAIMovements(ECS &ecs, float deltaTime, 
        std::unordered_map<std::string, Terrain> & sceneTerrain);

    /**
     * @author Alan
     * @brief update AI call
     * @param sceneNPCs vector of all npcs to iterate through
     * @param lua_state AI script to read for FSM in NPCs
     * @param AIUpdateIntervalTime this is the time representing the time for the ai to be called
     */
    static void updateAI(ECS &ecs, sol::state &lua_state, float deltaTime);

    /**
    * @brief Sets the camera to the proper terrain height based on whether the camera is on top of a valid terrain component
    * @param ecs The ECS registry
    * @param terrains The resource container containing all of the terrains
    * @param camera The specified camera which gets its position updated
    * @param offset_y A y-offset to adjust player height
    */
    static void updateCameraTerrainHeight(const ECS& ecs, const std::unordered_map<std::string, Terrain> & terrains, Camera & camera, float offset_y = 10.0f);
    
    /**
    * @brief Fetches a height value from a valid terrain component if an x and z value are present within it
    * @param ecs The ECS registry
    * @param terrains The resource map containing terrain objects
    * @param x The x position from which to fetch the height value
    * @param z The z position from which to fetch the height value
    */
    static const std::optional<float> getTerrainHeight(const ECS& ecs, const std::unordered_map<std::string, Terrain> & terrains, float x, float z);

    static void UpdateColliders(ECS &ecs);

    static void CheckObjectCollision(ECS &ecs);
    static void ReslvObjectCollision(TransformComponent &t,
                                     const ColliderComponent &collider);

    static void CheckCameraCollision(const ECS &ecs, Camera &camera,
                                     const ColliderComponent &collider);
    static void ReslvCameraCollision(Camera &camera,
                                     const ColliderComponent &collider);
};
