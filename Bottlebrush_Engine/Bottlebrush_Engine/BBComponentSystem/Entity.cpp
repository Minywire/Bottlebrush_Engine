//
// Created by Marco on 09/03/24.
//

#include "Entity.h"

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

template<typename T>
bool Entity::HasComponent(const entt::registry& reg)
{
    return reg.any_of<T>(entity_handle);
}

template<typename T, typename... Args>
T& Entity::AddComponent(entt::registry &reg, Args&&... args)
{
    if (hasComponent<T>())
    {
        std::cout << "Entity already has component." << std::endl;
    }
    return reg.emplace<T>(entity_handle, std::forward<Args>(args)...);
}

template<typename T>
const T& Entity::GetComponent(const entt::registry& reg) const
{
    if (!hasComponent<T>())
    {
        std::cout << "No components found in entity" << std::endl;
    }
    return reg.get<T>(entity_handle);
}

template<typename T>
void Entity::RemoveComponent(entt::registry& reg)
{
    if (!hasComponent<T>()) {
        std::cout << "Entity has no components; Nothing to delete." << std::endl;
        return;
    }
    return reg.remove<T>(entity_handle);
}

void Entity::DeleteEntity(entt::registry & reg)
{
    reg.destroy(entity_handle);
}