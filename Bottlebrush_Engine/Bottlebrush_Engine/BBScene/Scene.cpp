//
// Created by Marco Garzon Lara on 12/3/2024.
//

#include "Scene.h"
#include "../BBComponentSystem/Entity.h"
#include "../BBComponentSystem/Components.h"

Scene::Scene()
{ }

void Scene::deleteEntity(entt::entity entity)
{
    //todo see if theres a bool version of this to confirm deletion
    registry.destroy(entity);
}

Entity Scene::createEntity()
{
    entt::entity handle = registry.create();

    Entity entity{ handle };
    entity.addComponent<TransformComponent>(registry);
    entity.addComponent<TagComponent>(registry);
    return entity;
}

Entity Scene::createEntity(std::string tag)
{
    entt::entity handle = registry.create();

    Entity entity{ handle };
    entity.addComponent<TransformComponent>(registry);
    entity.addComponent<TagComponent>(registry, tag);

    return entity;
}

template<typename... Components>
auto Scene::GetAllEntitiesWith() const
{
    return registry.view<Components...>();
}