//
// Created by Marco on 09/03/24.
//
#pragma once

#include <entt/entt.hpp>

class Entity
{
public:
    Entity(entt::entity handle);

    Entity() = default;

    bool HasComponent();

    template<typename T, typename... Args>
    T& AddComponent(Args&&... args);

    template<typename T>
    const T& getComponent() const;

    template<typename T>
    void removeComponent();

private:
    entt::entity entityHandle = entt::null; //!> The entity wrapped by Bottlebrush's Entity interface

};


