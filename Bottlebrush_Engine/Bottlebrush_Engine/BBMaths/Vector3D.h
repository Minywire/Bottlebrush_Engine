#ifndef BOTTLEBRUSH_ENGINE_VECTOR3D_H_
#define BOTTLEBRUSH_ENGINE_VECTOR3D_H_

#include "Maths.h"
#include "Point2D.h"
#include "Point3D.h"
#include "Vector2D.h"

namespace BBMaths {
typedef float TypeVec3D;

/// @class Vec3D
/// @brief Vectors use a generic base class to store their components.
template <typename T>
class Vec3D {
 public:
  T x_;
  T y_;
  T z_;

 protected:
  inline Vec3D() = default;

  Vec3D(const T& a, const T& b, const T& c) {
    x_ = a;
    y_ = b;
    z_ = c;
  }

  explicit Vec3D(const Vec3D<TypeVec3D>& v) {
    x_ = v.x_;
    y_ = v.y_;
    z_ = v.z_;
  }

  explicit Vec3D(const Euc3D<TypeEuc3D>& p) {
    x_ = p.x_;
    y_ = p.y_;
    z_ = p.z_;
  }

  explicit Vec3D(const Vec2D<TypeVec2D>& v) {
    x_ = v.x_;
    y_ = v.y_;
    z_ = 0.0f;
  }

  Vec3D(const Vec2D<TypeVec2D>& v, float c) {
    x_ = v.x_;
    y_ = v.y_;
    z_ = c;
  }

  explicit Vec3D(const Euc2D<TypeEuc2D>& p) {
    x_ = p.x_;
    y_ = p.y_;
    z_ = 0.0f;
  }

  Vec3D(const Euc2D<TypeEuc2D>& p, float c) {
    x_ = p.x_;
    y_ = p.y_;
    z_ = c;
  }
};

/// @class Vector3D
/// @brief The \c Vector3D class encapsulates a 3D vector.
///
/// The \c Vector3D class is used to represent three-dimensional directional
/// vectors in Euclidean geometric space with real-valued components <i>x</i>,
/// <i>y</i>, and <i>z</i>. A directional vector of this class is assumed to
/// have a <i>w</i> co-ordinate of 0 in its four-dimensional representation.
/// Three-dimensional points, where the <i>w</i> co-ordinate would be 1 in its
/// four-dimensional representation, should be stored using the \c Point3D
/// class.
class Vector3D : public Vec3D<TypeVec3D> {
 public:
  inline Vector3D() = default;

  Vector3D(float a, float b, float c) : Vec3D<TypeVec3D>(a, b, c) {}

  explicit Vector3D(const Vec3D<TypeVec3D>& v) : Vec3D<TypeVec3D>(v) {}

  explicit Vector3D(const Euc3D<TypeEuc3D>& p) : Vec3D<TypeVec3D>(p) {}

  explicit Vector3D(const Vec2D<TypeVec2D>& v) : Vec3D<TypeVec3D>(v) {}

  Vector3D(const Vec2D<TypeVec2D>& v, float c) : Vec3D<TypeVec3D>(v, c) {}

  explicit Vector3D(const Euc2D<TypeEuc2D>& p) : Vec3D<TypeVec3D>(p) {}

  Vector3D(const Euc2D<TypeEuc2D>& p, float c) : Vec3D<TypeVec3D>(p, c) {}

  Vector3D& Set(float a, float b, float c);

  Vector3D& Normalise();

  Vector3D& RotateAboutX(float angle);

  Vector3D& RotateAboutY(float angle);

  Vector3D& RotateAboutZ(float angle);

  Vector3D& operator=(const Vector3D& v);

  Vector3D& operator=(const Point3D& p);

  Vector3D& operator=(const Vector2D& v);

  Vector3D& operator=(const Point2D& p);

  Vector3D& operator+=(const Vector3D& v);

  Vector3D& operator-=(const Vector3D& v);

  Vector3D& operator*=(float n);

  Vector3D& operator/=(float n);
};

float Dot(const Vector3D& a, const Vector3D& b);

Vector3D Cross(const Vector3D& a, const Vector3D& b);

float Magnitude(const Vector3D& v);

float InverseMagnitude(const Vector3D& v);

float SquaredMagnitude(const Vector3D& v);

Vector3D Projection(const Vector3D& a, const Vector3D& b);

Vector3D Rejection(const Vector3D& a, const Vector3D& b);

Vector3D operator-(const Vector3D& v);

Vector3D operator+(const Vector3D& a, const Vector3D& b);

Vector3D operator-(const Vector3D& a, const Vector3D& b);

Vector3D operator*(const Vector3D& v, float n);

Vector3D operator*(float n, const Vector3D& v);

Vector3D operator/(const Vector3D& v, float n);
}  // namespace BBMaths

#endif  // BOTTLEBRUSH_ENGINE_VECTOR3D_H_
