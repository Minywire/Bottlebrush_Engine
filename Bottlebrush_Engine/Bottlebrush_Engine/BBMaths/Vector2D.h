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
/// vectors in Euclidean geometric space with real-valued components \a x and \a
/// y. A directional vector of this class is assumed to have a \a w co-ordinate
/// of 0 in its four-dimensional representation. Two-dimensional points, where
/// the \a w co-ordinate would be 1 in its four-dimensional representation,
/// should be stored using the \c Vector2D class. The \a z co-ordinate of a
/// two-dimensional vector is always assumed to be 0 in any three-dimensional
/// representation.
/// <p>
/// The default constructor leaves the components of the vector undefined. If
/// the values \c a and \c b are provided in the constructor, they are assigned
/// to the \a x and \a y co-ordinates of the point.
/// @see Point2D
/// @author Jaiden di Lanzo
class Vector2D : public Vec2D<TypeVec2D> {
 public:
  inline Vector2D() = default;

  Vector2D(float a, float b) : Vec2D<TypeVec2D>(a, b) {}

  explicit Vector2D(const Vec2D<TypeVec2D>& v) : Vec2D<TypeVec2D>(v) {}

  explicit Vector2D(const Euc2D<TypeEuc2D>& p) : Vec2D<TypeVec2D>(p) {}

  /// @brief Sets both components of the 2D vector.
  /// <p>
  /// The \c Set function sets the \a x and \a y co-ordinates of a
  /// two-dimensional vector to the values given by the parameters \c a and \c
  /// b, respectively.
  /// <p>
  /// The return value is a reference to the \a Vector2D object.
  /// @param a The new \a x co-ordinate.
  /// @param b The new \a y co-ordinate.
  /// @returns A reference to a \c Vector2D object such that \b v = (<em>a</em>,
  /// <em>b</em>).
  Vector2D& Set(float a, float b);

  /// @brief Normalises the 2D vector.
  /// <p>
  /// The \c Normalise function normalises a two-dimensional vector to unit
  /// length, multiplying its components by the inverse of its magnitude.
  /// Normalising the zero vector produces undefined results.
  /// <p>
  /// The return value is a reference to the \c Vector2D object.
  /// @returns A reference to a \c Vector2D object such that \b v = \b v / ‖ \b
  /// v ‖.
  Vector2D& Normalise();

  /// @brief Rotates the 2D vector in the \a x-y plane.
  /// <p>
  /// The \c Rotate function rotates a two-dimensional vector in the \a x-y
  /// plane through the angle \a θ given by the \c angle parameter.
  /// <p>
  /// The return value is a reference to the \c Vector2D object.
  /// @param angle The angle, in radians, through which the vector is rotated.
  /// @returns A reference to a \c Vector2D object such that \b v = (\a x cos \a
  /// θ - \a y sin \a θ, \a x sin \a θ + \a y cos \a θ).
  Vector2D& Rotate(float angle);

  /// @brief Assigns the \a x and \a y components of the right-hand side vector
  /// \b a to the \a x and \a y components of the left-hand side vector \b v.
  /// @param a The right-hand side vector.
  /// @returns A reference to a \c Vector2D object such that \b v =
  /// (<em>x<sub>a</sub></em>, <em>y<sub>a</sub></em>).
  Vector2D& operator=(const Vector2D& a);

  /// @brief Assigns the \a x and \a y components of the right-hand side point
  /// \a p to the \a x and \a y components of the left-hand side vector \b v.
  /// @param p The right-hand side point.
  /// @returns A reference to a \c Vector2D object such that \b v =
  /// (<em>x<sub>a</sub></em>, <em>y<sub>a</sub></em>).
  Vector2D& operator=(const Point2D& a);

  /// @brief Adds the \a x and \a y components of the right-hand side vector \b
  /// a to the \a x and \a y components of the left-hand side vector \b v.
  /// @param a The right-hand side vector.
  /// @returns A reference to a \c Vector2D object such that \b v = \b v + \b a.
  Vector2D& operator+=(const Vector2D& a);

  /// @brief Subtracts the \a x and \a y components of the right-hand side
  /// vector \b a from the \a x and \a y components of the left-hand side vector
  /// \b v.
  /// @param a The right-hand side vector.
  /// @returns A reference to a \c Vector2D object such that \b v = \b v - \b a.
  Vector2D& operator-=(const Vector2D& a);

  /// @brief Multiplies the right-hand side scalar \a n with the \a x and \a y
  /// components of the left-hand side vector \b v.
  /// @param n The right-hand side scalar value.
  /// @returns A reference to a \c Vector2D object such that \b v = \b v ⋅ \a n.
  Vector2D& operator*=(float n);

  /// @brief Divides the \a x and \a y components of the left-hand side vector
  /// \b v with the right-hand side scalar \a n.
  /// @param n The right-hand side scalar value.
  /// @returns A reference to a \c Vector2D object such that \b v = \b v / \a n.
  Vector2D& operator/=(float n);
};

