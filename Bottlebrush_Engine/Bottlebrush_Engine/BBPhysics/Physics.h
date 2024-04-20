#ifndef BOTTLEBRUSH_ENGINE_PHYSICS_H
#define BOTTLEBRUSH_ENGINE_PHYSICS_H

#include "reactphysics3d/reactphysics3d.h"

class Physics {
 public:
  static void Create();
  static void Delete();
  static void Update(float delta);
  static rp3d::PhysicsCommon& GetCommon();
  static rp3d::PhysicsWorld* GetWorld();
  static bool IsWorldCreated();

 private:
  static bool created_;
  static rp3d::PhysicsCommon common_;
  static rp3d::PhysicsWorld* world_;
};

#endif  // BOTTLEBRUSH_ENGINE_PHYSICS_H
