//
// Created by Marco Garzon Lara on 12/3/2024.
//

#include "Scene.h"
#include "../BBComponentSystem/Entity.h"
#include "../BBComponentSystem/Components.h"

Scene::Scene()
{ }

void Scene::DeleteEntity(Entity entity)
{
    //todo see if theres a bool version of this to confirm deletion
    entity.DeleteEntity(registry);
}

Entity Scene::CreateEntity()
{
    entt::entity handle = registry.create();

    Entity entity{ handle };
    entity.AddComponent<TransformComponent>(registry);
    entity.AddComponent<TagComponent>(registry);
    return entity;
}

Entity Scene::CreateEntity(std::string tag)
{
    entt::entity handle = registry.create();

    Entity entity{ handle };
    entity.AddComponent<TransformComponent>(registry);
    entity.AddComponent<TagComponent>(registry, tag);

    return entity;
}

template<typename... Components>
auto Scene::GetAllEntitiesWith() const
{
    return registry.view<Components...>();
}