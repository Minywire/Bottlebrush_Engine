#ifndef BOTTLEBRUSH_ENGINE_MATHS_H
#define BOTTLEBRUSH_ENGINE_MATHS_H

#include <cmath>
#include <limits>
#include <numbers>
#include <numeric>

#include "glm/glm.hpp"

namespace BBMaths {

/// @brief Evaluates the conversion from degrees to radians.
/// @param degrees The real-valued number in degrees.
/// @returns The value of \c degrees evaluated such that \a R = \a D ⋅ \a π /
/// 180.
float DegToRad(float degrees);

/// @brief Evaluates the conversion from radians to degrees.
/// @param degrees The real-valued number in radians.
/// @returns The value of \c radians evaluated such that \a D = \a R ⋅ 180 / \a
/// π.
float RadToDeg(float radians);

}  // namespace BBMaths

#endif  // BOTTLEBRUSH_ENGINE_MATHS_H
