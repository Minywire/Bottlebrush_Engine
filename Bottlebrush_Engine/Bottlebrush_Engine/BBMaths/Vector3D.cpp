#include "engine/maths/Vector3D.h"

namespace BBMaths {
Vector3D& Vector3D::Set(float a, float b, float c) {
  x_ = a;
  y_ = b;
  z_ = c;
  return (*this);
}

Vector3D& Vector3D::Normalise() {
  x_ = x_ * InverseMagnitude(*this);
  y_ = y_ * InverseMagnitude(*this);
  z_ = z_ * InverseMagnitude(*this);
  return (*this);
}

Vector3D& Vector3D::RotateAboutX(float angle) {
  x_ = x_ * Cos(angle) - y_ * Sin(angle);
  y_ = x_ * Sin(angle) + y_ * Cos(angle);
  return (*this);
}

Vector3D& Vector3D::RotateAboutY(float angle) {
  x_ = x_ * Cos(angle) + z_ * Sin(angle);
  z_ = z_ * Cos(angle) - x_ * Sin(angle);
  return (*this);
}

Vector3D& Vector3D::RotateAboutZ(float angle) {
  y_ = y_ * Cos(angle) - z_ * Sin(angle);
  z_ = y_ * Sin(angle) + z_ * Cos(angle);
  return (*this);
}

Vector3D& Vector3D::operator=(const Vector3D& v) {
  x_ = v.x_;
  y_ = v.y_;
  z_ = v.z_;
  return (*this);
}

Vector3D& Vector3D::operator+=(const Vector3D& v) {
  x_ += v.x_;
  y_ += v.y_;
  z_ += v.z_;
  return (*this);
}

Vector3D& Vector3D::operator-=(const Vector3D& v) {
  x_ -= v.x_;
  y_ -= v.y_;
  z_ -= v.z_;
  return (*this);
}

Vector3D& Vector3D::operator*=(float n) {
  x_ *= n;
  y_ *= n;
  z_ *= n;
  return (*this);
}

Vector3D& Vector3D::operator/=(float n) {
  x_ /= n;
  y_ /= n;
  z_ /= n;
  return (*this);
}

float Dot(const Vector3D& a, const Vector3D& b) {
  return (a.x_ * b.x_ + a.y_ * b.y_ + a.z_ * b.z_);
}

Vector3D Cross(const Vector3D& a, const Vector3D& b) {
  return (Vector3D(a.y_ * b.z_ - a.z_ * b.y_, a.z_ * b.x_ - a.x_ * b.z_,
                   a.x_ * b.y_ - a.y_ * b.x_));
}

float Magnitude(const Vector3D& v) {
  return (Sqrt(v.x_ * v.x_ + v.y_ * v.y_ + v.z_ * v.z_));
}

float InverseMagnitude(const Vector3D& v) {
  return (InverseSqrt(v.x_ * v.x_ + v.y_ * v.y_ + v.z_ * v.z_));
}

float SquaredMagnitude(const Vector3D& v) {
  return (v.x_ * v.x_ + v.y_ * v.y_ + v.z_ * v.z_);
}

Vector3D Projection(const Vector3D& a, const Vector3D& b) {
  return (b * Dot(a, b) * 1.0f / Dot(b, b));
}

Vector3D Rejection(const Vector3D& a, const Vector3D& b) {
  return (a - b * Dot(a, b) * 1.0f / Dot(b, b));
}

Vector3D operator-(const Vector3D& v) {
  return (Vector3D(-v.x_, -v.y_, -v.z_));
}

Vector3D operator+(const Vector3D& a, const Vector3D& b) {
  return (Vector3D(a.x_ + b.x_, a.y_ + b.y_, a.z_ + b.z_));
}

Vector3D operator-(const Vector3D& a, const Vector3D& b) {
  return (Vector3D(a.x_ - b.x_, a.y_ - b.y_, a.z_ - b.z_));
}

Vector3D operator*(const Vector3D& v, float n) {
  return (Vector3D(v.x_ * n, v.y_ * n, v.z_ * n));
}

Vector3D operator*(float n, const Vector3D& v) {
  return (Vector3D(n * v.x_, n * v.y_, n * v.z_));
}

Vector3D operator/(const Vector3D& v, float n) {
  n = 1.0f / n;
  return (Vector3D(v.x_ * n, v.y_ * n, v.z_ * n));
}
}  // namespace BBMaths
