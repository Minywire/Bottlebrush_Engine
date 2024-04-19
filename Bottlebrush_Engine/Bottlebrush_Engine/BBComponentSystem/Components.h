//
// Created by Marco on 09/03/24.
//
#pragma once

#include <string>
#include <glm/glm.hpp>
#include <sol/sol.hpp>

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
    glm::vec3 scale = {1, 1, 1};
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
 * @brief Component that contains movement data for player
 * @author Marco Garzon Lara
 */
struct PlayerControllerComponent
{
    float max_speed;
    float current_speed;
    float acceleration_rate;
    float deceleration_rate;
};