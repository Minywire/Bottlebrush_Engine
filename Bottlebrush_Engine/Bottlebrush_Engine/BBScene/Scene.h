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
#include <Camera.h>

/**
 * @class Scene
 * @brief The scene 'graph' for a game instance created in Bottlebrush Engine
 * @author Marco Garzon Lara
 */
class Scene
{
public:
    /**
     *
     * @param lua_master
     */
    explicit Scene(const std::string & lua_master);

    /**
     *
     * @param projMatrix
     */
    void setProjectionMatrix(glm::mat4 projMatrix);

    /**
     *
     * @param viewMatrix
     */
    void setViewMatrix(glm::mat4 viewMatrix);

    /**
     *
     */
    void init();

    /**
     *
     * @param lua_file
     */
    void createEntity(const std::string & lua_file);

    /**
     *
     * @param lua_file
     * @param xPos
     * @param yPos
     * @param zPos
     */
    void createEntityAndTransform(const std::string & lua_file, float xPos, float yPos, float zPos);

    /**
     *
     * @param shaderType
     * @param vertexSource
     * @param fragSource
     */
    void setRendererShaderSource(ShaderType shaderType, const std::string & vertexSource, const std::string & fragSource);

    /**
     *
     */
    void clearRenderEngine();

    /**
     *
     */
    void update(float deltaTime);
private:
    glm::mat4 projectionMatrix; ///The camera projection matrix (temporary hack until everything from EntryPoint is ported here).
    glm::mat4 viewMatrix; ///The camera projection matrix (temporary hack until everything from EntryPoint is ported here).

    //Camera sceneCamera; This camera will be implemented later. A lot of callback porting is needed for this, so it won't be done in time for Assignment 1 submission.
    std::unique_ptr<RenderEngine> renderEngine; ///The render engine

    EntityFactory entityFactory; ///The interface in charge of creating entities from Scripts
    std::string masterLuaFile; ///The master scene file script for Lua
    BBScript lua; ///The BBScript object containing the lua state

    ECS bbECS; ///The ECS object containing the enTT registry.
    Systems bbSystems; ///The Systems of the ECS operating on entity data
    BBResourceManager resources; ///The resources stored in the scene (only model data for now)

    float accumulatedFrameTime; // a time counter used to slow AI updates, so that it is not called everyframe
    const float UpdateAIInterval; // interval at which to update AI, a value of 1 roughly represents a second
};