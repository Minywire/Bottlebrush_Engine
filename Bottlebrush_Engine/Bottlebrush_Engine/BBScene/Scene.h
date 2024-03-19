//
// Created by Marco Garzon Lara on 12/3/2024.
//
#pragma once

#include <entt/entt.hpp>

class Entity;
/**
 * @class Scene
 * @brief The scene 'graph' for a game instance created in Bottlebrush Engine
 * @author Marco Garzon Lara
 */
class Scene
{
public:
    /**
     * @brief Deletes Entity from the scene and the game(with our Entity type)
     * @param entity The entity to be deleted
     * @author Marco Garzon Lara
    */
    void DeleteEntity(Entity entity);

    /**
     *@brief Default constructor.
     */
    Scene();

    /**
     * @brief Creates an Entity on the current scene.
     * @return entity The entity created in the scene
     * @author Marco Garzon Lara
     */
    Entity CreateEntity();

    /**
     * @brief Creates an entity with a tag.
     * @param tag The alias to be given to the entity
     * @return entity The entity created in the scene
     * @author Marco Garzon Lara
     */
    Entity CreateEntity(std::string tag);

    /**
     *@brief Gets all entities with the provided components.
     * @tparam components All of the existing components in the ECS
     * @return view The EnTT view containing all entities with any existing components
     * @author Marco Garzon Lara
     */
    template<typename... Components>
    auto GetAllEntitiesWith() const;

private:
    entt::registry registry; ///The registry for ECS management (basically a big array under the hood)
    //TODO: This Scene will need a camera, Assimp scene, Physics api scene, and our Lua system in the near future.
};
