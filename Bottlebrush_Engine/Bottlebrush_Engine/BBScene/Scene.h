//
// Created by Marco Garzon Lara on 12/3/2024.
//
#pragma once

#include "ECS.h"
#include <sol/sol.hpp>

/**
 * @class Scene
 * @brief The scene 'graph' for a game instance created in Bottlebrush Engine
 * @author Marco Garzon Lara
 */
class Scene
{
public:
    Scene(std::string lua_master);

    /**
     *@brief Default constructor.
     */
    Scene();
private:
    ECS bb_ecs; ///The ECS object containing the enTT registry.

};
