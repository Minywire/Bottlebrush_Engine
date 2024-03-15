//
// Created by Marco on 09/03/24.
//
#pragma once

#include "../BBScene/Scene.h"
#include <iostream>
#include <entt/entt.hpp>
/**
 * @class Entity
 * @brief A class which encapsulates an EnTT entity object. This class provides an interface for Entity objects to be used by scenes
 * @author Marco Garzon Lara
 */
class Entity
{
public:
    /**
     * Entity accessor operator ()
     * @return This entity
     * @author Marco Garzon Lara
     */
    explicit operator entt::entity () const;

    /**
     * Default Constructor
     */
    Entity();

    /**
     * Entity param constructor
     * @brief Assigns other entity to this entity
     * @param handle The entity to copy to this entity
     * @author Marco Garzon Lara
     */
    explicit Entity(entt::entity handle);

    /**
     * @brief Checks whether an entity in a registry has components
     * @tparam T The entity type
     * @param reg The specified registry to find the entity component in
     * @return All of the entities containing the specified components
     * @author Marco Garzon Lara
     */
    template<typename T>
    bool hasComponent(const entt::registry& reg);

    /**
     * @brief Adds a component to specified entities in specified registry
     * @tparam T The type of component to be added
     * @tparam Args The components to be added to the entity
     * @param reg The specified registry which has the entity to add the component to
     * @param args The specified component(s) to be added to the entity
     * @return A flag that confirms the emplacement of the component in the entity
     * @author Marco Garzon Lara
     */
    template<typename T, typename... Args>
    T& addComponent(entt::registry& reg, Args&&... args);

    /**
     * @brief grabs a component from an entity in a registry
     * @tparam T The type of component
     * @param reg The specified registry to grab component from
     * @return T The component associated with an entity
     * @author Marco Garzon Lara
     */
    template<typename T>
    const T& getComponent(const entt::registry& reg) const;

    /**
     * @brief removes a component for an entity in a specified registry
     * @tparam T The type of component
     * @param reg The specified registry to remove the specific component from
     * @author Marco Garzon Lara
     */
    template<typename T>
    void removeComponent(entt::registry& reg);

    /**
     * @brief Deletes an entity in the specified registry
     * @param reg The specified registry to delete this entity from
     */
    void deleteEntity(entt::registry & reg);

    /**
     * @brief Returns the entity in this instance
     * @return The entity in this class
     */
    const entt::entity& getEntity() const;

private:
    entt::entity entityHandle; //!> The entity wrapped by Bottlebrush's Entity interface

};


