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
/// components <i>x</i>, <i>y</i>, and <i>z</i>. A Cartesian point of this class
/// is assumed to have a <i>w</i> co-ordinate of 1 in its four-dimensional
/// representation. Three-dimensional directional vectors, where the <i>w</i>
/// co-ordinate would be 0 in its four-dimensional representation, should be
/// stored using the \c Vector3D class.
class Point3D : public Euc3D<TypeEuc3D> {
 public:
  inline Point3D() = default;

  Point3D(float a, float b, float c) : Euc3D<TypeEuc3D>(a, b, c) {}

  Point3D(const Euc3D<TypeEuc3D>& p) : Euc3D<TypeEuc3D>(p) {}

  Point3D& operator=(const Point3D& p);

  Point3D& operator+=(const Point3D& p);

  Point3D& operator-=(const Point3D& p);

  Point3D& operator*=(float n);

  Point3D& operator/=(float n);
};

Point3D operator-(const Point3D& p);

Point3D operator+(const Point3D& a, const Point3D& b);

Point3D operator-(const Point3D& a, const Point3D& b);

Point3D operator*(const Point3D& p, float n);

Point3D operator*(float n, const Point3D& p);

Point3D operator/(const Point3D& p, float n);
}  // namespace BBMaths

#endif  // BOTTLEBRUSH_ENGINE_POINT3D_H_
