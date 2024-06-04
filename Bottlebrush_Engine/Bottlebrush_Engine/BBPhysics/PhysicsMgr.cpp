#include "PhysicsMgr.h"

void PhysicsMgr::CreateWorld() { world_ = common_.createPhysicsWorld(); }

void PhysicsMgr::DeleteWorld() { common_.destroyPhysicsWorld(world_); }

uint32_t PhysicsMgr::CreateBody(PhysicsBody::PhysicsBodyType type,
                                glm::vec3 position, glm::vec3 rotation,
                                glm::vec3 scale) {
    auto p = rp3d::Vector3(position.x, position.y, position.z);
    auto o = rp3d::Quaternion(rotation.x, rotation.y, rotation.z, 1.0f);
    auto t = rp3d::Transform(p, o);
    PhysicsBody::RigidBody rigid_body = world_->createRigidBody(t);

    // Create a physics body and set its rigid body so that the physics body can
    // manage its own data
    PhysicsBody physics_body(type, position, rotation, scale);
    physics_body.SetRigidBody(rigid_body);

    // Put the physics body in the map using its physics world / entity index as
    // a key so that the manager can reference it and manage it
    uint32_t index = rigid_body->getEntity().getIndex();
    physics_bodies_.insert(std::make_pair(index, physics_body));

    return index;
}

uint32_t PhysicsMgr::CreateBody(PhysicsBody& body) {
    auto position = body.GetPosition();
    auto rotation = body.GetRotation();
    auto p = rp3d::Vector3(position.x, position.y, position.z);
    auto o = rp3d::Quaternion(rotation.x, rotation.y, rotation.z, 1.0f);
    auto t = rp3d::Transform(p, o);
    PhysicsBody::RigidBody rigid_body = world_->createRigidBody(t);

    // Create a physics body and set its rigid body so that the physics body can
    // manage its own data
    body.SetRigidBody(rigid_body);

    // Put the physics body in the map using its physics world / entity index as
    // a key so that the manager can reference it and manage it
    uint32_t index = rigid_body->getEntity().getIndex();
    physics_bodies_.insert(std::make_pair(index, body));

    return index;
}

const PhysicsBody& PhysicsMgr::ObtainBody(uint32_t index) const {
    return physics_bodies_.at(index);
}

uint32_t PhysicsMgr::RemoveBody(uint32_t index) {
    // Destroy the rigid body in the RP3D physics world and erase it from the
    // map to ensure we are cleaning up after ourselves nice and proper
    world_->destroyRigidBody(physics_bodies_.at(index).GetRigidBody());
    return physics_bodies_.erase(index);
}

void PhysicsMgr::CreateBoxCollider(uint32_t index,
                                   const glm::vec3& half_extents) {
    auto e = Vec3(half_extents.x, half_extents.y, half_extents.z);
    auto t = Transform::identity();

    // Add the shape to the RP3D physics common so that its memory may be
    // managed and set the collider on the rigid body so that it is attached
    PhysicsBody::BoxShape shape = common_.createBoxShape(e);
    physics_bodies_.at(index).SetCollider(shape, t);
}

void PhysicsMgr::CreateCapsuleCollider(uint32_t index, float radius,
                                       float height) {
    auto t = Transform::identity();

    // Add the shape to the RP3D physics common so that its memory may be
    // managed and set the collider on the rigid body so that it is attached
    PhysicsBody::CapsuleShape shape =
        common_.createCapsuleShape(radius, height);
    physics_bodies_.at(index).SetCollider(shape, t);
}

void PhysicsMgr::CreateSphereCollider(uint32_t index, float radius) {
    auto t = Transform::identity();

    // Add the shape to the RP3D physics common so that its memory may be
    // managed and set the collider on the rigid body so that it is attached
    PhysicsBody::SphereShape shape = common_.createSphereShape(radius);
    physics_bodies_.at(index).SetCollider(shape, t);
}

void PhysicsMgr::Update(float delta) { world_->update(delta); }
