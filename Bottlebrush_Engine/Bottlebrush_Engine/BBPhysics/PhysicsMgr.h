#ifndef BOTTLEBRUSH_ENGINE_PHYSICSMGR_H
#define BOTTLEBRUSH_ENGINE_PHYSICSMGR_H

#include <unordered_map>

#include "PhysicsBody.h"
#include "reactphysics3d/reactphysics3d.h"

class PhysicsMgr {
    using PhysicsCommn = rp3d::PhysicsCommon;
    using PhysicsWorld = rp3d::PhysicsWorld*;

    inline static glm::vec3 kDefaultPosition = {0.0f, 0.0f, 0.0f};
    inline static glm::vec3 kDefaultRotation = {0.0f, 0.0f, 0.0f};
    inline static glm::vec3 kDefaultScale = {1.0f, 1.0f, 1.0f};
    inline static PhysicsBody::PhysicsBodyType kDefaultType =
        PhysicsBody::PhysicsBodyType::kStatic;

   public:
    static PhysicsMgr& GetInstance();

    uint32_t CreateBody(PhysicsBody::PhysicsBodyType type = kDefaultType,
                        glm::vec3 position = kDefaultPosition,
                        glm::vec3 rotation = kDefaultRotation,
                        glm::vec3 scale = kDefaultScale);
    void CreateWorld();
    void DeleteWorld();
    const PhysicsBody& ObtainBody(uint32_t index) const;
    uint32_t RemoveBody(uint32_t index);
    void Update(float delta);

    // TODO: DELETE THIS, IT IS FOR TESTING
    rp3d::PhysicsWorld* GetWorld() { return world_; }

   private:
    PhysicsMgr() = default;

    PhysicsCommn common_;
    std::unordered_map<uint32_t, PhysicsBody> physics_bodies_;
    PhysicsWorld world_ = nullptr;
};

#endif  // BOTTLEBRUSH_ENGINE_PHYSICSMGR_H
