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
/// vectors in Euclidean geometric space with real-valued components \a x,
/// \a y, \a z, and \a w. A directional vector of this class is assumed to have
/// a \a w co-ordinate of 0 when constructed from a two-dimensional or
/// three-dimensional vector, or a \a w co-ordinate of 1 when constructed from a
/// two-dimensional or three-dimensional point.
/// <p>
/// The default constructor leaves the components of the vector undefined. If
/// the values \c a, \c b, \c c, and \c d are provided in the constructor, they
/// are assigned to the \a x, \a y, \a z, and \a w co-ordinates of the point.
/// @see Point2D
/// @see Point3D
/// @see Vector2D
/// @see Vector3D
/// @author Jaiden di Lanzo
class Vector4D : public Vec4D<TypeVec4D> {
 public:
  inline Vector4D() = default;

  Vector4D(float a, float b, float c, float d) : Vec4D<TypeVec4D>(a, b, c, d) {}

  Vector4D(const Vector4D& v) = default;

  explicit Vector4D(const Vector3D& v) : Vec4D<TypeVec4D>(v) {}

  Vector4D(const Vector3D& v, float d) : Vec4D<TypeVec4D>(v, d) {}

  explicit Vector4D(const Point3D& p) : Vec4D<TypeVec4D>(p) {}

  Vector4D(const Point3D& p, float d) : Vec4D<TypeVec4D>(p, d) {}

  explicit Vector4D(const Vector2D& v) : Vec4D<TypeVec4D>(v) {}

  Vector4D(const Vector2D& v, float c, float d) : Vec4D<TypeVec4D>(v, c, d) {}

  explicit Vector4D(const Point2D& p) : Vec4D<TypeVec4D>(p) {}

  Vector4D(const Point2D& p, float c, float d) : Vec4D<TypeVec4D>(p, c, d) {}

  /// @brief Sets all four components of the 4D vector.
  /// <p>
  /// The \c Set function sets the \a x, \a y, \a z, and /a w co-ordinates of a
  /// four-dimensional vector to the values given by the parameters \c a, \c b,
  /// \c c, and \c d, respectively.
  /// <p>
  /// The return value is a reference to the \c Vector4D object.
  /// @param a The new \a x co-ordinate.
  /// @param b The new \a y co-ordinate.
  /// @param c The new \a z co-ordinate.
  /// @param d The new \a z co-ordinate.
  /// @returns A reference to a \c Vector4D object such that \b v = (<em>a</em>,
  /// <em>b</em>, <em>c</em>, <em>d</em>).
  Vector4D& Set(float a, float b, float c, float d);

  /// @brief Normalises the 4D vector.
  /// <p>
  /// The \c Normalise function normalises a four-dimensional vector to unit
  /// length, multiplying its components by the inverse of its magnitude.
  /// Normalising the zero vector produces undefined results. <p> The return
  /// value is a reference to the \c Vector4D object.
  /// @returns A reference to a \c Vector4D object such that \b v = \b v / ‖ \b
  /// v ‖.
  Vector4D& Normalise();

  /// @brief Rotates the 4D vector about the \a x axis.
  /// <p>
  /// The \c RotateAboutX function rotates a four-dimensional vector about the
  /// \a x axis through the angle \a θ given by the \c angle parameter.
  /// <p>
  /// The return value is a reference to the \c Vector4D object.
  /// @param angle The angle, in radians, through which the vector is rotated.
  /// @returns A reference to a \c Vector4D object such that \b v = (\a x, \a y
  /// cos \a θ - \a z sin \a θ, \a y sin \a θ + \a z cos \a θ, \a w).
  Vector4D& RotateAboutX(float angle);

  /// @brief Rotates the 4D vector about the \a y axis.
  /// <p>
  /// The \c RotateAboutY function rotates a four-dimensional vector about the
  /// \a y axis through the angle \a θ given by the \c angle parameter.
  /// <p>
  /// The return value is a reference to the \c Vector4D object.
  /// @param angle The angle, in radians, through which the vector is rotated.
  /// @returns A reference to a \c Vector4D object such that \b v = (\a x cos \a
  /// θ + \a z sin \a θ, \a y, \a z cos \a θ - \a x sin \a θ, \a w).
  Vector4D& RotateAboutY(float angle);

  /// @brief Rotates the 4D vector about the \a z axis.
  /// <p>
  /// The \c RotateAboutX function rotates a four-dimensional vector about the
  /// \a z axis through the angle \a θ given by the \c angle parameter.
  /// <p>
  /// The return value is a reference to the \c Vector4D object.
  /// @param angle The angle, in radians, through which the vector is rotated.
  /// @returns A reference to a \c Vector4D object such that \b v = (\a x cos \a
  /// θ - \a y sin \a θ, \a x sin \a θ - \a y cos \a θ, \a z, \a w).
  Vector4D& RotateAboutZ(float angle);

