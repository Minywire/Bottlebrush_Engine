//
// Created by Marco Garzon Lara on 12/3/2024.
//
#pragma once

#include <BBScript.h>
#include <ECS.h>
#include <Systems.h>
#include <EntityFactory.h>
#include <string>
#include <sol/sol.hpp>
#include <BBResourceManager.hpp>

/**
 * @class Scene
 * @brief The scene 'graph' for a game instance created in Bottlebrush Engine
 * @author Marco Garzon Lara
 */
class Scene
{
public:
    Scene(const std::string & lua_master);

    void init();

    void createEntity(const std::string & lua_file);

    const ECS & getECS() const;

    const std::string &getMasterFile() const;

    void update();
private:
    std::unique_ptr<RenderEngine> renderEngine;
    EntityFactory entityFactory;
    std::string masterLuaFile; ///The master scene file script for Lua
    BBScript lua; ///The BBScript object containing the lua state
    ECS bbECS; ///The ECS object containing the enTT registry.
    Systems bbSystems;
    BBResourceManager resources;
};