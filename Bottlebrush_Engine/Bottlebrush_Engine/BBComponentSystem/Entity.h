//
// Created by Marco on 09/03/24.
//
#pragma once

#include "../BBScene/Scene.h"
#include <iostream>
#include <entt/entt.hpp>

class Entity
{
public:
    explicit operator entt::entity () const;

    Entity();

    explicit Entity(entt::entity handle);

    template<typename T>
    bool hasComponent(const entt::registry& reg);

    template<typename T, typename... Args>
    T& addComponent(entt::registry& reg, Args&&... args);

    template<typename T>
    const T& getComponent(const entt::registry& reg) const;

    template<typename T>
    void removeComponent(entt::registry& reg);

private:
    entt::entity entityHandle; //!> The entity wrapped by Bottlebrush's Entity interface

};


