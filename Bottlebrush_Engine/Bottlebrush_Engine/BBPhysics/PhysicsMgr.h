#ifndef BOTTLEBRUSH_ENGINE_PHYSICSMGR_H
#define BOTTLEBRUSH_ENGINE_PHYSICSMGR_H

#include "reactphysics3d/reactphysics3d.h"

class PhysicsMgr {
   public:
    using PhysicsCommon = rp3d::PhysicsCommon;
    using PhysicsWorld = rp3d::PhysicsWorld*;

    ~PhysicsMgr();

    static PhysicsMgr& GetInstance();

    void Update(float delta);

   private:
    PhysicsMgr();

    void CreateWorld();
    void DeleteWorld();

    PhysicsCommon common_;
    PhysicsWorld world_;
};

#endif  // BOTTLEBRUSH_ENGINE_PHYSICSMGR_H
