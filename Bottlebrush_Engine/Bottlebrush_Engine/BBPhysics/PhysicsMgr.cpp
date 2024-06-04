#include "PhysicsMgr.h"

PhysicsMgr::~PhysicsMgr() { DeleteWorld(); }

PhysicsMgr& PhysicsMgr::GetInstance() {
    static PhysicsMgr instance_;
    return instance_;
}

const PhysicsBody& PhysicsMgr::GetPhysicsBody(uint32_t index) const {
    return physics_bodies_.at(index);
}

void PhysicsMgr::SetPhysicsBody(PhysicsBody::PhysicsBodyType type,
                                glm::vec3 position, glm::vec3 rotation,
                                glm::vec3 scale) {
    auto p = rp3d::Vector3(position.x, position.y, position.z);
    auto o = rp3d::Quaternion::identity();
    auto t = rp3d::Transform(p, o);
    PhysicsBody::RigidBody rigid_body = world_->createRigidBody(t);

    // Create a physics body and set its rigid body so that the physics body can
    // manage its own data
    PhysicsBody physics_body(type, position, rotation, scale);
    physics_body.SetRigidBody(rigid_body);

    // Put the physics body in the map using its physics world / entity index as
    // a key so that the manager can reference it and manage it
    uint32_t index = rigid_body->getEntity().getIndex();
    physics_bodies_[index] = physics_body;
}

void PhysicsMgr::Update(float delta) { world_->update(delta); }

PhysicsMgr::PhysicsMgr() { CreateWorld(); }

void PhysicsMgr::CreateWorld() { world_ = common_.createPhysicsWorld(); }

void PhysicsMgr::DeleteWorld() { common_.destroyPhysicsWorld(world_); }
