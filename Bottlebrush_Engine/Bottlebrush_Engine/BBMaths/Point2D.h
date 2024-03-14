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
/// co-ordinates in Euclidean geometric space with real-valued components
/// <i>x</i> and <i>y</i>. A Cartesian point of this class is assumed to have a
/// <i>w</i> co-ordinate of 1 in its four-dimensional representation.
/// Two-dimensional directional vectors, where the <i>w</i> co-ordinate would be
/// 0 in its four-dimensional representation, should be stored using the \c
/// Vector2D class. The <i>z</i> co-ordinate of a two-dimensional point is
/// always assumed to be 0 in any three-dimensional representation.
class Point2D : public Euc2D<TypeEuc2D> {
 public:
  inline Point2D() = default;

  Point2D(float a, float b) : Euc2D<TypeEuc2D>(a, b) {}

  explicit Point2D(const Euc2D<TypeEuc2D>& p) : Euc2D<TypeEuc2D>(p) {}

  Point2D& operator=(const Point2D& p);

  Point2D& operator+=(const Point2D& p);

  Point2D& operator-=(const Point2D& p);

  Point2D& operator*=(float n);

  Point2D& operator/=(float n);
};

Point2D operator-(const Point2D& p);

Point2D operator+(const Point2D& a, const Point2D& b);

Point2D operator-(const Point2D& a, const Point2D& b);

Point2D operator*(const Point2D& p, float n);

Point2D operator*(float n, const Point2D& p);

Point2D operator/(const Point2D& p, float n);
}  // namespace BBMaths

#endif  // BOTTLEBRUSH_ENGINE_POINT2D_H_
