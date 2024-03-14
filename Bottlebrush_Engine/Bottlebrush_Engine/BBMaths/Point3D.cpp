#include "engine/maths/Point3D.h"

namespace BBMaths {
Point3D& Point3D::operator=(const Point3D& p) {
  x_ = p.x_;
  y_ = p.y_;
  z_ = p.z_;
  return (*this);
}

Point3D& Point3D::operator+=(const Point3D& p) {
  x_ += p.x_;
  y_ += p.y_;
  z_ += p.z_;
  return (*this);
}

Point3D& Point3D::operator-=(const Point3D& p) {
  x_ -= p.x_;
  y_ -= p.y_;
  z_ -= p.z_;
  return (*this);
}

Point3D& Point3D::operator*=(float n) {
  x_ *= n;
  y_ *= n;
  z_ *= n;
  return (*this);
}

Point3D& Point3D::operator/=(float n) {
  x_ /= n;
  y_ /= n;
  z_ /= n;
  return (*this);
}

Point3D operator-(const Point3D& p) { return (Point3D(-p.x_, -p.y_, -p.z_)); }

Point3D operator+(const Point3D& a, const Point3D& b) {
  return (Point3D(a.x_ + b.x_, a.y_ + b.y_, a.z_ + b.z_));
}

Point3D operator-(const Point3D& a, const Point3D& b) {
  return (Point3D(a.x_ - b.x_, a.y_ - b.y_, a.z_ - b.z_));
}

Point3D operator*(const Point3D& p, float n) {
  return (Point3D(p.x_ * n, p.y_ * n, p.z_ * n));
}

Point3D operator*(float n, const Point3D& p) {
  return (Point3D(n * p.x_, n * p.y_, n * p.z_));
}

Point3D operator/(const Point3D& p, float n) {
  n = 1.0f / n;
  return (Point3D(p.x_ * n, p.y_ * n, p.z_ * n));
}
}  // namespace BBMaths
