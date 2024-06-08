//
// Created by Marco on 07/04/24.
//
#pragma once

#include <filesystem>

#include <string>
#include <sol/sol.hpp>
#include <ECS.h>
#include <BBResourceManager.hpp>

#include "CollisionMgr.h"

class EntityFactory {
public:
    /**
     * @brief Creates an entity from a lua file
     * @param ecs The component system object containing the specified registry to create the entity on
     * @param lua_file The specified Lua file to create the entity from
     * @param resources The resource interface containing all resource containers
     * @return created entity
     */
    Entity create_from_file(ECS &ecs, sol::state &lua_state, const std::filesystem::path &lua_file, BBResourceManager & resources);

    /**
     *
     * @param ecs The registry from which to create entities from
     * @param lua_state the lua state
     * @param lua_file the lua file to load from
     * @param resources The resource interface containing all resource containers
     * @param xPos x translate
     * @param yPos y translate
     * @param zPos z translate
     * @return created entity
     */
    Entity create_from_file(ECS &ecs, sol::state &lua_state, const std::filesystem::path &lua_file, BBResourceManager & resources, float xPos, float yPos, float zPos);

private:
    /**
     *
     * @param ecs The ecs to load components from
     * @param entity entity to add components to
     * @param table tables
     * @param resources The resource interface containing all resource containers
     */
    void load_components(ECS &ecs, Entity &entity, const sol::table &table, BBResourceManager & resources);

    /**
     * @param ecs  The ecs to load components from
     * @param entity the entity to attach components to
     * @param table the sol table to compare
     * @param resources The resource interface containing all resource containers
     * @param xPos x translate
     * @param yPos y translate
     * @param zPos z translate
     */
    void load_components(ECS &ecs, Entity &entity, const sol::table &table, BBResourceManager & resources, float xPos, float yPos, float zPos);

    /**
     *
     * @param entity the entity to load the transform component from
     * @param transform the transform sol table to compare against
     */
    void loadTransform(ECS& ecs, Entity &entity, const sol::table &transform);

    /**
     *
     * @param ecs the ecs to load the transform component from
     * @param entity the entity to attach the component to
     * @param transform the transform table to compare agains
     * @param xPos x translate
     * @param yPos y translate
     * @param zPos z translate
     */
    void loadTransform(ECS& ecs, Entity &entity, const sol::table &transform, float xPos, float yPos, float zPos);

    /**
     *
     * @param ecs the ecs registry to load model component from
     * @param entity the entity to attach to
     * @param model the model table to compare against
     * @param resources The resource interface containing all resource containers
     */
    void loadModel(ECS& ecs, Entity &entity, const sol::table &model, BBResourceManager & resources);

    /**
     *
     * @param ecs the ecs registry to load model component from
     * @param entity the entity to attach to
     * @param ai the ai table to compare against
     * @param resources The resource interface containing all resource containers
     */
    void loadAIController(ECS &ecs, Entity &entity, const sol::table &ai, BBResourceManager& resources);

    /**
    *  @param ecs the ecs registry to load model component from
     * @param entity the entity to attach to
     * @param terrain the terrain table to compare against
     * @param resources The resource interface containing all resource containers
    */
    void loadTerrain(ECS &ecs, Entity &entity, const sol::table &terrain, BBResourceManager & resources);

    /**
     *  @param ecs the ecs registry to load model component from
     * @param entity the entity to attach to
     * @param MD2 the MD2 table to compare against
     * @param resources The resource interface containing all resource containers
     */
    void loadMD2(ECS &ecs, Entity &entity, const sol::table &MD2, BBResourceManager & resources);

    /**
     * @param ecs the ecs registry to load model component from
     * @param entity the entity to attach to
     * @param Collider the Collider table to compare against
     */
    void LoadCollider(ECS &ecs, Entity &entity, const sol::table &Collider);
};
