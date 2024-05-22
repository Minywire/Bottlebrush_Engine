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

Entity EntityFactory::create_from_file(ECS & ecs, sol::state & lua_state, const std::filesystem::path & lua_file, float xPos, float yPos, float zPos)
{

    if(lua_file.extension() != ".lua") { throw std::runtime_error("Lua file is no lua file"); }

    lua_state.script_file(lua_file.string());

    Entity namedEntity;

    auto entityTable = lua_state["Entity"];

    if(entityTable.valid())
    {
        namedEntity = ecs.CreateEntity();
        load_components(ecs, namedEntity, entityTable, xPos, yPos, zPos);

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
    if(table["AI"].valid())
    {
        loadAIController(ecs, entity, table["AI"]);
    }
}

void EntityFactory::load_components(ECS& ecs, Entity& entity, const sol::table& table, float xPos, float yPos, float zPos)
{
    if(table["Transform"].valid())
    {
        loadTransform(ecs, entity, table["Transform"], xPos, yPos, zPos);
    }
    if(table["Model"].valid())
    {
        loadModel(ecs, entity, table["Model"]);
    }
    if(table["AI"].valid())
    {
        loadAIController(ecs, entity, table["AI"]);
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

void EntityFactory::loadTransform(ECS& ecs, Entity& entity, const sol::table & transform, float xPos, float yPos, float zPos)
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

    glm::vec3 appliedTransform = {xPos, yPos, zPos};
    glm::vec finalTransform = pos + appliedTransform;

    transformComponent.position = finalTransform;
    transformComponent.rotation = rot;
    transformComponent.scale = scale;
}

void EntityFactory::loadModel(ECS &ecs, Entity &entity, const sol::table &model)
{
    std::string model_location = model["ModelPath"];
    std::string material_location = model["MaterialPath"];

    ModelComponent& modelComponent = entity.AddComponent<ModelComponent>(ecs.getReg()); //add model component to entity.

    modelComponent.model_path = model_location;
    modelComponent.material_path = material_location;
}

void EntityFactory::loadAIController(ECS& ecs, Entity& entity, const sol::table& ai)
{
    std::string statesPath = ai["StatesPath"];
    std::string initialState = ai["InitialState"];

    AIControllerComponent& aicComponent = entity.AddComponent<AIControllerComponent>(ecs.getReg(), statesPath, initialState); // add an AI controller to entity

    std::cout << "Loaded AI component" << std::endl; //@Debug Line, to be removed
}
