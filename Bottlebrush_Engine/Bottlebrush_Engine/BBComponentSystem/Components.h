//
// Created by Marco on 09/03/24.
//
#pragma once

#include <string>
#include "Maths.h"

/**
 * @brief Component that controls the position of an entity
 * @author Marco Garzon Lara
 */
struct TransformComponent
{
    ///TODO: Add Vec3D points here
};

/**
 * @brief Component that contains model path information.
 * @author Marco Garzon Lara
 */
struct MeshComponent
{
    std::string model_path;
    std::string material_path;
    //Depending on ASSIMP implementation, more info will probably be added here
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