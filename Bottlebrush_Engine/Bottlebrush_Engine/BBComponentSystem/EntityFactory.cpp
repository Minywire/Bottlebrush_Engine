//
// Created by Marco on 07/04/24.
//

#include "EntityFactory.h"


Entity EntityFactory::create_from_file(ECS & ecs, sol::state & lua_state, const std::filesystem::path & lua_file, BBResourceManager & resources, PhysicsMgr & physMgr)
{

    if(lua_file.extension() != ".lua") { throw std::runtime_error("Lua file is no lua file"); }

    lua_state.script_file(lua_file.string());

    Entity namedEntity;

    auto entityTable = lua_state["Entity"];

    if(entityTable.valid())
    {
        namedEntity = ecs.CreateEntity();
        load_components(ecs, namedEntity, entityTable,  resources, physMgr);

        return namedEntity;
    }
    return namedEntity;
}

Entity EntityFactory::create_from_file(ECS & ecs, sol::state & lua_state,  const std::filesystem::path & lua_file, BBResourceManager & resources, PhysicsMgr & physMgr, float xPos, float yPos, float zPos)
{

    if(lua_file.extension() != ".lua") { throw std::runtime_error("Lua file is no lua file"); }

    lua_state.script_file(lua_file.string());

    Entity namedEntity;

    auto entityTable = lua_state["Entity"];

    if(entityTable.valid())
    {
        namedEntity = ecs.CreateEntity();
        load_components(ecs, namedEntity, entityTable, resources, physMgr, xPos, yPos, zPos);

        return namedEntity;
    }
    return namedEntity;
}

void EntityFactory::load_components(ECS& ecs, Entity& entity, const sol::table& table, BBResourceManager & resources, PhysicsMgr & physMgr)
{
    if(table["Transform"].valid())
    {
        loadTransform(ecs, entity, table["Transform"]);
    }
    if(table["Model"].valid())
    {
        loadModel(ecs, entity, table["Model"], resources);
    }
    if(table["AI"].valid())
    {
        loadAIController(ecs, entity, table["AI"]);
    }
    if (table["Terrain"].valid()) 
    {
        loadTerrain(ecs, entity, table["Terrain"], resources);
    }
    if (table["MD2Model"].valid())
    {
        loadMD2(ecs, entity, table["MD2Model"], resources);
    }
    if (table["PhysicsBody"].valid())
    {
        loadPhysicsBody(ecs, entity, table["PhysicsBody"], physMgr);
    }
}

void EntityFactory::load_components(ECS& ecs, Entity& entity, const sol::table& table, BBResourceManager & resources, PhysicsMgr & physmgr, float xPos, float yPos, float zPos)
{
    if(table["Transform"].valid())
    {
        loadTransform(ecs, entity, table["Transform"], xPos, yPos, zPos);
    }
    if(table["Model"].valid())
    {
        loadModel(ecs, entity, table["Model"], resources);
    }
    if(table["AI"].valid())
    {
        loadAIController(ecs, entity, table["AI"]);
    }
    if (table["Terrain"].valid()) 
    {
        loadTerrain(ecs, entity, table["Terrain"], resources);
    }
    if (table["MD2Model"].valid()) 
    {
      loadMD2(ecs, entity, table["MD2Model"], resources);
    }
    if (table["PhysicsBody"].valid()) 
    {
        loadPhysicsBody(ecs, entity, table["PhysicsBody"], physmgr);
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

void EntityFactory::loadModel(ECS &ecs, Entity &entity, const sol::table &model, BBResourceManager & resources)
{
    std::string model_location = model["ModelPath"];
    std::string material_location = model["MaterialPath"];

    auto & modelMap = resources.getSceneModels();

    ModelComponent& modelComponent = entity.AddComponent<ModelComponent>(ecs.getReg(), model_location, material_location); //add model component to entity.

    if(!modelMap.contains(model_location))
    {
        modelMap.emplace(std::pair<std::string, std::unique_ptr<Model>>(model_location, GraphicsFactory<GraphicsAPI::OpenGL>::CreateModel(model_location, material_location)));
    }
}

void EntityFactory::loadAIController(ECS& ecs, Entity& entity, const sol::table& ai)
{
    std::string statesPath = ai["StatesPath"];
    std::string initialState = ai["InitialState"];

    AIControllerComponent& aic = entity.AddComponent<AIControllerComponent>(ecs.getReg(), statesPath, initialState, entity); // add an AI controller to entity
    if (aic.npc.GetFSM().GetStatePath().extension() != ".lua") {
        throw std::runtime_error("Lua file is no lua file");
    }

    // if NPC has waypoints add them
    if (ai["Waypoints"].valid()) {
        sol::table waypoints = ai["Waypoints"];
        for (const auto& [name, waypoint] : waypoints) {
            aic.npc.AddWaypoint(waypoint.as<glm::vec2>());
        }
    }

    std::cout << "Loaded AI component" << std::endl; //@Debug Line, to be removed
}

void EntityFactory::loadTerrain(ECS& ecs, Entity& entity, const sol::table& terrain, BBResourceManager & resources)
{
    const std::string terrainPath = terrain["TerrainPath"];
    const std::string terrainTexturePath = terrain["TerrainTexturePath"];
    auto & terrainMap = resources.getSceneTerrain();

    entity.AddComponent<TerrainComponent>(ecs.getReg(), terrainPath, terrainTexturePath); //add terrain component to entity.

    const auto& terrainTransform = entity.GetComponent<TransformComponent>(ecs.getReg());

    if (!terrainMap.contains(terrainPath))
    {
        terrainMap.emplace(std::pair<std::string, Terrain>(terrainPath, Terrain(terrainPath, terrainTexturePath, terrainTransform.scale, terrainTransform.position)));
    }
}

void EntityFactory::loadMD2(ECS & ecs, Entity & entity, const sol::table & MD2, BBResourceManager & resources)
{
    const std::string MD2Path = MD2["ModelPath"];
    const std::string MD2TexPath = MD2["TexturePath"];
    auto& MD2map = resources.getSceneMD2Models();

    entity.AddComponent<MD2Component>(ecs.getReg(), MD2Path, MD2TexPath);

    if (!MD2map.contains(MD2Path))
    {
        MD2map.emplace(std::pair<std::string, BBMD2>(MD2Path, BBMD2(MD2Path, MD2TexPath)));
    }
}

void EntityFactory::loadPhysicsBody(ECS & ecs, Entity & entity, const sol::table & PhysBody, PhysicsMgr & physicsManager)
{
    const PhysicsBody::PhysicsBodyType type = PhysBody["BodyType"];

    entity.AddComponent<PhysicsBodyComponent>(ecs.getReg());

    const auto & transform = entity.GetComponent<TransformComponent>(ecs.getReg());
    auto & currentPhysBody = entity.GetComponent<PhysicsBodyComponent>(ecs.getReg());

    physicsManager.CreateBody(currentPhysBody.physics_body);

    currentPhysBody.physics_body.SetType(type);
    currentPhysBody.physics_body.SetPosition(transform.position);
    currentPhysBody.physics_body.SetRotation(transform.rotation);
    currentPhysBody.physics_body.SetScale(transform.scale);
}