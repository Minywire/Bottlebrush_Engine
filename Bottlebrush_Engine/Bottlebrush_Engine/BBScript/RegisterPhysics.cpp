#include <RegisterPhysics.h>

void PhysicsScripts::registerPhysicsType(sol::state& lua_state)
{
    lua_state.new_enum<PhysicsBody::PhysicsBodyType>("BodyType", {
        {"kStatic", PhysicsBody::PhysicsBodyType::kStatic}, 
        {"kKinematic", PhysicsBody::PhysicsBodyType::kKinematic},
        {"kDynamic", PhysicsBody::PhysicsBodyType::kDynamic},
    });
}