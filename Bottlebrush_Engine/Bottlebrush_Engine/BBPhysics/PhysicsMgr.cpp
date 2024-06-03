#include "PhysicsMgr.h"

PhysicsMgr::~PhysicsMgr() { DeleteWorld(); }

PhysicsMgr& PhysicsMgr::GetInstance() {
    static PhysicsMgr instance_;
    return instance_;
}

void PhysicsMgr::Update(float delta) { world_->update(delta); }

PhysicsMgr::PhysicsMgr() { CreateWorld(); }

void PhysicsMgr::CreateWorld() { world_ = common_.createPhysicsWorld(); }

void PhysicsMgr::DeleteWorld() { common_.destroyPhysicsWorld(world_); }