/// @brief Evaluates the dot product between two 2D vectors.
/// <p>
/// The \c Dot function evaluates the component-wise dot product between the
/// two-dimensional vectors \b a and \b b.
/// <p>
/// The return value is a scalar.
/// @param a A two-dimensional vector.
/// @param b A two-dimensional vector.
/// @returns A scalar value such that \a n = \b a ⋅ \b b.
float Dot(const Vector2D& a, const Vector2D& b);

/// @brief Evaluates the magnitude of a 2D vector.
/// <p>
/// The \c Magnitude function evaluates the magnitude (or length, or norm) of
/// the two-dimensional vector \b a.
/// <p>
/// The return value is a scalar.
/// @param a A two-dimensional vector.
/// @returns A scalar value such that ‖ \b a ‖ = √\b a ⋅ \b a.
float Magnitude(const Vector2D& a);

/// @brief Evaluates the inverse magnitude of a 2D vector.
/// <p>
/// The \c InverseMagnitude function evaluates the inverse magnitude (or length,
/// or norm) of the two-dimensional vector \b a.
/// <p>
/// The return value is a scalar.
/// @param a A two-dimensional vector.
/// @returns A scalar value such that 1 / ‖ \b a ‖ = 1 / √\b a ⋅ \b a.
float InverseMagnitude(const Vector2D& a);

/// @brief Evaluates the squared magnitude of a 2D vector.
/// <p>
/// The \c SquaredMagnitude function evaluates the squared magnitude (or length,
/// or norm) of the two-dimensional vector \b a.
/// <p>
/// The return value is a scalar.
/// @param a A two-dimensional vector.
/// @returns A scalar value such that ‖ \b a ‖ <sup>2</sup> = \b a ⋅ \b a.
float SquaredMagnitude(const Vector2D& a);

/// @brief Evaluates the orthogonal projection of a 2D vector.
/// <p>
/// The \c Projection function evaluates the orthogonal projection of the
/// two-dimensional vector \b a onto a straight line parallel to the
/// two-dimensional vector \b b.
/// <p>
/// The return value is a \c Vector2D object.
/// @param a A two-dimensional vector.
/// @param b A two-dimensional vector.
/// @returns A \c Vector2D object such that proj<sub>\a b</sub>\a a = \b b ⋅ \b
/// a ⋅ \b b / \b b ⋅ \b b.
Vector2D Projection(const Vector2D& a, const Vector2D& b);

/// @brief Evaluates the orthogonal rejection of a 2D vector.
/// <p>
/// The \c Rejection function evaluates the orthogonal rejection of the
/// two-dimensional vector \b a onto a straight line parallel to the
/// two-dimensional vector \b b.
/// <p>
/// The return value is a \c Vector2D object.
/// @param a A two-dimensional vector.
/// @param b A two-dimensional vector.
/// @returns A \c Vector2D object such that rej<sub>\a b</sub>\a a = \b a  - \b
/// b ⋅ \b a ⋅ \b b / \b b ⋅ \b b.
Vector2D Rejection(const Vector2D& a, const Vector2D& b);

/// @brief Negates the \a x and \a y components of the vector \a a.
/// @param a A two-dimensional vector.
/// @returns A \c Vector2D object such that \b v = -\b a.
Vector2D operator-(const Vector2D& a);

/// @brief Adds the \a x and \a y components of the vector \b a to the \a x and
/// \a y components of the vector \b b.
/// @param a A two-dimensional vector.
/// @param b A two-dimensional vector.
/// @returns A \c Vector2D object such that \b v = \b a + \b b.
Vector2D operator+(const Vector2D& a, const Vector2D& b);

/// @brief Subtracts the \a x and \a y components of the vector \b b from the \a
/// x and \a y components of the vector \b a.
/// @param a A two-dimensional vector.
/// @param b A two-dimensional vector.
/// @returns A \c Vector2D object such that \b v = \b a - \b b.
Vector2D operator-(const Vector2D& a, const Vector2D& b);

/// @brief Multiplies the \a x and \a y components of the vector \b a with the
/// the scalar \a n.
/// @param n A scalar value.
/// @returns A \c Vector2D object such that \b v = \b a ⋅ \a n.
Vector2D operator*(const Vector2D& a, float n);

/// @brief Multiplies the the scalar \a n with the \a x and \a y components of
/// the vector \b a.
/// @param n A scalar value.
/// @returns A \c Vector2D object such that \b v = \a n ⋅ \b a.
Vector2D operator*(float n, const Vector2D& a);

/// @brief Divides the \a x and \a y components of the vector \b a with the
/// scalar \a n.
/// @param n A scalar value.
/// @returns A \c Vector2D object such that <\b v = \b a / \a n.
Vector2D operator/(const Vector2D& a, float n);

}  // namespace BBMaths

#endif  // BOTTLEBRUSH_ENGINE_VECTOR2D_H_
