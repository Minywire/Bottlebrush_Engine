//
// Created by Marco on 09/03/24.
//
#pragma once

#include <string>

/**
 * @brief Component that contains transform information.
 */
struct MeshComponent
{
    std::string ModelPath;
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