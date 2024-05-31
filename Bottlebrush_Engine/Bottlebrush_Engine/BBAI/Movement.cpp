//
// Created by Alan 28/05/2024
//

#include "Movement.h"
#include "Components.h"

namespace Movement {

    bool MoveTo(const glm::vec2& curPos, const glm::vec2& targetPos,
            const float& currentSpeed, const float& acceleration,
            glm::vec2& currentDirection, float deltaTime, float offset)
    {
        // calculate the heading from the object's position to target
        glm::vec2 toTarget = targetPos - curPos;
        toTarget = glm::normalize(toTarget);

        // get new speed after acceleration
        const float newSpeed = currentSpeed + acceleration;

        // calculate new direction and assigning it
        currentDirection = toTarget * glm::length(currentDirection); // assigns the direction to be towards the target
        glm::vec2 displacement = currentDirection * deltaTime * newSpeed;
        const glm::vec2 newPos = curPos + displacement;

        // calculate real target position
        const glm::vec2 realTargetPos = targetPos - toTarget * offset;

        // calculate the direction from newPos to realTargetPos
        glm::vec2 toRealTarget = realTargetPos - newPos;

        toRealTarget = glm::normalize(toRealTarget);
        // returns true if predicted new pos is within the acceptable range
        if (glm::length(toRealTarget) == 0) {
          return true;
        }
        // check to see whether newPos has gone passed the realTargetPos
        // dot product of 2 vectors
        float dp = glm::dot(toRealTarget, toTarget);
        return dp < 0.0f;
    }

    bool SeeTarget(const glm::vec2& curPos, const glm::vec2& targetPos,
        const glm::vec2& curDirection, float coneDistance,
        float fov)
    {
        // vector between current position and target position
	    glm::vec2 toTarget = targetPos - curPos;
	    // distance between current position and target position
	    float dist = glm::length(toTarget);	  
	    if (dist > coneDistance) return false; // not within range

	    // get heading to target
	    toTarget = glm::normalize(toTarget);
	    glm::vec2 direction = curDirection;
	    //get patrollers current heading
        direction = glm::normalize(direction);

	    //compute angle between patroller and target
	    double angle = glm::dot(direction, toTarget);
	    //getting some precision problem ensure cos angle is in -1.0 to 1.0
	    //if (angle > 1.0) angle = 1.0;
	    //else if (angle < -1.0) angle = -1.0;
        //get heading in degrees
        angle = glm::degrees(acos(angle));

	    //determine if target is in fov
        return angle <= (fov / 2);
    }
}
