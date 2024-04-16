//
// Created by Marco Garzon Lara on 12/3/2024.
//

#include "Scene.h"

const std::string & Scene::getMasterFile() const
{
    return masterLuaFile;
}

Scene::Scene(const std::string & lua_master)
{
    masterLuaFile = lua_master;
    lua.getLuaState().set("create_entity", &Scene::createEntity); //register create entity function into lua state
}

void Scene::init()
{
    lua.getLuaState().script(masterLuaFile); //load the master lua scene script

}

void Scene::createEntity(const std::filesystem::path & lua_file) //provides a user-friendly function that you only need to specify the script entity to.
{
    entityFactory.create_from_file(bbECS, lua.getLuaState(), lua_file);
}

void Scene::update()
{ }