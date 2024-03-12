//
// Created by Marco Garzon Lara on 12/3/2024.
//
#pragma once

#include <entt/entt.hpp>

class Scene
{
public:

private:
    entt::registry registry; ///The registry for ECS management (basically a big array under the hood)
    ///TODO: This Scene will need a camera, Assimp scene, Physics api scene, and our Lua system in the near future.
};
