//
// Created by Alan 17/05/2024
//

#pragma once

#include <glm/glm.hpp>

/// forward decl to avoid cirle reference
class MovementComponent;

namespace Movement {

    /// @author Alan
    /// @brief Steers an object to targetPos by its current velocity
    /// @param curPos objects current position
    /// @param targetPos position to reach
    /// @param curVelocity current velocity
    /// @param deltaTime delta time in frames
    /// @param offset how far to stand away from target position
    /// @return whether the object has reached the targetPos
    bool MoveTo(const glm::vec2& curPos, const glm::vec2& targetPos, 
        MovementComponent& moveComp,
        float deltaTime, float offset = 100);
}
