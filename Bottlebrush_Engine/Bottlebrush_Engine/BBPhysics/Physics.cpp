#include "Physics.h"

Physics::~Physics() { DeleteWorld(); }

Physics& Physics::GetInstance() {
    static Physics instance_;
    return instance_;
}

void Physics::Update(float delta) { world_->update(delta); }

Physics::Physics() { CreateWorld(); }

void Physics::CreateWorld() { world_ = common_.createPhysicsWorld(); }

void Physics::DeleteWorld() { common_.destroyPhysicsWorld(world_); }
