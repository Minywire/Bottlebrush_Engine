//
// Created by Alan 28/05/2024
//

#include "Movement.h"
#include "Components.h"

namespace Movement {

    bool MoveTo(const glm::vec2& curPos, const glm::vec2& targetPos,
            MovementComponent& moveComp,
            float deltaTime, float offset)
    {
        // calculate the heading from the object's position to target
        glm::vec2 toTarget = targetPos - curPos;
        toTarget = glm::normalize(toTarget);
        if (glm::length(toTarget) == 0) return true; // early return if already at destination

        // get new speed after acceleration
        float newSpeed = moveComp.current_speed + moveComp.acceleration_rate;

        // calculate new direction and assigning it
        moveComp.direction = toTarget * glm::length(moveComp.direction); // assigns the direction to be towards the target
        glm::vec2 displacement = moveComp.direction * deltaTime * newSpeed;
        glm::vec2 newPos = curPos + displacement;

        // calculate real target position
        glm::vec2 realTargetPos = targetPos - toTarget * offset;

        // calculate the direction from newPos to realTargetPos
        glm::vec2 toRealTarget = realTargetPos - newPos;

        toRealTarget = glm::normalize(toRealTarget);
        if (glm::length(toRealTarget) == 0) {
            return true;
        }

        // check to see whether newPos has gone passed the realTargetPos
        // dot product of 2 vectors
        float dp = glm::dot(toRealTarget, toTarget);
        if (dp < 0.0) {
            return true;
        }

        return false;
    }
}
