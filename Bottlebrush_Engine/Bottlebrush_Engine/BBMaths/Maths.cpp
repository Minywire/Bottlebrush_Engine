#include "Maths.h"

namespace BBMaths {

float DegToRad(float degrees) {
  return degrees * (float)std::numbers::pi / 180.0f;
}

float RadToDeg(float radians) {
  return radians * 180.0f / (float)std::numbers::pi;
}

}  // namespace BBMaths
