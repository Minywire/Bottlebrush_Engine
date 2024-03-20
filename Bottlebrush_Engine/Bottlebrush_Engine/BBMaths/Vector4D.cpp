#include "Vector4D.h"

namespace BBMaths {

Vector4D& Vector4D::Set(float a, float b, float c, float d) {
  x_ = a;
  y_ = b;
  z_ = c;
  w_ = d;
  return (*this);
}

Vector4D& Vector4D::Normalise() {
  float n = InverseMagnitude(*this);
  x_ = x_ * n;
  y_ = y_ * n;
  z_ = z_ * n;
  w_ = w_ * n;
  return (*this);
}

Vector4D& Vector4D::RotateAboutX(float angle) {
  float y = y_, z = z_;
  y_ = y * Cos(angle) - z * Sin(angle);
  z_ = y * Sin(angle) + z * Cos(angle);
  return (*this);
}

Vector4D& Vector4D::RotateAboutY(float angle) {
  float x = x_, z = z_;
  x_ = x * Cos(angle) + z * Sin(angle);
  z_ = z * Cos(angle) - x * Sin(angle);
  return (*this);
}

Vector4D& Vector4D::RotateAboutZ(float angle) {
  float x = x_, y = y_;
  x_ = x * Cos(angle) - y * Sin(angle);
  y_ = x * Sin(angle) + y * Cos(angle);
  return (*this);
}

Vector4D& Vector4D::operator=(const Vector4D& a) {
  x_ = a.x_;
  y_ = a.y_;
  z_ = a.z_;
  w_ = a.w_;
  return (*this);
}

Vector4D& Vector4D::operator=(const Vector3D& a) {
  x_ = a.x_;
  y_ = a.y_;
  z_ = a.z_;
  w_ = 0.0f;
  return (*this);
}

Vector4D& Vector4D::operator=(const Point3D& a) {
  x_ = a.x_;
  y_ = a.y_;
  z_ = a.z_;
  w_ = 1.0f;
  return (*this);
}

Vector4D& Vector4D::operator=(const Vector2D& a) {
  x_ = a.x_;
  y_ = a.y_;
  z_ = 0.0f;
  w_ = 0.0f;
  return (*this);
}

Vector4D& Vector4D::operator=(const Point2D& a) {
  x_ = a.x_;
  y_ = a.y_;
  z_ = 0.0f;
  w_ = 1.0f;
  return (*this);
}

Vector4D& Vector4D::operator+=(const Vector4D& a) {
  x_ += a.x_;
  y_ += a.y_;
  z_ += a.z_;
  w_ += a.w_;
  return (*this);
}

Vector4D& Vector4D::operator-=(const Vector4D& a) {
  x_ -= a.x_;
  y_ -= a.y_;
  z_ -= a.z_;
  w_ -= a.w_;
  return (*this);
}

Vector4D& Vector4D::operator*=(float n) {
  x_ *= n;
  y_ *= n;
  z_ *= n;
  w_ *= n;
  return (*this);
}

Vector4D& Vector4D::operator/=(float n) {
  x_ /= n;
  y_ /= n;
  z_ /= n;
  w_ /= n;
  return (*this);
}

float Dot(const Vector4D& a, const Vector4D& b) {
  return (a.x_ * b.x_ + a.y_ * b.y_ + a.z_ * b.z_ + a.w_ * b.w_);
}

float Magnitude(const Vector4D& a) {
  return (Sqrt(a.x_ * a.x_ + a.y_ * a.y_ + a.z_ * a.z_ + a.w_ * a.w_));
}

float InverseMagnitude(const Vector4D& a) {
  return (InverseSqrt(a.x_ * a.x_ + a.y_ * a.y_ + a.z_ * a.z_ + a.w_ * a.w_));
}

float SquaredMagnitude(const Vector4D& a) {
  return (a.x_ * a.x_ + a.y_ * a.y_ + a.z_ * a.z_ + a.w_ * a.w_);
}

Vector4D Projection(const Vector4D& a, const Vector4D& b) {
  return (b * Dot(a, b) * 1.0f / Dot(b, b));
}

Vector4D Rejection(const Vector4D& a, const Vector4D& b) {
  return (a - b * Dot(a, b) * 1.0f / Dot(b, b));
}

Vector4D operator-(const Vector4D& a) { return {-a.x_, -a.y_, -a.z_, -a.w_}; }

Vector4D operator+(const Vector4D& a, const Vector4D& b) {
  return {a.x_ + b.x_, a.y_ + b.y_, a.z_ + b.z_, a.w_ + b.w_};
}

Vector4D operator-(const Vector4D& a, const Vector4D& b) {
  return {a.x_ - b.x_, a.y_ - b.y_, a.z_ - b.z_, a.w_ - b.w_};
}

Vector4D operator*(const Vector4D& a, float n) {
  return {a.x_ * n, a.y_ * n, a.z_ * n, a.w_ * n};
}

Vector4D operator*(float n, const Vector4D& a) {
  return {n * a.x_, n * a.y_, n * a.z_, n * a.w_};
}

Vector4D operator/(const Vector4D& a, float n) {
  n = 1.0f / n;
  return {a.x_ * n, a.y_ * n, a.z_ * n, a.w_ * n};
}

}  // namespace BBMaths
