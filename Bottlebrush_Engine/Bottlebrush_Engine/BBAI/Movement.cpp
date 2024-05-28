//
// Created by Alan 28/05/2024
//

#include "Movement.h"

namespace Movement {

	bool MoveTo(glm::vec2& curPos, const glm::vec2 targetPos,
            glm::vec2& curVelocity, float& curMoveSpeed, float moveAcceleration, 
			float deltaTime, float offset)
	{
		// calculate the heading from the object's position to target
		glm::vec2 toTarget = targetPos - curPos;
		toTarget = glm::normalize(toTarget);
		if (glm::length(toTarget) == 0) return true; // early return if already at destination

		// ramp up speed
		curMoveSpeed = moveAcceleration;

		// calculate new velocity and new character position
		curVelocity = toTarget * glm::length(curVelocity);
		glm::vec2 displacement = curVelocity * deltaTime * curMoveSpeed;
		glm::vec2 newPos = curPos + displacement;

		// calculate real target position
		glm::vec2 realTargetPos = targetPos - toTarget * offset;

		// calculate the direction from newPos to realTargetPos
		glm::vec2 toRealTarget = realTargetPos - newPos;

		toRealTarget = glm::normalize(toRealTarget);
		if (glm::length(toRealTarget) == 0) {
			curPos = realTargetPos;
			return true;
		}

		// check to see whether newPos has gone passed the realTargetPos
		// dot product of 2 vectors
		float dp = glm::dot(toRealTarget, toTarget);
		if (dp < 0.0) {
			//newPos has passed realTargetPos, as their angle > 90 degree
			curPos = realTargetPos; // step back to realTargetPos
			return true;
		}

		// newPos has not yet passed realTargetPos
		curPos = newPos; // update character position
		return false;
	}
}
