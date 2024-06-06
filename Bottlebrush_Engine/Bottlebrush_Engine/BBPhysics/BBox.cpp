#include "BBox.h"

BBox::BBox() : Collider(kColliderBox, {}, true) { half_extents_ = {}; }

BBox::BBox(const glm::vec3& centre, const std::array<float, 3>& half_extents,
           bool is_static)
    : Collider(kColliderBox, centre, is_static) {
    half_extents_ = half_extents;
}

const std::array<float, 3>& BBox::GetHalfExtents() const {
    return half_extents_;
}
