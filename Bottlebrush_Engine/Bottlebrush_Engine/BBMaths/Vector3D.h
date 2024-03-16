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
/// vectors in Euclidean geometric space with real-valued components \a x, \a y,
/// and \a z. A directional vector of this class is assumed to have a \a w
/// co-ordinate of 0 in its four-dimensional representation. Three-dimensional
/// points, where the \a w co-ordinate would be 1 in its four-dimensional
/// representation, should be stored using the \c Point3D class.
/// <p>
/// The default constructor leaves the components of the vector undefined. If
/// the values \c a, \c b, and \c c are provided in the constructor, they are
/// assigned to the \a x, \a y, and \a z co-ordinates of the point.
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

  /// @brief Sets all three components of the 3D vector.
  /// <p>
  /// The \c Set function sets the \a x, \a y, and /a z co-ordinates of a
  /// three-dimensional vector to the values given by the parameters \c a, \c b,
  /// and \c c, respectively.
  /// <p>
  /// The return value is a reference to the \c Vector3D object.
  /// @param a The new \a x co-ordinate.
  /// @param b The new \a y co-ordinate.
  /// @param c The new \a z co-ordinate.
  /// @returns A reference to a \c Vector3D object such that \b v = (<em>a</em>,
  /// <em>b</em>, <em>c</em>).
  Vector3D& Set(float a, float b, float c);

  /// @brief Normalises the 3D vector.
  /// <p>
  /// The \c Normalise function normalises a three-dimensional vector to unit
  /// length, multiplying its components by the inverse of its magnitude.
  /// Normalising the zero vector produces undefined results.
  /// <p>
  /// The return value is a reference to the \c Vector3D object.
  /// @returns A reference to a \c Vector3D object such that \b v = \b v / ‖ \b
  /// v ‖.
  Vector3D& Normalise();

  /// @brief Rotates the 3D vector about the \a x axis.
  /// <p>
  /// The \c RotateAboutX function rotates a three-dimensional vector about the
  /// \a x axis through the angle \a θ given by the \c angle parameter.
  /// <p>
  /// The return value is a reference to the \c Vector3D object.
  /// @param angle The angle, in radians, through which the vector is rotated.
  /// @returns A reference to a \c Vector3D object such that \b v = (\a x, \a y
  /// cos \a θ - \a z sin \a θ, \a y sin \a θ + \a z cos \a θ).
  Vector3D& RotateAboutX(float angle);

  /// @brief Rotates the 3D vector about the \a y axis.
  /// <p>
  /// The \c RotateAboutY function rotates a three-dimensional vector about the
  /// \a y axis through the angle \a θ given by the \c angle parameter.
  /// <p>
  /// The return value is a reference to the \c Vector3D object.
  /// @param angle The angle, in radians, through which the vector is rotated.
  /// @returns A reference to a \c Vector3D object such that \b v = (\a x cos \a
  /// θ + \a z sin \a θ, \a y, \a z cos \a θ - \a x sin \a θ).
  Vector3D& RotateAboutY(float angle);

  /// @brief Rotates the 3D vector about the \a z axis.
  /// <p>
  /// The \c RotateAboutX function rotates a three-dimensional vector about the
  /// \a z axis through the angle \a θ given by the \c angle parameter.
  /// <p>
  /// The return value is a reference to the \c Vector3D object.
  /// @param angle The angle, in radians, through which the vector is rotated.
  /// @returns A reference to a \c Vector3D object such that \b v = (\a x cos \a
  /// θ + \a z sin \a θ, \a z cos \a θ - \a x sin \a θ, \a z).
  Vector3D& RotateAboutZ(float angle);

  /// @brief Assigns the \a x, \a y, and \a z components of the right-hand side
  /// vector \b a to the \a x, \a y, and \a z components of the left-hand side
  /// vector \b v.
  /// @param v The right-hand side vector.
  /// @returns A reference to a \c Vector3D object such that \b v =
  /// (<em>x<sub>a</sub></em>, <em>y<sub>a</sub></em>, <em>z<sub>a</sub></em>).
  Vector3D& operator=(const Vector3D& a);

  /// @brief Assigns the \a x, \a y, and \a z components of the right-hand side
  /// point \a p to the \a x, \a y, and \a z components of the left-hand side
  /// vector \b v.
  /// @param a The right-hand side point.
  /// @returns A reference to a \c Vector3D object such that \b v =
  /// (<em>x<sub>a</sub></em>, <em>y<sub>a</sub></em>, <em>z<sub>a</sub></em>).
  Vector3D& operator=(const Point3D& a);

  /// @brief Assigns the \a x and \a y components of the right-hand side vector
  /// \b a to the \a x and \a y components of the left-hand side vector \b v.
  /// The \a z component of the left-hand side vector is assigned a value of 0.
  /// @param a The right-hand side vector.
  /// @returns A reference to a \c Vector3D object such that \b v =
  /// (<em>x<sub>a</sub></em>, <em>y<sub>a</sub></em>, 0).
  Vector3D& operator=(const Vector2D& a);

  /// @brief Assigns the \a x and \a y components of the right-hand side point
  /// \b a to the \a x and \a y components of the left-hand side vector \b v.
  /// The \a z component of the left-hand side vector is assigned a value of 0.
  /// @param a The right-hand side point.
  /// @returns A reference to a \c Vector3D object such that \b v =
  /// (<em>x<sub>a</sub></em>, <em>y<sub>a</sub></em>, 0).
  Vector3D& operator=(const Point2D& a);

  /// @brief Adds the \a x, \a y, and \a z components of the right-hand side
  /// vector \b a to the \a x, \a y, and \a z components of the left-hand side
  /// vector \b v.
  /// @param a The right-hand side vector.
  /// @returns A reference to a \c Vector3D object such that \b v = \b v + \b a.
  Vector3D& operator+=(const Vector3D& a);

  /// @brief Subtracts the \a x, \a y, and \a z components of the right-hand
  /// side vector \b a from the \a x, \a y, and \a z components of the left-hand
  /// side vector \b v.
  /// @param a The right-hand side vector.
  /// @returns A reference to a \c Vector3D object such that \b v = \b v - \b a.
  Vector3D& operator-=(const Vector3D& a);

  /// @brief Multiplies the right-hand side scalar \a n with the \a x, \a y, and
  /// \a z components of the left-hand side vector \b v.
  /// @param n The right-hand side scalar value.
  /// @returns A reference to a \c Vector3D object such that \b v = \b v ⋅ \a n.
  Vector3D& operator*=(float n);

  /// @brief Divides the \a x, \a y, and \a z components of the left-hand side
  /// vector \b v with the right-hand side scalar \a n.
  /// @param n The right-hand side scalar value.
  /// @returns A reference to a \c Vector3D object such that \b v = \b v / \a n.
  Vector3D& operator/=(float n);
};

