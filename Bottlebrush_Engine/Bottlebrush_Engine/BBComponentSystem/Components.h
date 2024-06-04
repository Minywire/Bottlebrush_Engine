//
// Created by Marco on 09/03/24.
//
#pragma once

#include <string>
#include <glm/glm.hpp>
#include <sol/sol.hpp>

#include "NPC.h"
#include "BBMD2.h"

#include <PhysicsBody.h>

/** forward decl to avoid circle linking */
class Entity;

/**
 * @brief Component that binds a lua function to an Entity
 * @author Marco Garzon Lara
 */
struct ScriptFunctionComponent
{
    sol::function func;
};

/**
 * @brief Component that controls the position of an entity
 * @author Marco Garzon Lara
 */
struct TransformComponent
{
    glm::vec3 position;
    glm::vec3 rotation;
    glm::vec3 scale;
};

/**
 * @brief Component that contains model path information.
 * @author Marco Garzon Lara
 */
struct ModelComponent
{
    std::string model_path;
    std::string material_path;
};

/**
 * @brief Component that contains alias or tag for entity query.
 * @author Marco Garzon Lara
 */
struct TagComponent
{
    std::string tag;
};

/**
 * @brief Component that contains data for AI controlled NPCs
 */
struct AIControllerComponent
{
    NPC npc;

    AIControllerComponent(const std::filesystem::path& statesPath, const std::string& initialState,
                          Entity& entity)
        : npc(NPC(statesPath, initialState, entity))
    {}
};

/**
* @brief Component that contains data for the MD2 Model
*/
struct MD2Component
{
    std::string model_path;
    std::string texture_path;
    std::string current_animation = "stand";
    int current_frame = 0;
    float interpolation = 0.0f;
    float anim_speed = 5.0f;
};

/**
* @brief Component that contains Terrain data
*/
struct TerrainComponent 
{
    std::string terrain_path;
    std::string terrain_texture;
};

struct PhysicsBodyComponent {
    PhysicsBody physics_body;
};