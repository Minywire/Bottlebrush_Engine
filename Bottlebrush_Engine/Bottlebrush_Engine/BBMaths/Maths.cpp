#include "Maths.h"

namespace BBMaths {

float Cos(float x) { return std::cos(x); }

float Sin(float x) { return std::sin(x); }

float Tan(float x) { return std::tan(x); }

float ArcCos(float x) { return std::acos(x); }

float ArcSin(float x) { return std::asin(x); }

float ArcTan(float x) { return std::atan(x); }

float Log(float x) { return std::log(x); }

float Log10(float x) { return std::log10(x); }

float Log2(float x) { return std::log2(x); }

float Exp(float x) { return std::exp(x); }

float Exp2(float x) { return std::exp2(x); }

float Sqrt(float x) { return std::sqrt(x); }

float InverseSqrt(float x) { return 1.0f / std::sqrt(x); }

float DegToRad(float degrees) { return degrees * kPi / 180.0f; }

float RadToDeg(float radians) { return radians * 180.0f / kPi; }

}  // namespace BBMaths
