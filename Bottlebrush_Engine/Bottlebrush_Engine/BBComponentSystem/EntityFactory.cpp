//
// Created by Marco on 07/04/24.
//

#include "EntityFactory.h"


Entity EntityFactory::create_from_file(ECS & ecs, sol::state & lua_state, const std::filesystem::path & lua_file)
{

    if(lua_file.extension() != ".lua") { throw std::runtime_error("Lua file is no lua file"); }

    lua_state.script_file(lua_file.string());

    Entity namedEntity;

    auto entityTable = lua_state["Entity"];

    if(entityTable.valid())
    {
        namedEntity = ecs.CreateEntity();
        load_components(ecs, namedEntity, entityTable);

        return namedEntity;
    }
    return namedEntity;
}

void EntityFactory::load_components(ECS& ecs, Entity& entity, const sol::table& table)
{
    if(table["Transform"].valid())
    {
        loadTransform(ecs, entity, table["Transform"]);
    }
    if(table["Model"].valid())
    {
        loadModel(ecs, entity, table["Model"]);
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

    TransformComponent& transformComponent = entity.GetComponent<TransformComponent>(ecs.getReg()); //Transform components exist by default so we get here.

    transformComponent.position = pos;
    transformComponent.rotation = rot;
    transformComponent.scale = scale;
}

void EntityFactory::loadModel(ECS &ecs, Entity &entity, const sol::table &model)
{
    std::string model_location = model["ModelPath"];

    std::cout << model_location << "\n";

    ModelComponent& modelComponent = entity.AddComponent<ModelComponent>(ecs.getReg()); //add model component to entity.

    modelComponent.model_path = model_location;
}