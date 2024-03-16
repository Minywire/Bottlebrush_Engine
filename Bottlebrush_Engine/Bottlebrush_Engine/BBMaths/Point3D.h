#ifndef BOTTLEBRUSH_ENGINE_POINT3D_H_
#define BOTTLEBRUSH_ENGINE_POINT3D_H_

namespace BBMaths {

typedef float TypeEuc3D;

/// @class Euc3D
/// @brief Points use a generic base class to store their components.
template <typename T>
class Euc3D {
 public:
  T x_;
  T y_;
  T z_;

 protected:
  inline Euc3D() = default;

  Euc3D(const T& a, const T& b, const T& c) {
    x_ = a;
    y_ = b;
    z_ = c;
  }

  explicit Euc3D(const Euc3D<TypeEuc3D>& p) {
    x_ = p.x_;
    y_ = p.y_;
    z_ = p.z_;
  }
};

/// @class Point3D
/// @brief The \c Point3D class encapsulates a 3D point.
///
/// The \c Point3D class is used to represent singular three-dimensional
/// Cartesian co-ordinates in Euclidean geometric space with real-valued
/// components \a x, \a y, and \a z. A Cartesian point of this class is assumed
/// to have a \a w co-ordinate of 1 in its four-dimensional representation.
/// Three-dimensional directional vectors, where the \a w co-ordinate would be 0
/// in its four-dimensional representation, should be stored using the \c
/// Vector3D class.
/// <p>
/// The default constructor leaves the components of the point undefined. If the
/// values \c a, \c b, and \c c are provided in the constructor, they are
/// assigned to the \a x, \a y, and /a z co-ordinates of the point.
/// @see Vector3D
/// @author Jaiden di Lanzo
class Point3D : public Euc3D<TypeEuc3D> {
 public:
  inline Point3D() = default;

  Point3D(float a, float b, float c) : Euc3D<TypeEuc3D>(a, b, c) {}

  explicit Point3D(const Euc3D<TypeEuc3D>& p) : Euc3D<TypeEuc3D>(p) {}

  /// @brief Assigns the \a x, \a y, and \a z components of the right-hand side
  /// point \a a to the \a x, \a y, and \a z components of the left-hand side
  /// point \a p.
  /// @param a The right-hand side point.
  /// @returns A reference to a \c Point3D object such that \a p =
  /// (<em>x<sub>a</sub></em>, <em>y<sub>a</sub></em>, <em>z<sub>a</sub></em>).
  Point3D& operator=(const Point3D& a);

  /// @brief Adds the \a x, \a y, and \a z components of the right-hand side
  /// point \a a to the \a x, \a y, and \a z components of the left-hand side
  /// point \a p.
  /// @param a The right-hand side point.
  /// @returns A reference to a \c Point3D object such that \a p = \a p + \a a.
  Point3D& operator+=(const Point3D& a);

  /// @brief Subtracts the \a x, \a y, and \a z components of the right-hand
  /// side point \a a from the \a x, \a y, and \a z components of the left-hand
  /// side point \a p.
  /// @param a The right-hand side point.
  /// @returns A reference to a \c Point3D object such that \a p = \a p - \a a.
  Point3D& operator-=(const Point3D& a);

  /// @brief Multiplies the right-hand side scalar \a n with the \a x, \a y, and
  /// \a z components of the left-hand side point \a p.
  /// @param n The right-hand side scalar value.
  /// @returns A reference to a \c Point3D object such that \a p = \a p ⋅ \a n.
  Point3D& operator*=(float n);

  /// @brief Divides the \a x, \a y, and \a z components of the left-hand side
  /// point \a p with the right-hand side scalar \a n.
  /// @param n The right-hand side scalar value.
  /// @returns A reference to a \c Point3D object such that \a p = \a p / \a n.
  Point3D& operator/=(float n);
};

/// @brief Negates the \a x, \a y, and \a z components of the point \a a.
/// @param a A three-dimensional point.
/// @returns A \c Point3D object such that \a p = -\a a.
Point3D operator-(const Point3D& a);

/// @brief Adds the \a x, \a y, and \a z components of the point \a a to the \a
/// x, \a y, and \a z components of the point \a b.
/// @param a A three-dimensional point.
/// @param b A three-dimensional point.
/// @returns A \c Point3D object such that \a p = \a a + \a b.
Point3D operator+(const Point3D& a, const Point3D& b);

/// @brief Subtracts the \a x, \a y, and \a z components of the point \a b from
/// the \a x, \a y, and \a z components of the point \a a.
/// @param a A three-dimensional point.
/// @param b A three-dimensional point.
/// @returns A \c Point3D object such that \a p = \a a - \a b.
Point3D operator-(const Point3D& a, const Point3D& b);

/// @brief Multiplies the \a x, \a y, and \a z components of the point \a p with
/// the the scalar \a n.
/// @param n A scalar value.
/// @returns A \c Point3D object such that \a p = \a a ⋅ \a n.
Point3D operator*(const Point3D& a, float n);

/// @brief Multiplies the the scalar \a n with the \a x, \a y, and \a z
/// components of the point \a p.
/// @param n A scalar value.
/// @returns A \c Point3D object such that \a p = \a n ⋅ \a a.
Point3D operator*(float n, const Point3D& a);

/// @brief Divides the \a x, \a y, and \a z components of the point \a p with
/// the scalar \a n.
/// @param n A scalar value.
/// @returns A \c Point3D object such that \a p = \a a / \a n.
Point3D operator/(const Point3D& a, float n);

}  // namespace BBMaths

#endif  // BOTTLEBRUSH_ENGINE_POINT3D_H_
