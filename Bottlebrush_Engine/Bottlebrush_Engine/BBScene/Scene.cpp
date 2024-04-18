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

Scene::Scene(const std::string & lua_master)
{
    masterLuaFile = lua_master;
    lua.getLuaState().set_function("create_entity", &Scene::createEntity, this); //register create entity function into lua state of this instance
}

void Scene::init()
{
    lua.getLuaState().do_file(masterLuaFile); //load the master lua scene script

}

void Scene::createEntity(const std::string & lua_file) //provides a user-friendly function that you only need to specify the script entity to.
{
    entityFactory.create_from_file(bbECS, lua.getLuaState(), lua_file);
}

void Scene::update()
{ }