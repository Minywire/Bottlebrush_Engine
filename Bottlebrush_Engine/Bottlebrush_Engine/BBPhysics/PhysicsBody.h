#ifndef BOTTLEBRUSH_ENGINE_PHYSICSBODY_H
#define BOTTLEBRUSH_ENGINE_PHYSICSBODY_H

#include "glm/glm.hpp"
#include "reactphysics3d/reactphysics3d.h"

class PhysicsBody {
    inline static glm::vec3 kDefaultPosition = {0.0f, 0.0f, 0.0f};
    inline static glm::vec3 kDefaultRotation = {0.0f, 0.0f, 0.0f};
    inline static glm::vec3 kDefaultScale = {1.0f, 1.0f, 1.0f};

   public:
    using RigidBody = rp3d::RigidBody*;

    enum PhysicsBodyType { kStatic, kKinematic, kDynamic };

    explicit PhysicsBody(PhysicsBodyType type = kStatic,
                         glm::vec3 position = kDefaultPosition,
                         glm::vec3 rotation = kDefaultRotation,
                         glm::vec3 scale = kDefaultScale);

    [[nodiscard]] const glm::vec3& GetPosition() const;
    [[nodiscard]] RigidBody GetRigidBody() const;
    [[nodiscard]] const glm::vec3& GetRotation() const;
    [[nodiscard]] const glm::vec3& GetScale() const;
    [[nodiscard]] PhysicsBodyType GetType() const;
    void SetPosition(const glm::vec3& position);
    void SetRigidBody(RigidBody body);
    void SetRotation(const glm::vec3& rotation);
    void SetScale(const glm::vec3& scale);
    void SetType(PhysicsBodyType type);

   private:
    void SetRigidBodyTrns();
    void SetRigidBodyType();

    RigidBody body_;
    glm::vec3 position_;
    glm::vec3 rotation_;
    glm::vec3 scale_;
    PhysicsBodyType type_;
};

#endif  // BOTTLEBRUSH_ENGINE_PHYSICSBODY_H
