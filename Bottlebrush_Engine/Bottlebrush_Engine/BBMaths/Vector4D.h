#ifndef BOTTLEBRUSH_ENGINE_VECTOR4D_H_
#define BOTTLEBRUSH_ENGINE_VECTOR4D_H_

#include "Maths.h"
#include "Point2D.h"
#include "Point3D.h"
#include "Vector2D.h"
#include "Vector3D.h"

namespace BBMaths {
typedef float TypeVec4D;

/// @class Vec4D
/// @brief Vectors use a generic base class to store their components.
template <typename T>
class Vec4D {
 public:
  T x_;
  T y_;
  T z_;
  T w_;

 protected:
  inline Vec4D() = default;

  Vec4D(const T& a, const T& b, const T& c, const T& d) {
    x_ = a;
    y_ = b;
    z_ = c;
    w_ = d;
  }

  explicit Vec4D(const Vec4D<TypeVec4D>& v) {
    x_ = v.x_;
    y_ = v.y_;
    z_ = v.z_;
    w_ = v.w_;
  }

  explicit Vec4D(const Vec3D<TypeVec3D>& v) {
    x_ = v.x_;
    y_ = v.y_;
    z_ = v.z_;
    w_ = 0.0f;
  }

  Vec4D(const Vec3D<TypeVec3D>& v, float d) {
    x_ = v.x_;
    y_ = v.y_;
    z_ = v.z_;
    w_ = d;
  }

  explicit Vec4D(const Euc3D<TypeEuc3D>& p) {
    x_ = p.x_;
    y_ = p.y_;
    z_ = p.z_;
    w_ = 1.0f;
  }

  Vec4D(const Euc3D<TypeEuc3D>& p, float d) {
    x_ = p.x_;
    y_ = p.y_;
    z_ = p.z_;
    w_ = d;
  }

  explicit Vec4D(const Vec2D<TypeVec2D>& v) {
    x_ = v.x_;
    y_ = v.y_;
    z_ = 0.0f;
    w_ = 0.0f;
  }

  Vec4D(const Vec2D<TypeVec2D>& v, float c, float d) {
    x_ = v.x_;
    y_ = v.y_;
    z_ = c;
    w_ = d;
  }

  explicit Vec4D(const Euc2D<TypeEuc2D>& p) {
    x_ = p.x_;
    y_ = p.y_;
    z_ = 0.0f;
    w_ = 1.0f;
  }

  Vec4D(const Euc2D<TypeEuc2D>& p, float c, float d) {
    x_ = p.x_;
    y_ = p.y_;
    z_ = c;
    w_ = d;
  }
};

/// @class Vector4D
/// @brief The \c Vector4D class encapsulates a 3D vector.
///
/// The \c Vector4D class is used to represent four-dimensional directional
/// vectors in Euclidean geometric space with real-valued components <i>x</i>,
/// <i>y</i>, <i>z</i>, and <i>w</i>. A directional vector of this class is
/// assumed to have a <i>w</i> co-ordinate of 0 when constructed from a
/// two-dimensional or three-dimensional vector, or a <i>w</i> co-ordinate of 1
/// when constructed from a two-dimensional or three-dimensional point.
class Vector4D : public Vec4D<TypeVec4D> {
 public:
  inline Vector4D() = default;

  Vector4D(float a, float b, float c, float d) : Vec4D<TypeVec4D>(a, b, c, d) {}

  explicit Vector4D(const Vec4D<TypeVec4D>& v) : Vec4D<TypeVec4D>(v) {}

  explicit Vector4D(const Vec3D<TypeVec3D>& v) : Vec4D<TypeVec4D>(v) {}

  Vector4D(const Vec3D<TypeVec3D>& v, float d) : Vec4D<TypeVec4D>(v, d) {}

  explicit Vector4D(const Euc3D<TypeEuc3D>& p) : Vec4D<TypeVec4D>(p) {}

  Vector4D(const Euc3D<TypeEuc3D>& p, float d) : Vec4D<TypeVec4D>(p, d) {}

  explicit Vector4D(const Vec2D<TypeVec2D>& v) : Vec4D<TypeVec4D>(v) {}

  Vector4D(const Vec2D<TypeVec2D>& v, float c, float d)
      : Vec4D<TypeVec4D>(v, c, d) {}

  explicit Vector4D(const Euc2D<TypeEuc2D>& p) : Vec4D<TypeVec4D>(p) {}

  Vector4D(const Euc2D<TypeEuc2D>& p, float c, float d)
      : Vec4D<TypeVec4D>(p, c, d) {}

  Vector4D& Set(float a, float b, float c, float d);

  Vector4D& Set(const Vector3D& v);

  Vector4D& Set(const Vector3D& v, float d);

  Vector4D& Set(const Vector2D& v);

  Vector4D& Set(const Vector2D& v, float c, float d);

  Vector4D& Normalise();

  Vector4D& RotateAboutX(float angle);

  Vector4D& RotateAboutY(float angle);

  Vector4D& RotateAboutZ(float angle);

  Vector4D& operator=(const Vector4D& v);

  Vector4D& operator=(const Vector3D& v);

  Vector4D& operator=(const Point3D& p);

  Vector4D& operator=(const Vector2D& v);

  Vector4D& operator=(const Point2D& p);

  Vector4D& operator+=(const Vector4D& v);

  Vector4D& operator-=(const Vector4D& v);

  Vector4D& operator*=(float n);

  Vector4D& operator/=(float n);
};

float Dot(const Vector4D& a, const Vector4D& b);

float Magnitude(const Vector4D& v);

float InverseMagnitude(const Vector4D& v);

float SquaredMagnitude(const Vector4D& v);

Vector4D Projection(const Vector4D& a, const Vector4D& b);

Vector4D Rejection(const Vector4D& a, const Vector4D& b);

Vector4D operator-(const Vector4D& v);

Vector4D operator+(const Vector4D& a, const Vector4D& b);

Vector4D operator-(const Vector4D& a, const Vector4D& b);

Vector4D operator*(const Vector4D& v, float n);

Vector4D operator*(float n, const Vector4D& v);

Vector4D operator/(const Vector4D& v, float n);
}  // namespace BBMaths

#endif  // BOTTLEBRUSH_ENGINE_VECTOR4D_H_
