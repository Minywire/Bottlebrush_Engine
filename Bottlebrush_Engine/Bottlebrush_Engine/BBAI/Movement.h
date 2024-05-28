//
// Created by Alan 17/05/2024
//

#pragma once

#include <glm/glm.hpp>

namespace Movement {

    /// @author Alan
    /// @brief Steers an object to targetPos by its current velocity
    /// @param curPos objects current position
    /// @param targetPos position to reach
    /// @param curVelocity current velocity
    /// @param deltaTime delta time in frames
    /// @param offset how far to stand away from target position
    /// @return whether the object has reached the targetPos
    bool MoveTo(glm::vec2& curPos, const glm::vec2 targetPos, 
        glm::vec2& curVelocity, float& curMoveSpeed, float moveAcceleration,
        float deltaTime, float offset = 0);
}