/// @brief Evaluates the dot product between two 3D vectors.
/// <p>
/// The \c Dot function evaluates the component-wise dot product between the
/// three-dimensional vectors \b a and \b b.
/// <p>
/// The return value is a scalar.
/// @param a A three-dimensional vector.
/// @param b A three-dimensional vector.
/// @returns A scalar value such that \a n = \b a ⋅ \b b.
float Dot(const Vector3D& a, const Vector3D& b);

/// @brief Evaluates the cross product between two 3D vectors.
/// <p>
/// The \c Cross function evaluates the geometric cross product between the
/// three-dimensional vectors \b a and \b b.
/// <p>
/// The return value is a \c Vector3D object.
/// @param a A three-dimensional vector.
/// @param b A three-dimensional vector.
/// @returns A \c Vector3D object such that \b v = \b a × \b b.
Vector3D Cross(const Vector3D& a, const Vector3D& b);

/// @brief Evaluates the magnitude of a 3D vector.
/// <p>
/// The \c Magnitude function evaluates the magnitude (or length, or norm) of
/// the three-dimensional vector \b a.
/// <p>
/// The return value is a scalar.
/// @param a A three-dimensional vector.
/// @returns A scalar value such that ‖ \b a ‖ = √\b a ⋅ \b a.
float Magnitude(const Vector3D& a);

