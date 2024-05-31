//
// Created by Marco Garzon Lara on 12/3/2024.
//
#pragma once

#include <Skybox.h>
#include <BBScript.h>
#include <Window.h>
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
    void ProcessInput(float deltaTime);
    
    /**
     *
     * @param lua_master
     */
    explicit Scene(const std::string & lua_master, float screenwidth, float screenheight);

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
    void setExitFlag(bool flag);

    /**
     *
     */
    void setFirstMouseFlag(bool flag);

    /**
    *
    */
    void setWireFrameFlag(bool flag);

    void setLastX(float lX);

    void setLastY(float lY);

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
    void update();

    /**
    * 
    */
    const Camera & getCamera() const;

    Camera& getCamera();

    bool getWireframeFlag() const;
    
    bool getExitScreenFlag() const;

    bool getFirstMouseFlag() const;

    float getLastX() const;

    float getLastY() const;

   private:
    Window window;

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

    float accumulatedFrameTime = 0; // a time counter used to slow AI updates, so that it is not called everyframe
    const float UpdateAIInterval; // interval at which to update AI, a value of 1 roughly represents a second
    
    Skybox skybox;

    Camera mainCamera; // main scene camera. Scene realistically only needs one camera for this project
    unsigned int screen_width = 1920, screen_height = 1080;
    bool wireframe = false;

    float last_x = screen_width / 2.0f, last_y = screen_height / 2.0f, offset_y = 1.5f;
    bool first_mouse_click = true;

    bool exitScreen = false;

    float last_frame = 0;
};