//
// Created by Marco on 09/03/24.
//
#pragma once

#include <string>

/**
 * @brief Component that controls the position of an entity
 */
struct TransformComponent
{
    ///TODO: Add our vec3 definitions here for entity position
};

/**
 * @brief Component that contains model information.
 */
struct MeshComponent
{
    std::string modelPath;
    std::string materialPath;
    //Depending on ASIMP implementation, more info will probably be added here
};

/**
 * @brieg Component that contains alias or tag.
 */
struct TagComponent
{
    std::string tag;
};

/**
 * @brief Component that contains movement data for player
 */
struct PlayerControllerComponent
{
    float maxSpeed;
    float currentSpeed;
    float accelerationRate;
    float decelerationRate;
};