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

    void setRendererShaderSource(ShaderType shaderType, const std::string & vertexSource, const std::string & fragSource);

    void clearRenderEngine();

    const std::string &getMasterFile() const;

    void update();
private:
    std::unique_ptr<RenderEngine> renderEngine = GraphicsFactory<GraphicsAPI::OpenGL>::CreateRenderer(); ///The render engine
    EntityFactory entityFactory; ///The interface in charge of creating entities from Scripts
    std::string masterLuaFile; ///The master scene file script for Lua
    BBScript lua; ///The BBScript object containing the lua state
    ECS bbECS; ///The ECS object containing the enTT registry.
    Systems bbSystems; ///The Systems of the ECS operating on entity data
    BBResourceManager resources; ///The resources stored in the scene (only model data for now)
};