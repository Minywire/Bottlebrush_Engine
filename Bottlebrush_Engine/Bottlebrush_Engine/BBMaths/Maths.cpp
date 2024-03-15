#include "Maths.h"

namespace BBMaths {
float Cos(float angle) { return std::cos(angle); }

float Sin(float angle) { return std::sin(angle); }

float Tan(float angle) { return std::tan(angle); }

float Sqrt(float x) { return (std::sqrt(x)); }

float InverseSqrt(float x) { return (1.0f / std::sqrt(x)); }
}  // namespace BBMaths
