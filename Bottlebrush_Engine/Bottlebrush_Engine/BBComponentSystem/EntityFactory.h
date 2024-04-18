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
     * @return
     */
    Entity create_from_file(ECS &ecs, sol::state &lua_state, const std::filesystem::path &lua_file);

private:
    /**
     *
     * @param ecs
     * @param entity
     * @param table
     */
    void load_components(ECS &ecs, Entity &entity, const sol::table &table);

    /**
     *
     * @param entity
     * @param transform
     */
    void loadTransform(ECS& ecs, Entity &entity, const sol::table &transform);
};
