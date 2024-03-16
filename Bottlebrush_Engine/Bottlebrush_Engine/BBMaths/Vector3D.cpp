#include "Vector3D.h"

namespace BBMaths {

Vector3D& Vector3D::Set(float a, float b, float c) {
  x_ = a;
  y_ = b;
  z_ = c;
  return (*this);
}

Vector3D& Vector3D::Normalise() {
  float n = InverseMagnitude(*this);
  x_ = x_ * n;
  y_ = y_ * n;
  z_ = z_ * n;
  return (*this);
}

Vector3D& Vector3D::RotateAboutX(float angle) {
  float y = y_, z = z_;
  y_ = y * Cos(angle) - z * Sin(angle);
  z_ = y * Sin(angle) + z * Cos(angle);
  return (*this);
}

Vector3D& Vector3D::RotateAboutY(float angle) {
  float x = x_, z = z_;
  x_ = x * Cos(angle) + z * Sin(angle);
  z_ = z * Cos(angle) - x * Sin(angle);
  return (*this);
}

Vector3D& Vector3D::RotateAboutZ(float angle) {
  float x = x_, y = y_;
  x_ = x * Cos(angle) - y * Sin(angle);
  y_ = x * Sin(angle) + y * Cos(angle);
  return (*this);
}

Vector3D& Vector3D::operator=(const Vector3D& a) {
  x_ = a.x_;
  y_ = a.y_;
  z_ = a.z_;
  return (*this);
}

Vector3D& Vector3D::operator=(const Point3D& a) {
  x_ = a.x_;
  y_ = a.y_;
  z_ = a.z_;
  return (*this);
}

Vector3D& Vector3D::operator=(const Vector2D& a) {
  x_ = a.x_;
  y_ = a.y_;
  z_ = 1.0f;
  return (*this);
}

Vector3D& Vector3D::operator=(const Point2D& a) {
  x_ = a.x_;
  y_ = a.y_;
  z_ = 0.0f;
  return (*this);
}

Vector3D& Vector3D::operator+=(const Vector3D& a) {
  x_ += a.x_;
  y_ += a.y_;
  z_ += a.z_;
  return (*this);
}

Vector3D& Vector3D::operator-=(const Vector3D& a) {
  x_ -= a.x_;
  y_ -= a.y_;
  z_ -= a.z_;
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
  return {a.y_ * b.z_ - a.z_ * b.y_, a.z_ * b.x_ - a.x_ * b.z_,
          a.x_ * b.y_ - a.y_ * b.x_};
}

float Magnitude(const Vector3D& a) {
  return (Sqrt(a.x_ * a.x_ + a.y_ * a.y_ + a.z_ * a.z_));
}

float InverseMagnitude(const Vector3D& a) {
  return (InverseSqrt(a.x_ * a.x_ + a.y_ * a.y_ + a.z_ * a.z_));
}

float SquaredMagnitude(const Vector3D& a) {
  return (a.x_ * a.x_ + a.y_ * a.y_ + a.z_ * a.z_);
}

Vector3D Projection(const Vector3D& a, const Vector3D& b) {
  return (b * Dot(a, b) * 1.0f / Dot(b, b));
}

Vector3D Rejection(const Vector3D& a, const Vector3D& b) {
  return (a - b * Dot(a, b) * 1.0f / Dot(b, b));
}

Vector3D operator-(const Vector3D& a) { return {-a.x_, -a.y_, -a.z_}; }

Vector3D operator+(const Vector3D& a, const Vector3D& b) {
  return {a.x_ + b.x_, a.y_ + b.y_, a.z_ + b.z_};
}

Vector3D operator-(const Vector3D& a, const Vector3D& b) {
  return {a.x_ - b.x_, a.y_ - b.y_, a.z_ - b.z_};
}

Vector3D operator*(const Vector3D& a, float n) {
  return {a.x_ * n, a.y_ * n, a.z_ * n};
}

Vector3D operator*(float n, const Vector3D& a) {
  return {n * a.x_, n * a.y_, n * a.z_};
}

Vector3D operator/(const Vector3D& a, float n) {
  n = 1.0f / n;
  return {a.x_ * n, a.y_ * n, a.z_ * n};
}

}  // namespace BBMaths
