//
// Created by Marco Garzon Lara on 12/3/2024.
//
#pragma once

#include <BBScript.h>
#include <ECS.h>
#include <BBResourceManager.hpp>
#include <EntityFactory.h>
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
    Scene(std::string & lua_master) : masterLuaFile(lua_master) {};

    /**
     *@brief Default constructor.
     */
    Scene();

    void init();

    void update();
private:
    EntityFactory entityFactory;
    std::string masterLuaFile; ///The master scene file script for Lua
    BBScript lua; ///The BBScript object containing the lua state
    ECS bbECS; ///The ECS object containing the enTT registry.
    BBResourceManager sceneResources; ///The interface which stores all the resources in a game scene

};