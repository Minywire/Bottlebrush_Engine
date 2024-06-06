#ifndef BOTTLEBRUSH_ENGINE_COLLISIONMGR_H
#define BOTTLEBRUSH_ENGINE_COLLISIONMGR_H

#include <memory>

#include "BBox.h"
#include "Collider.h"

class CollisionMgr {
   public:
    static bool IsCollision(const std::unique_ptr<Collider>& a,
                            const std::unique_ptr<Collider>& b);

   private:
    static bool IsCollision(const BBox* a, const BBox* b);
};

#endif  // BOTTLEBRUSH_ENGINE_COLLISIONMGR_H