  /// @brief Assigns the \a x, \a y, \a z and \a w components of the right-hand
  /// side vector \b a to the \a x, \a y, \a z and \a w components of the
  /// left-hand side vector \b v.
  /// @param v The right-hand side vector.
  /// @returns A reference to a \c Vector4D object such that \b v =
  /// (<em>x<sub>a</sub></em>, <em>y<sub>a</sub></em>, <em>z<sub>a</sub></em>,
  /// <em>w<sub>a</sub></em>).
  Vector4D& operator=(const Vector4D& a);

  /// @brief Assigns the \a x, \a y, and \a z components of the right-hand side
  /// vector \b a to the \a x, \a y, and \a z components of the left-hand side
  /// vector \b v. The \a w component of the left-hand side vector is assigned a
  /// value of 0.
  /// @param a The right-hand side vector.
  /// @returns A reference to a \c Vector4D object such that \b v =
  /// (<em>x<sub>a</sub></em>, <em>y<sub>a</sub></em>, <em>z<sub>a</sub></em>,
  /// 0).
  Vector4D& operator=(const Vector3D& a);

  /// @brief Assigns the \a x, \a y, and \a z components of the right-hand side
  /// point \b a to the \a x, \a y, and \a z components of the left-hand side
  /// vector \b v. The \a w component of the left-hand side vector is assigned a
  /// value of 1.
  /// @param a The right-hand side vector.
  /// @returns A reference to a \c Vector4D object such that \b v =
  /// (<em>x<sub>a</sub></em>, <em>y<sub>a</sub></em>, <em>z<sub>a</sub></em>,
  /// 1).
  Vector4D& operator=(const Point3D& a);

  /// @brief Assigns the \a x and \a y components of the right-hand side vector
  /// \b a to the \a x and \a y components of the left-hand side vector \b v.
  /// The \a z and \a w components of the left-hand side vector are assigned a
  /// value of 0.
  /// @param a The right-hand side vector.
  /// @returns A reference to a \c Vector4D object such that \b v =
  /// (<em>x<sub>a</sub></em>, <em>y<sub>a</sub></em>, 0, 0).
  Vector4D& operator=(const Vector2D& a);

  /// @brief Assigns the \a x and \a y components of the right-hand side point
  /// \b a to the \a x and \a y components of the left-hand side vector \b v.
  /// The \a z component of the left-hand side vector is assigned a value of 0.
  /// The \a w component of the left-hand side vector is assigned a value of 1.
  /// @param a The right-hand side vector.
  /// @returns A reference to a \c Vector4D object such that \b v =
  /// (<em>x<sub>a</sub></em>, <em>y<sub>a</sub></em>, 0, 1).
  Vector4D& operator=(const Point2D& a);

  /// @brief Adds the \a x, \a y, \a z, and \a w components of the right-hand
  /// side vector \b a to the \a x, \a y, \a z, and \a w components of the
  /// left-hand side vector \b v.
  /// @param a The right-hand side vector.
  /// @returns A reference to a \c Vector4D object such that \b v = \b v + \b a.
  Vector4D& operator+=(const Vector4D& a);

  /// @brief Subtracts the \a x, \a y, \a z, and \a w components of the
  /// right-hand side vector \b a from the \a x, \a y, \a z, and \a w components
  /// of the left-hand side vector \b v.
  /// @param a The right-hand side vector.
  /// @returns A reference to a \c Vector4D object such that \b v = \b v - \b a.
  Vector4D& operator-=(const Vector4D& a);

  /// @brief Multiplies the right-hand side scalar \a n with the \a x, \a y, \a
  /// z, and \a w components of the left-hand side vector \b v.
  /// @param n The right-hand side scalar value.
  /// @returns A reference to a \c Vector4D object such that \b v = \b v ⋅ \a n.
  Vector4D& operator*=(float n);

  /// @brief Divides the \a x, \a y, \a z, and \a w components of the left-hand
  /// side vector \b v with the right-hand side scalar \a n.
  /// @param n The right-hand side scalar value.
  /// @returns A reference to a \c Vector4D object such that \b v = \b v / \a n.
  Vector4D& operator/=(float n);
};

/// @brief Evaluates the dot product between two 4D vectors.
/// <p>
/// The \c Dot function evaluates the component-wise dot product between the
/// four-dimensional vectors \b a and \b b.
/// <p>
/// The return value is a scalar.
/// @param a A four-dimensional vector.
/// @param b A four-dimensional vector.
/// @returns A scalar value such that \a n = \b a ⋅ \b b.
float Dot(const Vector4D& a, const Vector4D& b);

