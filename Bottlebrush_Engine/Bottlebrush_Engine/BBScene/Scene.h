//
// Created by Marco Garzon Lara on 12/3/2024.
//
#pragma once

#include <entt/entt.hpp>

class Entity;

class Scene
{
public:
    /**
	 * @brief Deletes Entity from the scene and the game
	 * @param entity
	*/
    void deleteEntity(Entity entity);
    /**
     * @brief Deletes Entity from the scene and the game( a stupid dumb dumb version cause sometimes we still deal with entt i hate groups)
     * @param entity
    */
    void deleteEntity(entt::entity entity);
    /**
     *@brief Default constructor.
     *
     */
    Scene();
    /**
     * @brief Creates an Entity on the current scene.
     *
     * \return Entity
     */
    Entity createEntity();
    /**
     * @brief Creates an entity with a tag.
     *
     * \param tag
     * \return
     */
    Entity createEntity(std::string tag);
    /**
     *@brief Gets all entities with the provided components.
     * @tparam components
     * \return
     */
    template<typename... Components>
    auto GetAllEntitiesWith() const;

private:
    entt::registry registry; ///The registry for ECS management (basically a big array under the hood)
    friend class Entity;
    //TODO: This Scene will need a camera, Assimp scene, Physics api scene, and our Lua system in the near future.
};
