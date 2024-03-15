#ifndef BOTTLEBRUSH_ENGINE_VECTOR2D_H_
#define BOTTLEBRUSH_ENGINE_VECTOR2D_H_

#include "Maths.h"
#include "Point2D.h"

namespace BBMaths {
typedef float TypeVec2D;

/// @class Vec2D
/// @brief Vectors use a generic base class to store their components.
template <typename T>
class Vec2D {
 public:
  T x_;
  T y_;

 protected:
  inline Vec2D() = default;

  Vec2D(const T& a, const T& b) {
    x_ = a;
    y_ = b;
  }

  explicit Vec2D(const Vec2D<TypeVec2D>& v) {
    x_ = v.x_;
    y_ = v.y_;
  }

  explicit Vec2D(const Euc2D<TypeEuc2D>& p) {
    x_ = p.x_;
    y_ = p.y_;
  }
};

/// @class Vector2D
/// @brief The \c Vector2D class encapsulates a 2D vector.
///
/// The \c Vector2D class is used to represent two-dimensional directional
/// vectors in Euclidean geometric space with real-valued components <i>x</i>
/// and <i>y</i>. A directional vector of this class is assumed to have a
/// <i>w</i> co-ordinate of 0 in its four-dimensional representation.
/// Two-dimensional points, where the <i>w</i> co-ordinate would be 1 in its
/// four-dimensional representation, should be stored using the \c Point2D
/// class. The <i>z</i> co-ordinate of a two-dimensional vector is always
/// assumed to be 0 in any three-dimensional representation.
class Vector2D : public Vec2D<TypeVec2D> {
 public:
  inline Vector2D() = default;

  Vector2D(float a, float b) : Vec2D<TypeVec2D>(a, b) {}

  explicit Vector2D(const Vec2D<TypeVec2D>& v) : Vec2D<TypeVec2D>(v) {}

  explicit Vector2D(const Euc2D<TypeEuc2D>& p) : Vec2D<TypeVec2D>(p) {}

  Vector2D& Set(float a, float b);

  Vector2D& Normalise();

  Vector2D& Rotate(float angle);

  Vector2D& operator=(const Vector2D& v);

  Vector2D& operator=(const Point2D& p);

  Vector2D& operator+=(const Vector2D& v);

  Vector2D& operator-=(const Vector2D& v);

  Vector2D& operator*=(float n);

  Vector2D& operator/=(float n);
};

float Dot(const Vector2D& a, const Vector2D& b);

float Magnitude(const Vector2D& v);

float InverseMagnitude(const Vector2D& v);

float SquaredMagnitude(const Vector2D& v);

Vector2D Projection(const Vector2D& a, const Vector2D& b);

Vector2D Rejection(const Vector2D& a, const Vector2D& b);

Vector2D operator-(const Vector2D& v);

Vector2D operator+(const Vector2D& a, const Vector2D& b);

Vector2D operator-(const Vector2D& a, const Vector2D& b);

Vector2D operator*(const Vector2D& v, float n);

Vector2D operator*(float n, const Vector2D& v);

Vector2D operator/(const Vector2D& v, float n);
}  // namespace BBMaths

#endif  // BOTTLEBRUSH_ENGINE_VECTOR2D_H_
