//
// Created by Marco on 07/04/24.
//

#include "ECS.h"

void ECS::DeleteEntity(Entity entity)
{
    //todo see if theres a bool version of this to confirm deletion
    entity.DeleteEntity(registry);
}

Entity ECS::CreateEntity()
{
    entt::entity handle = registry.create();

    Entity entity{ handle };
    entity.AddComponent<TransformComponent>(registry);
    entity.AddComponent<TagComponent>(registry);
    return entity;
}

Entity ECS::CreateEntity(std::string tag)
{
    entt::entity handle = registry.create();

    Entity entity{ handle };
    entity.AddComponent<TransformComponent>(registry);
    entity.AddComponent<TagComponent>(registry, tag);

    return entity;
}

template<typename... Components>
auto ECS::GetAllEntitiesWith() const
{
    return registry.view<Components...>();
}