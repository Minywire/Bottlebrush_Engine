#include "Maths.h"

namespace BBMaths {
float Cos(float angle) { return std::cos(angle); }

float Sin(float angle) { return std::sin(angle); }

float Tan(float angle) { return std::tan(angle); }

float Sqrt(float x) { return (std::sqrt(x)); }

float InverseSqrt(float x) {
  float const y =
      std::bit_cast<float>(0x5f3759df - (std::bit_cast<std::uint32_t>(x) >> 1));
  return y * (1.5f - (x * 0.5f * y * y));
}
}  // namespace BBMaths
