#ifndef BOTTLEBRUSH_ENGINE_PHYSICSBODY_H
#define BOTTLEBRUSH_ENGINE_PHYSICSBODY_H

#include "glm/glm.hpp"
#include "reactphysics3d/reactphysics3d.h"

class PhysicsBody {
    using Vec3 = rp3d::Vector3;
    using Quat = rp3d::Quaternion;
    using Transform = rp3d::Transform;

    inline static glm::vec3 kDefaultHalfExtents = {0.0f, 0.0f, 0.0f};
    inline static float kDefaultHeight = 0.0f;
    inline static glm::vec3 kDefaultPosition = {0.0f, 0.0f, 0.0f};
    inline static float kDefaultRadius = 0.0f;
    inline static glm::vec3 kDefaultRotation = {0.0f, 0.0f, 0.0f};
    inline static glm::vec3 kDefaultScale = {1.0f, 1.0f, 1.0f};

   public:
    using BoxShape = rp3d::BoxShape*;
    using CapsuleShape = rp3d::CapsuleShape*;
    using Collider = rp3d::Collider*;
    using RigidBody = rp3d::RigidBody*;
    using SphereShape = rp3d::SphereShape*;

    enum ColliderType { kBox, kCapsule, kSphere };

    enum PhysicsBodyType { kStatic, kKinematic, kDynamic };

    explicit PhysicsBody(PhysicsBodyType type = kStatic,
                         glm::vec3 position = kDefaultPosition,
                         glm::vec3 rotation = kDefaultRotation,
                         glm::vec3 scale = kDefaultScale);

    [[nodiscard]] const Collider& GetCollider() const;
    [[nodiscard]] const glm::vec3& GetPosition() const;
    [[nodiscard]] const RigidBody& GetRigidBody() const;
    [[nodiscard]] const glm::vec3& GetRotation() const;
    [[nodiscard]] const glm::vec3& GetScale() const;
    [[nodiscard]] PhysicsBodyType GetType() const;
    void SetCollider(const Collider& collider);
    void SetPosition(const glm::vec3& position);
    void SetRigidBody(const RigidBody& body);
    void SetRotation(const glm::vec3& rotation);
    void SetScale(const glm::vec3& scale);
    void SetType(PhysicsBodyType type);

   private:
    void SetRigidBodyTrns();
    void SetRigidBodyType();

    RigidBody body_ = nullptr;
    Collider collider_ = nullptr;
    glm::vec3 position_;
    glm::vec3 rotation_;
    glm::vec3 scale_;
    PhysicsBodyType type_;
};

#endif  // BOTTLEBRUSH_ENGINE_PHYSICSBODY_H
