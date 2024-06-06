#include "CollisionMgr.h"

bool CollisionMgr::IsCollision(const std::unique_ptr<Collider>& a,
                               const std::unique_ptr<Collider>& b) {
    // If null, then no collision
    if (a == nullptr || b == nullptr) return false;
    // If objects are the same, then no collision (no self collision)
    if (a == b) return false;

    const auto a_type = a->GetType(), b_type = b->GetType();

    if (a_type == Collider::ColliderType::kColliderBox &&
        b_type == Collider::ColliderType::kColliderBox)
        return IsCollision(dynamic_cast<BBox*>(a.get()),
                           dynamic_cast<BBox*>(b.get()));

    return false;
}

bool CollisionMgr::IsCollision(const BBox* a, const BBox* b) {
    // If distance from A to B in x is greater than the combined radius in x,
    // then no collision
    if (abs(a->GetCentre().x - b->GetCentre().x) >
        (a->GetHalfExtents().at(0) + b->GetHalfExtents().at(0)))
        return false;

    // If distance from A to B in y is greater than the combined radius in y,
    // then no collision
    if (abs(a->GetCentre().y - b->GetCentre().y) >
        (a->GetHalfExtents().at(1) + b->GetHalfExtents().at(1)))
        return false;

    // If distance from A to B in z is greater than the combined radius in z,
    // then no collision
    if (abs(a->GetCentre().z - b->GetCentre().z) >
        (a->GetHalfExtents().at(2) + b->GetHalfExtents().at(2)))
        return false;

    // Collision in all other cases
    return true;
}