/// @brief Evaluates the magnitude of a 4D vector.
/// <p>
/// The \c Magnitude function evaluates the magnitude (or length, or norm) of
/// the four-dimensional vector \b a.
/// <p>
/// The return value is a scalar.
/// @param a A four-dimensional vector.
/// @returns A scalar value such that ‖ \b a ‖ = √\b a ⋅ \b a.
float Magnitude(const Vector4D& a);

/// @brief Evaluates the inverse magnitude of a 4D vector.
/// <p>
/// The \c InverseMagnitude function evaluates the inverse magnitude (or length,
/// or norm) of the three-dimensional vector \b a.
/// <p>
/// The return value is a scalar.
/// @param a A four-dimensional vector.
/// @returns A scalar value such that 1 / ‖ \b a ‖ = 1 / √\b a ⋅ \b a.
float InverseMagnitude(const Vector4D& a);

/// @brief Evaluates the squared magnitude of a 4D vector.
/// <p>
/// The \c SquaredMagnitude function evaluates the squared magnitude (or length,
/// or norm) of the four-dimensional vector \b a.
/// <p>
/// The return value is a scalar.
/// @param a A four-dimensional vector.
/// @returns A scalar value such that ‖ \b a ‖ <sup>2</sup> = \b a ⋅ \b a.
float SquaredMagnitude(const Vector4D& a);

/// @brief Evaluates the orthogonal projection of a 4D vector.
/// <p>
/// The \c Projection function evaluates the orthogonal projection of the
/// four-dimensional vector \b a onto a straight line parallel to the
/// four-dimensional vector \b b.
/// <p>
/// The return value is a \c Vector4D object.
/// @param a A four-dimensional vector.
/// @param b A four-dimensional vector.
/// @returns A \c Vector4D object such that proj<sub>\a b</sub>\a a = \b b ⋅ \b
/// a ⋅ \b b / \b b ⋅ \b b.
Vector4D Projection(const Vector4D& a, const Vector4D& b);

/// @brief Evaluates the orthogonal rejection of a 4D vector.
/// <p>
/// The \c Rejection function evaluates the orthogonal rejection of the
/// four-dimensional vector \b a onto a straight line parallel to the
/// four-dimensional vector \b b.
/// <p>
/// The return value is a \c Vector4D object.
/// @param a A four-dimensional vector.
/// @param b A four-dimensional vector.
/// @returns A \c Vector4D object such that rej<sub>\a b</sub>\a a = \b a  - \b
/// b ⋅ \b a ⋅ \b b / \b b ⋅ \b b.
Vector4D Rejection(const Vector4D& a, const Vector4D& b);

/// @brief Negates the \a x, \a y, \a z, and \a w components of the vector \a a.
/// @param a A four-dimensional vector.
/// @returns A \c Vector4D object such that \b v = -\b a.
Vector4D operator-(const Vector4D& a);

/// @brief Adds the \a x, \a y, \a z, and \a w components of the vector \b a to
/// the \a x, \a y, \a z, and \a w components of the vector \b b.
/// @param a A four-dimensional vector.
/// @param b A four-dimensional vector.
/// @returns A \c Vector4D object such that \b v = \b a + \b b.
Vector4D operator+(const Vector4D& a, const Vector4D& b);

/// @brief Subtracts the \a x, \a y, \a z, and \a w components of the vector \b
/// b from the \a x, \a y, \a z, and \a w components of the vector \b a.
/// @param a A four-dimensional vector.
/// @param b A four-dimensional vector.
/// @returns A \c Vector4D object such that \b v = \b a - \b b.
Vector4D operator-(const Vector4D& a, const Vector4D& b);

/// @brief Multiplies the \a x, \a y, \a z, and \a w components of the vector \b
/// a with the the scalar \a n.
/// @param n A scalar value.
/// @returns A \c Vector4D object such that \b v = \b a ⋅ \a n.
Vector4D operator*(const Vector4D& a, float n);

/// @brief Multiplies the the scalar \a n with the \a x, \a y, \a z, and \a w
/// components of the vector \b a.
/// @param n A scalar value.
/// @returns A \c Vector4D object such that \b v = \a n ⋅ \b a.
Vector4D operator*(float n, const Vector4D& a);

/// @brief Divides the \a x, \a y, \a z, and \a w components of the vector \b a
/// with the scalar \a n.
/// @param n A scalar value.
/// @returns A \c Vector4D object such that <\b v = \b a / \a n.
Vector4D operator/(const Vector4D& a, float n);

}  // namespace BBMaths

#endif  // BOTTLEBRUSH_ENGINE_VECTOR4D_H_
