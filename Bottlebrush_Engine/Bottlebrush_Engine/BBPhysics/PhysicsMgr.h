#ifndef BOTTLEBRUSH_ENGINE_PHYSICSMGR_H
#define BOTTLEBRUSH_ENGINE_PHYSICSMGR_H

#include <unordered_map>

#include "PhysicsBody.h"
#include "reactphysics3d/reactphysics3d.h"

class PhysicsMgr {
   public:
    using PhysicsCommon = rp3d::PhysicsCommon;
    using PhysicsWorld = rp3d::PhysicsWorld*;

    ~PhysicsMgr();

    static PhysicsMgr& GetInstance();

    const PhysicsBody& GetPhysicsBody(uint32_t index) const;
    void CreatePhysicsBody(PhysicsBody::PhysicsBodyType type =
                               PhysicsBody::PhysicsBodyType::kStatic,
                           glm::vec3 position = {0.0f, 0.0f, 0.0f},
                           glm::vec3 rotation = {0.0f, 0.0f, 0.0f},
                           glm::vec3 scale = {1.0f, 1.0f, 1.0f});

    void Update(float delta);

   private:
    PhysicsMgr();

    void CreateWorld();
    void DeleteWorld();

    std::unordered_map<uint32_t, PhysicsBody> physics_bodies_;
    PhysicsCommon common_;
    PhysicsWorld world_;
};

#endif  // BOTTLEBRUSH_ENGINE_PHYSICSMGR_H
