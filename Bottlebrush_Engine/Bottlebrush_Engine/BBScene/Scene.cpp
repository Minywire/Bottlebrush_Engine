//
// Created by Marco Garzon Lara on 12/3/2024.
//

#include "Scene.h"

const std::string & Scene::getMasterFile() const
{
    return masterLuaFile;
}

const ECS & Scene::getECS() const
{
    return bbECS;
}

void Scene::createEntity(const std::string & lua_file) //provides a user-friendly function that you only need to specify the script entity to.
{
    entityFactory.create_from_file(bbECS, lua.getLuaState(), lua_file);
}

Scene::Scene(const std::string & lua_master)
{
    renderEngine = GraphicsFactory<GraphicsAPI::OpenGL>::CreateRenderer();
    masterLuaFile = lua_master;
    lua.getLuaState().set_function("create_entity", &Scene::createEntity, this); //register create entity function into lua state of this instance
}

void Scene::setProjectionMatrix(glm::mat4 projMatrix)
{
    projectionMatrix = projMatrix;
}

void Scene::setViewMatrix(glm::mat4 vMatrix)
{
    viewMatrix = vMatrix;
}

void Scene::init()
{
    if(!lua.getLuaState().do_file(masterLuaFile).valid())
    {
        std::cout << "Could not load master game script file\n";
    }//load the master lua scene script containing all entities

    bbSystems.createModelComponents(bbECS, resources.getSceneModels());
}

void Scene::update()
{
    Systems::drawModels(bbECS, ShaderType::Default, *renderEngine, resources.getSceneModels(), projectionMatrix, viewMatrix);
}

void Scene::setRendererShaderSource(ShaderType shaderType, const std::string & vertexSource, const std::string & fragSource)
{
    renderEngine->SetShaderSource(shaderType, vertexSource, fragSource);
}

void Scene::clearRenderEngine()
{
    renderEngine->Clear();
}