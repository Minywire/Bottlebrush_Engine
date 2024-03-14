//
// Created by Marco on 09/03/24.
//
#pragma once

#include <string>
#include "../include/engine/maths/Maths.h"

/**
 * @brief Component that controls the position of an entity
 * @author Marco Garzon Lara
 */
struct TransformComponent
{
    ///TODO: Add our vec3 definitions here for entity position
};

/**
 * @brief Component that contains model path information.
 * @author Marco Garzon Lara
 */
struct MeshComponent
{
    std::string modelPath;
    std::string materialPath;
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
    float maxSpeed;
    float currentSpeed;
    float accelerationRate;
    float decelerationRate;
};