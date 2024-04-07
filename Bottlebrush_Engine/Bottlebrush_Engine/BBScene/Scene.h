//
// Created by Marco Garzon Lara on 12/3/2024.
//
#pragma once

#include "ECS.h"
#include <string>
#include <sol/sol.hpp>

/**
 * @class Scene
 * @brief The scene 'graph' for a game instance created in Bottlebrush Engine
 * @author Marco Garzon Lara
 */
class Scene
{
public:
    Scene(std::string & lua_master) : master_lua_file(lua_master) {};

    /**
     *@brief Default constructor.
     */
    Scene();
private:
    std::string master_lua_file;

    ECS bb_ecs; ///The ECS object containing the enTT registry.

};