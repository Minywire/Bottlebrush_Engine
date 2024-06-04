#ifndef BOTTLEBRUSH_ENGINE_PHYSICSMGR_H
#define BOTTLEBRUSH_ENGINE_PHYSICSMGR_H

#include <unordered_map>

#include "PhysicsBody.h"
#include "reactphysics3d/reactphysics3d.h"

class PhysicsMgr {
    using PhysicsCommn = rp3d::PhysicsCommon;
    using PhysicsWorld = rp3d::PhysicsWorld*;
    using Transform = rp3d::Transform;
    using Vec3 = rp3d::Vector3;

    inline static glm::vec3 kDefaultHalfExtents = {0.0f, 0.0f, 0.0f};
    inline static float kDefaultHeight = 0.0f;
    inline static glm::vec3 kDefaultPosition = {0.0f, 0.0f, 0.0f};
    inline static float kDefaultRadius = 0.0f;
    inline static glm::vec3 kDefaultRotation = {0.0f, 0.0f, 0.0f};
    inline static glm::vec3 kDefaultScale = {1.0f, 1.0f, 1.0f};
    inline static PhysicsBody::PhysicsBodyType kDefaultBodyType =
        PhysicsBody::PhysicsBodyType::kStatic;

   public:
    PhysicsMgr() = default;

    void CreateWorld();
    void DeleteWorld();

    uint32_t CreateBody(PhysicsBody::PhysicsBodyType type = kDefaultBodyType,
                        glm::vec3 position = kDefaultPosition,
                        glm::vec3 rotation = kDefaultRotation,
                        glm::vec3 scale = kDefaultScale);
    uint32_t CreateBody(const PhysicsBody& body);
    const PhysicsBody& ObtainBody(uint32_t index) const;
    uint32_t RemoveBody(uint32_t index);

    void CreateBoxCollider(uint32_t index,
                           const glm::vec3& half_extents = kDefaultHalfExtents);
    void CreateCapsuleCollider(uint32_t index, float radius = kDefaultRadius,
                               float height = kDefaultHeight);
    void CreateSphereCollider(uint32_t index, float radius = kDefaultRadius);

    void Update(float delta);

   private:
    PhysicsCommn common_;
    std::unordered_map<uint32_t, PhysicsBody> physics_bodies_;
    PhysicsWorld world_ = nullptr;
};

#endif  // BOTTLEBRUSH_ENGINE_PHYSICSMGR_H
