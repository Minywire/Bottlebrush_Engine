//
// Created by Marco Garzon Lara on 12/3/2024.
//

#include "Scene.h"

Scene::Scene()
{
    lua.getLuaState().set("create_entity", &Scene::createEntity); //register create entity function into lua state
}

void Scene::init()
{ }

void Scene::createEntity(const std::filesystem::path & lua_file) //provides a user-friendly function that you only need to specify the script entity to.
{
    entityFactory.create_from_file(bbECS, lua.getLuaState(), lua_file);
}

void Scene::update()
{ }