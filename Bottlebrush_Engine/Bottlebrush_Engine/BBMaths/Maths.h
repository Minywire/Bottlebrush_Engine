#ifndef BOTTLEBRUSH_ENGINE_MATHS_H
#define BOTTLEBRUSH_ENGINE_MATHS_H

#include <cmath>

namespace BBMaths {

const float kPiOver6 = 0.52359877559829887308f;
const float kPiOver4 = 0.78539816339744830962f;
const float kPiOver3 = 1.04719755119659774615f;
const float kPiOver2 = 1.57079632679489661923f;
const float k2PiOver3 = 2.09439510239319549231f;
const float k3PiOver4 = 2.35619449019234492885f;
const float k5PiOver6 = 2.61799387799149436539f;
const float kPi = 3.14159265358979323846f;
const float k7PiOver6 = 3.66519142918809211154f;
const float k5PiOver4 = 3.92699081698724154808f;
const float k3PiOver2 = 4.71238898038468985769f;
const float k5PiOver3 = 5.23598775598298873077f;
const float k7PiOver4 = 5.49778714378213816731f;
const float k11PiOver6 = 5.75958653158128760385f;
const float k2Pi = 6.28318530717958647693;

/// @brief Evaluates the trigonometric cosine function cos \a x for the given
/// angle \a x in radians.
/// @param x The angle in radians.
/// @returns The value of \c x evaluated such that \a y = cos \a x.
float Cos(float x);

/// @brief Evaluates the trigonometric sine function sin \a x for the given
/// angle \a x in radians.
/// @param x The angle in radians.
/// @returns The value of \c x evaluated such that \a y = sin \a x.
float Sin(float x);

/// @brief Evaluates the trigonometric tangent function tan \a x for the given
/// angle \a x in radians.
/// @param x The angle in radians.
/// @returns The value of \c x evaluated such that \a y = tan \a x.
float Tan(float x);

/// @brief Evaluates the trigonometric inverse cosine function cos<sup>-1</sup>
/// \a x for the given angle \a x in radians.
/// @param x The angle in radians.
/// @returns The value of \c x evaluated such that \a y = cos<sup>-1</sup> \a x.
float ArcCos(float x);

/// @brief Evaluates the trigonometric inverse sine function sin<sup>-1</sup> \a
/// x for the given angle \a x in radians.
/// @param x The angle in radians.
/// @returns The value of \c x evaluated such that \a y = sin<sup>-1</sup> \a x.
float ArcSin(float x);

/// @brief Evaluates the trigonometric inverse tangent function tan<sup>-1</sup>
/// \a x for the given angle \a x in radians.
/// @param x The angle in radians.
/// @returns The value of \c x evaluated such that \a y = tan<sup>-1</sup> \a x.
float ArcTan(float x);

/// @brief Evaluates the natural base \a e logarithm \a ln \a x for the given
/// value \a x.
/// @param x The real-valued number.
/// @returns The value of \c x evaluated such that \a y = \a ln \a x.
float Log(float x);

/// @brief Evaluates the common base 10 logarithm log<sub>10</sub> \a x for the
/// given value \a x.
/// @param x The real-valued number.
/// @returns The value of \c x evaluated such that \a y = log<sub>10</sub> \a x.
float Log10(float x);

/// @brief Evaluates the binary base 2 logarithm log<sub>2</sub> \a x for the
/// given value \a x.
/// @param x The real-valued number.
/// @returns The value of \c x evaluated such that \a y = log<sub>2</sub> \a x.
float Log2(float x);

/// @brief Evaluates Euler's number \a e raised to the power of the given value
/// \a x.
/// @param x The real-valued number.
/// @returns The value of \c x evaluated such that \a y = \a e<sup>x</sup>.
float Exp(float x);

/// @brief Evaluates 2 raised to the power of the given value \a x.
/// @param x The real-valued number.
/// @returns The value of \c x evaluated such that \a y = 2<sup>\a x</sup>.
float Exp2(float x);

/// @brief Evaluates the square root √\a x of the given value \a x.
/// @param x The real-valued number.
/// @returns The value of \c x evaluated such that \a y = √\a x.
float Sqrt(float x);

/// @brief Evaluates the inverse square root 1 / √\a x of the given value \a x.
/// @param x The real-valued number.
/// @returns The value of \c x evaluated such that \a y = 1 / √\a x.
float InverseSqrt(float x);

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