/// @brief Evaluates the inverse magnitude of a 3D vector.
/// <p>
/// The \c InverseMagnitude function evaluates the inverse magnitude (or length,
/// or norm) of the three-dimensional vector \b a.
/// <p>
/// The return value is a scalar.
/// @param a A three-dimensional vector.
/// @returns A scalar value such that 1 / ‖ \b a ‖ = 1 / √\b a ⋅ \b a.
float InverseMagnitude(const Vector3D& a);

/// @brief Evaluates the squared magnitude of a 3D vector.
/// <p>
/// The \c SquaredMagnitude function evaluates the squared magnitude (or length,
/// or norm) of the three-dimensional vector \b a.
/// <p>
/// The return value is a scalar.
/// @param a A three-dimensional vector.
/// @returns A scalar value such that ‖ \b a ‖ <sup>2</sup> = \b a ⋅ \b a.
float SquaredMagnitude(const Vector3D& a);

/// @brief Evaluates the orthogonal projection of a 3D vector.
/// <p>
/// The \c Projection function evaluates the orthogonal projection of the
/// three-dimensional vector \b a onto a straight line parallel to the
/// three-dimensional vector \b b.
/// <p>
/// The return value is a \c Vector3D object.
/// @param a A three-dimensional vector.
/// @param b A three-dimensional vector.
/// @returns A \c Vector3D object such that proj<sub>\a b</sub>\a a = \b b ⋅ \b
/// a ⋅ \b b / \b b ⋅ \b b.
Vector3D Projection(const Vector3D& a, const Vector3D& b);

/// @brief Evaluates the orthogonal rejection of a 3D vector.
/// <p>
/// The \c Rejection function evaluates the orthogonal rejection of the
/// three-dimensional vector \b a onto a straight line parallel to the
/// three-dimensional vector \b b.
/// <p>
/// The return value is a \c Vector3D object.
/// @param a A three-dimensional vector.
/// @param b A three-dimensional vector.
/// @returns A \c Vector3D object such that rej<sub>\a b</sub>\a a = \b a  - \b
/// b ⋅ \b a ⋅ \b b / \b b ⋅ \b b.
Vector3D Rejection(const Vector3D& a, const Vector3D& b);

/// @brief Negates the \a x, \a y, and \a z components of the vector \a a.
/// @param a A three-dimensional vector.
/// @returns A \c Vector3D object such that \b v = -\b a.
Vector3D operator-(const Vector3D& a);

/// @brief Adds the \a x, \a y, and \a z components of the vector \b a to the \a
/// x, \a y, and \a z components of the vector \b b.
/// @param a A three-dimensional vector.
/// @param b A three-dimensional vector.
/// @returns A \c Vector3D object such that \b v = \b a + \b b.
Vector3D operator+(const Vector3D& a, const Vector3D& b);

/// @brief Subtracts the \a x, \a y, and \a z components of the vector \b b from
/// the \a x, \a y, and \a z components of the vector \b a.
/// @param a A three-dimensional vector.
/// @param b A three-dimensional vector.
/// @returns A \c Vector3D object such that \b v = \b a - \b b.
Vector3D operator-(const Vector3D& a, const Vector3D& b);

/// @brief Multiplies the \a x, \a y, and \a z components of the vector \b a
/// with the the scalar \a n.
/// @param n A scalar value.
/// @returns A \c Vector3D object such that \b v = \b a ⋅ \a n.
Vector3D operator*(const Vector3D& a, float n);

/// @brief Multiplies the the scalar \a n with the \a x, \a y, and \a z
/// components of the vector \b a.
/// @param n A scalar value.
/// @returns A \c Vector3D object such that \b v = \a n ⋅ \b a.
Vector3D operator*(float n, const Vector3D& a);

/// @brief Divides the \a x, \a y, and \a z components of the vector \b a with
/// the scalar \a n.
/// @param n A scalar value.
/// @returns A \c Vector3D object such that <\b v = \b a / \a n.
Vector3D operator/(const Vector3D& a, float n);

}  // namespace BBMaths

#endif  // BOTTLEBRUSH_ENGINE_VECTOR3D_H_
