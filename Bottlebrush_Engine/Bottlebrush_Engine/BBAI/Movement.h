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
    /// @param currentSpeed current speed
    /// @param acceleration current acceleration
    /// @param currentDirection the direction the object is currently facing, 
    /// this will be adjusted to face towards targetPos
    /// @param deltaTime delta time in frames
    /// @param offset how far to stand away from target position
    /// @return whether the object has reached the targetPos
    bool MoveTo(const glm::vec2& curPos, const glm::vec2& targetPos, 
        const float& currentSpeed, const float& acceleration, glm::vec2& currentDirection,
        float deltaTime, float offset);

    /// @author Alan
    /// @brief projects a cone infront of a position to see if target is within that cone
    /// @param curPos objects current position
    /// @param targetPos position of the target
    /// @param curDirection direction object is currently facing
    /// @param coneDistance how far the cone will go
    /// @param fov degrees to cast the cone
    /// @return if the target is within the cone's radius
    bool SeeTarget(const glm::vec2& curPos, const glm::vec2& targetPos, const glm::vec2& curDirection, float coneDistance, float fov);
}
