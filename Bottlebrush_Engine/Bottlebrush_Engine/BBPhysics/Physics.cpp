#include "Physics.h"

bool Physics::created_ = false;
rp3d::PhysicsCommon Physics::common_;
rp3d::PhysicsWorld* Physics::world_ = nullptr;

void Physics::Create() {
  if (created_) return;
  world_ = common_.createPhysicsWorld();
  created_ = true;
}

void Physics::Delete() {
  if (!created_) return;
  common_.destroyPhysicsWorld(world_);
  created_ = false;
}

void Physics::Update(float delta) {
  if (!created_) return;
  world_->update(delta);
}

rp3d::PhysicsCommon& Physics::GetCommon() { return common_; }

rp3d::PhysicsWorld* Physics::GetWorld() { return world_; }

bool Physics::IsWorldCreated() { return created_; }
