//
// Created by Marco on 09/03/24.
//
#pragma once

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
    bool HasComponent(const entt::registry& reg)
    {
        return reg.any_of<T>(entity_handle);
    }

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
    T& AddComponent(entt::registry& reg, Args&&... args)
    {
        if (HasComponent<T>(reg))
        {
            std::cout << "Entity already has component." << std::endl;
        }
        return reg.emplace<T>(entity_handle, std::forward<Args>(args)...);
    }

    /**
     * @brief grabs a component from an entity in a registry
     * @tparam T The type of component
     * @param reg The specified registry to grab component from
     * @return T The component associated with an entity
     * @author Marco Garzon Lara
     */
    template<typename T>
    const T& GetComponent(const entt::registry& reg) const
    {
        if (!HasComponent<T>(reg))
        {
            std::cout << "No components found in entity" << std::endl;
        }
        return reg.get<T>(entity_handle);
    }

    /**
     *
     * @tparam T
     * @param reg
     * @return
     */
    template<typename T>
    T& GetComponent(entt::registry& reg)
    {
        if (!HasComponent<T>(reg))
        {
            std::cout << "No components found in entity" << std::endl;
        }
        return reg.get<T>(entity_handle);
    }

    /**
     * @brief removes a component for an entity in a specified registry
     * @tparam T The type of component
     * @param reg The specified registry to remove the specific component from
     * @author Marco Garzon Lara
     */
    template<typename T>
    void RemoveComponent(entt::registry& reg)
    {
        if (!HasComponent<T>(reg)) {
            std::cout << "Entity has no components; Nothing to delete." << std::endl;
            return;
        }
        return reg.remove<T>(entity_handle);
    }

    /**
     * @brief Deletes an entity in the specified registry
     * @param reg The specified registry to delete this entity from
     */
    void DeleteEntity(entt::registry & reg);


private:
    entt::entity entity_handle; //!> The entity wrapped by Bottlebrush's Entity interface

};



