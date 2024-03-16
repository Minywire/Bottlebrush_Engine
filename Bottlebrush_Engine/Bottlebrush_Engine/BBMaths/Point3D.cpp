#include "Point3D.h"

namespace BBMaths {

Point3D& Point3D::operator=(const Point3D& a) {
  x_ = a.x_;
  y_ = a.y_;
  z_ = a.z_;
  return (*this);
}

Point3D& Point3D::operator+=(const Point3D& a) {
  x_ += a.x_;
  y_ += a.y_;
  z_ += a.z_;
  return (*this);
}

Point3D& Point3D::operator-=(const Point3D& a) {
  x_ -= a.x_;
  y_ -= a.y_;
  z_ -= a.z_;
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

Point3D operator-(const Point3D& a) { return {-a.x_, -a.y_, -a.z_}; }

Point3D operator+(const Point3D& a, const Point3D& b) {
  return {a.x_ + b.x_, a.y_ + b.y_, a.z_ + b.z_};
}

Point3D operator-(const Point3D& a, const Point3D& b) {
  return {a.x_ - b.x_, a.y_ - b.y_, a.z_ - b.z_};
}

Point3D operator*(const Point3D& a, float n) {
  return {a.x_ * n, a.y_ * n, a.z_ * n};
}

Point3D operator*(float n, const Point3D& a) {
  return {n * a.x_, n * a.y_, n * a.z_};
}

Point3D operator/(const Point3D& a, float n) {
  n = 1.0f / n;
  return {a.x_ * n, a.y_ * n, a.z_ * n};
}

}  // namespace BBMaths
