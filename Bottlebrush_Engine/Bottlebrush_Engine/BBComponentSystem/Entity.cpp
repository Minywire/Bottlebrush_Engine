//
// Created by Marco on 09/03/24.
//

#include "Entity.h"

Entity::Entity()
{
    entityHandle = entt::null;
}

Entity::Entity(entt::entity handle) : entityHandle(handle)
{ }

Entity::operator entt::entity () const
{
    return entityHandle;
}

template<typename T>
bool Entity::hasComponent(const entt::registry& reg)
{
    return reg.any_of<T>(entityHandle);
}

template<typename T, typename... Args>
T& Entity::addComponent(entt::registry &reg, Args&&... args)
{
    if (hasComponent<T>())
    {
        std::cout << "Entity already has component." << std::endl;
    }
    return reg.emplace<T>(entityHandle, std::forward<Args>(args)...);
}

template<typename T>
const T& Entity::getComponent(const entt::registry& reg) const
{
    if (!hasComponent<T>())
    {
        std::cout << "No components found in entity" << std::endl;
    }
    return reg.get<T>(entityHandle);
}

template<typename T>
void Entity::removeComponent(entt::registry& reg)
{
    if (!hasComponent<T>()) {
        std::cout << "Entity has no components; Nothing to delete." << std::endl;
        return;
    }
    return reg.remove<T>(entityHandle);
}

const entt::entity& Entity::getEntity() const
{
    return entityHandle;
}

void Entity::deleteEntity(entt::registry & reg)
{
    reg.destroy(entityHandle);
}