//
// Created by Marco on 09/03/24.
//

#include "Entity.h"
#include "Components.h"

Entity::Entity()
{
    entity_handle = entt::null;
}

Entity::Entity(entt::entity handle) : entity_handle(handle)
{ }

Entity::operator entt::entity () const
{
    return entity_handle;
}

void Entity::DeleteEntity(entt::registry & reg)
{
    reg.destroy(entity_handle);
}