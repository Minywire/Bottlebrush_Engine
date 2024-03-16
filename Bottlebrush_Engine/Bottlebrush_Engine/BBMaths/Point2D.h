#ifndef BOTTLEBRUSH_ENGINE_POINT2D_H_
#define BOTTLEBRUSH_ENGINE_POINT2D_H_

namespace BBMaths {

typedef float TypeEuc2D;

/// @class Euc2D
/// @brief Points use a generic base class to store their components.
template <typename T>
class Euc2D {
 public:
  T x_;
  T y_;

 protected:
  inline Euc2D() = default;

  Euc2D(const T& a, const T& b) {
    x_ = a;
    y_ = b;
  }

  explicit Euc2D(const Euc2D<TypeEuc2D>& p) {
    x_ = p.x_;
    y_ = p.y_;
  }
};

/// @class Point2D
/// @brief The \c Point2D class encapsulates a 2D point.
///
/// The \c Point2D class is used to represent singular two-dimensional Cartesian
/// co-ordinates in Euclidean geometric space with real-valued components \a x
/// and \a y. A Cartesian point of this class is assumed to have a \a w
/// co-ordinate of 1 in its four-dimensional representation. Two-dimensional
/// directional vectors, where the \a w co-ordinate would be 0 in its
/// four-dimensional representation, should be stored using the \c Vector2D
/// class. The \a z co-ordinate of a two-dimensional point is always assumed
/// to be 0 in any three-dimensional or four-dimensional representation.
/// <p>
/// The default constructor leaves the components of the point undefined. If the
/// values \c a and \c b are provided in the constructor, they are assigned to
/// the \a x and \a y co-ordinates of the point.
/// @see Vector2D
/// @author Jaiden di Lanzo
class Point2D : public Euc2D<TypeEuc2D> {
 public:
  inline Point2D() = default;

  Point2D(float a, float b) : Euc2D<TypeEuc2D>(a, b) {}

  explicit Point2D(const Euc2D<TypeEuc2D>& p) : Euc2D<TypeEuc2D>(p) {}

  /// @brief Assigns the \a x and \a y components of the right-hand side point
  /// \a a to the \a x and \a y components of the left-hand side point \a p.
  /// @param a The right-hand side point.
  /// @returns A reference to a \c Point2D object such that \a p =
  /// (<em>x<sub>a</sub></em>, <em>y<sub>a</sub></em>).
  Point2D& operator=(const Point2D& a);

  /// @brief Adds the \a x and \a y components of the right-hand side point \a a
  /// to the \a x and \a y components of the left-hand side point \a p.
  /// @param a The right-hand side point.
  /// @returns A reference to a \c Point2D object such that \a p = \a p + \a a.
  Point2D& operator+=(const Point2D& a);

  /// @brief Subtracts the \a x and \a y components of the right-hand side point
  /// \a a from the \a x and \a y components of the left-hand side point \a p.
  /// @param a The right-hand side point.
  /// @returns A reference to a \c Point2D object such that \a p = \a p - \a a.
  Point2D& operator-=(const Point2D& a);

  /// @brief Multiplies the right-hand side scalar \a n with the \a x and \a y
  /// components of the left-hand side point \a p.
  /// @param n The right-hand side scalar value.
  /// @returns A reference to a \c Point2D object such that \a p = \a p ⋅ \a n.
  Point2D& operator*=(float n);

  /// @brief Divides the \a x and \a y components of the left-hand side point \a
  /// p with the right-hand side scalar \a n.
  /// @param n The right-hand side scalar value.
  /// @returns A reference to a \c Point2D object such that \a p = \a p / \a n.
  Point2D& operator/=(float n);
};

/// @brief Negates the \a x and \a y components of the point \a a.
/// @param a A two-dimensional point.
/// @returns A \c Point2D object such that \a p = -\a a.
Point2D operator-(const Point2D& a);

/// @brief Adds the \a x and \a y components of the point \a a to the \a x and
/// \a y components of the point \a b.
/// @param a A two-dimensional point.
/// @param b A two-dimensional point.
/// @returns A \c Point2D object such that \a p = \a a + \a b.
Point2D operator+(const Point2D& a, const Point2D& b);

/// @brief Subtracts the \a x and \a y components of the point \a b from the \a
/// x and \a y components of the point \a a.
/// @param a A two-dimensional point.
/// @param b A two-dimensional point.
/// @returns A \c Point2D object such that \a p = \a a - \a b.
Point2D operator-(const Point2D& a, const Point2D& b);

/// @brief Multiplies the \a x and \a y components of the point \a p with the
/// the scalar \a n.
/// @param n A scalar value.
/// @returns A \c Point2D object such that \a p = \a a ⋅ \a n.
Point2D operator*(const Point2D& a, float n);

/// @brief Multiplies the the scalar \a n with the \a x and \a y components of
/// the point \a p.
/// @param n A scalar value.
/// @returns A \c Point2D object such that \a p = \a n ⋅ \a a.
Point2D operator*(float n, const Point2D& a);

/// @brief Divides the \a x and \a y components of the point \a p with the
/// scalar \a n.
/// @param n A scalar value.
/// @returns A \c Point2D object such that \a p = \a a / \a n.
Point2D operator/(const Point2D& a, float n);

}  // namespace BBMaths

#endif  // BOTTLEBRUSH_ENGINE_POINT2D_H_
