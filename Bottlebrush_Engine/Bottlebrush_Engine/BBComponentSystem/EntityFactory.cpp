//
// Created by Marco on 07/04/24.
//

#include "EntityFactory.h"


Entity EntityFactory::create_from_file(ECS & ecs, sol::state & lua_state, const std::filesystem::path & lua_file)
{

    if(lua_file.extension() != ".lua") { throw std::runtime_error("Lua file is no lua file"); }


    lua_state.script_file(lua_file.string());

    auto entityTable = lua_state["Entity"];

    if(entityTable.valid())
    {
        Entity namedEntity = ecs.CreateEntity();
        load_components(ecs, namedEntity, entityTable);

        return namedEntity;
    }
}

void EntityFactory::load_components(ECS& ecs, Entity& entity, const sol::table& table)
{
    if(table["Transform"].valid())
    {
        loadTransform(ecs, entity, table["Transform"]);
    }
}

void EntityFactory::loadTransform(ECS& ecs, Entity& entity, const sol::table & transform)
{
    glm::vec3 pos = { transform["Position"]["x"],
                      transform["Position"]["y"],
                      transform["Position"]["z"] };

    glm::vec3 rot = { transform["Rotation"]["x"],
                      transform["Rotation"]["y"],
                      transform["Rotation"]["z"] };

    glm::vec3 scale = { transform["Scale"]["x"],
                      transform["Scale"]["y"],
                      transform["Scale"]["z"] };

    TransformComponent& transformComponent = entity.GetComponent<TransformComponent>(ecs.getReg());

    transformComponent.position = pos;
    transformComponent.rotation = rot;
    transformComponent.scale = scale;
}