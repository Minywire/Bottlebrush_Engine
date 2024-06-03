#ifndef BOTTLEBRUSH_ENGINE_PHYSICS_H
#define BOTTLEBRUSH_ENGINE_PHYSICS_H

#include "reactphysics3d/reactphysics3d.h"

class Physics {
   public:
    using PhysicsCommon = rp3d::PhysicsCommon;
    using PhysicsWorld = rp3d::PhysicsWorld*;

    ~Physics();

    static Physics& GetInstance();

    void Update(float delta);

   private:
    Physics();

    void CreateWorld();
    void DeleteWorld();

    PhysicsCommon common_;
    PhysicsWorld world_;
};

#endif  // BOTTLEBRUSH_ENGINE_PHYSICS_H
