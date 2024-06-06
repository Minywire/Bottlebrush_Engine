#ifndef BOTTLEBRUSH_ENGINE_BBOX_H
#define BOTTLEBRUSH_ENGINE_BBOX_H

#include <array>

#include "Collider.h"
#include "glm/glm.hpp"

class BBox : public Collider {
   public:
    BBox();
    BBox(const glm::vec3& centre, const std::array<float, 3>& half_extents,
         bool is_static);

    [[nodiscard]] const std::array<float, 3>& GetHalfExtents() const;

   private:
    std::array<float, 3> half_extents_ = {};
};

#endif  // BOTTLEBRUSH_ENGINE_BBOX_H
