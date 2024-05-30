//
// Created by Marco on 07/04/24.
//
#pragma once

#include <filesystem>

#include <string>
#include <sol/sol.hpp>
#include <ECS.h>

class EntityFactory {
public:
    /**
     * @brief Creates an entity from a lua file
     * @param ecs The component system object containing the specified registry to create the entity on
     * @param lua_file The specified Lua file to create the entity from
     * @return created entity
     */
    Entity create_from_file(ECS &ecs, sol::state &lua_state, const std::filesystem::path &lua_file);

    /**
     *
     * @param ecs The registry from which to create entities from
     * @param lua_state the lua state
     * @param lua_file the lua file to load from
     * @param xPos x translate
     * @param yPos y translate
     * @param zPos z translate
     * @return created entity
     */
    Entity create_from_file(ECS &ecs, sol::state &lua_state, const std::filesystem::path &lua_file, float xPos, float yPos, float zPos);

private:
    /**
     *
     * @param ecs The ecs to load components from
     * @param entity entity to add components to
     * @param table tables
     */
    void load_components(ECS &ecs, Entity &entity, const sol::table &table);

    /**
     * @param ecs  The ecs to load components from
     * @param entity the entity to attach components to
     * @param table the sol table to compare
     * @param xPos x translate
     * @param yPos y translate
     * @param zPos z translate
     */
    void load_components(ECS &ecs, Entity &entity, const sol::table &table, float xPos, float yPos, float zPos);

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
     */
    void loadModel(ECS& ecs, Entity &entity, const sol::table &model);

    /**
     *
     * @param ecs the ecs registry to load model component from
     * @param entity the entity to attach to
     * @param ai the ai table to compare against
     */
    void loadAIController(ECS &ecs, Entity &entity, const sol::table &ai);

    /**
    *  @param ecs the ecs registry to load model component from
     * @param entity the entity to attach to
     * @param terrain the terrain table to compare against
    */
    void loadTerrain(ECS &ecs, Entity &entity, const sol::table &terrain);
};
