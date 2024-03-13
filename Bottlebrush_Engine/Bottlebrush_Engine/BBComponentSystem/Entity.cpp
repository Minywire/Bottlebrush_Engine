//
// Created by Marco on 09/03/24.
//

#include "Entity.h"

Entity::Entity()
{
    entityHandle = entt::null;
    parentScene = nullptr;
}

Entity::Entity(entt::entity handle, Scene* scene) : entityHandle(handle), parentScene(scene)
{ }

Entity::operator entt::entity () const
{
    return entityHandle;
}

template<typename T>
bool Entity::hasComponent()
{
    return parentScene->registry.any_of<T>(entityHandle);
}

template<typename T, typename... Args>
T& Entity::addComponent(Args&&... args)
{
    if (hasComponent<T>())
    {
        std::cout << "Entity already has component." << std::endl;
    }
    return parentScene->registry.emplace<T>(entityHandle, std::forward<Args>(args)...);
}

template<typename T>
const T& Entity::getComponent() const
{
    if (!hasComponent<T>())
    {
        std::cout << "No components found in entity" << std::endl;
    }
    return parentScene->registry.get<T>(entityHandle);
}

template<typename T>
void Entity::removeComponent()
{
    if (!hasComponent<T>()) {
        std::cout << "Entity has no components; Nothing to delete." << std::endl;
        return;
    }
    return parentScene->registry.remove<T>(entityHandle);
}