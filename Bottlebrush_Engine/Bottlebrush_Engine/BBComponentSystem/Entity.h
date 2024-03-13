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
    operator entt::entity () const;

    Entity(entt::entity handle, Scene* scene);

    Entity();

    template<typename T>
    bool hasComponent();

    template<typename T, typename... Args>
    T& addComponent(Args&&... args);

    template<typename T>
    const T& getComponent() const;

    template<typename T>
    void removeComponent();

private:
    entt::entity entityHandle; //!> The entity wrapped by Bottlebrush's Entity interface
    Scene* parentScene; //! Scene which this entity belongs to

};


