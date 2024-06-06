#include "Collider.h"

Collider::Collider(ColliderType type, const glm::vec3& centre, bool is_static) {
    type_ = type;
    is_static_ = is_static;
    centre_ = centre;
}

const glm::vec3& Collider::GetCentre() const { return centre_; }

Collider::ColliderType Collider::GetType() const { return type_; }

bool Collider::IsStatic() const { return is_static_; }

void Collider::SetCentre(const glm::vec3& centre) { centre_ = centre; }
