#ifndef BOTTLEBRUSH_ENGINE_COLLIDER_H
#define BOTTLEBRUSH_ENGINE_COLLIDER_H

#include "glm/glm.hpp"

class Collider {
   public:
    enum ColliderType {
        kColliderNone = -1,
        kColliderBox,
        kColliderCapsule,
        kColliderSphere
    };

    Collider() = default;
    Collider(ColliderType type, const glm::vec3& centre, bool is_static);

    virtual ~Collider() = default;

    [[nodiscard]] const glm::vec3& GetCentre() const;
    [[nodiscard]] ColliderType GetType() const;
    [[nodiscard]] bool IsStatic() const;
    void SetCentre(const glm::vec3& centre);

   private:
    glm::vec3 centre_ = {};
    bool is_static_ = true;
    ColliderType type_ = kColliderNone;
};

#endif  // BOTTLEBRUSH_ENGINE_COLLIDER_H
