#ifndef BOTTLEBRUSH_ENGINE_MATHS_H
#define BOTTLEBRUSH_ENGINE_MATHS_H

#include <cmath>
#include <cstdint>
#include <bit>

namespace BBMaths {
const float PI = 3.1415926535897932384f;

float Cos(float angle);

float Sin(float angle);

float Tan(float angle);

float Sqrt(float x);

float InverseSqrt(float x);
}  // namespace BBMaths

#endif  // BOTTLEBRUSH_ENGINE_MATHS_H
