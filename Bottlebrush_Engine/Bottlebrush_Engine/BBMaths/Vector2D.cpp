#include "Vector2D.h"

namespace BBMaths {
Vector2D& Vector2D::Set(float a, float b) {
  x_ = a;
  y_ = b;
  return (*this);
}

Vector2D& Vector2D::Normalise() {
  x_ = x_ * InverseMagnitude(*this);
  y_ = y_ * InverseMagnitude(*this);
  return (*this);
}

Vector2D& Vector2D::Rotate(float angle) {
  x_ = x_ * Cos(angle) - y_ * Sin(angle);
  y_ = x_ * Sin(angle) + y_ * Cos(angle);
  return (*this);
}

Vector2D& Vector2D::operator=(const Vector2D& v) {
  x_ = v.x_;
  y_ = v.y_;
  return (*this);
}

Vector2D& Vector2D::operator+=(const Vector2D& v) {
  x_ += v.x_;
  y_ += v.y_;
  return (*this);
}

Vector2D& Vector2D::operator-=(const Vector2D& v) {
  x_ -= v.x_;
  y_ -= v.y_;
  return (*this);
}

Vector2D& Vector2D::operator*=(float n) {
  x_ *= n;
  y_ *= n;
  return (*this);
}

Vector2D& Vector2D::operator/=(float n) {
  x_ /= n;
  y_ /= n;
  return (*this);
}

float Dot(const Vector2D& a, const Vector2D& b) {
  return (a.x_ * b.x_ + a.y_ * b.y_);
}

float Magnitude(const Vector2D& v) { return (Sqrt(v.x_ * v.x_ + v.y_ * v.y_)); }

float InverseMagnitude(const Vector2D& v) {
  return (InverseSqrt(v.x_ * v.x_ + v.y_ * v.y_));
}

float SquaredMagnitude(const Vector2D& v) {
  return (v.x_ * v.x_ + v.y_ * v.y_);
}

Vector2D Projection(const Vector2D& a, const Vector2D& b) {
  return (b * Dot(a, b) * 1.0f / Dot(b, b));
}

Vector2D Rejection(const Vector2D& a, const Vector2D& b) {
  return (a - b * Dot(a, b) * 1.0f / Dot(b, b));
}

Vector2D operator-(const Vector2D& v) { return {-v.x_, -v.y_}; }

Vector2D operator+(const Vector2D& a, const Vector2D& b) {
  return {a.x_ + b.x_, a.y_ + b.y_};
}

Vector2D operator-(const Vector2D& a, const Vector2D& b) {
  return {a.x_ - b.x_, a.y_ - b.y_};
}

Vector2D operator*(const Vector2D& v, float n) { return {v.x_ * n, v.y_ * n}; }

Vector2D operator*(float n, const Vector2D& v) { return {n * v.x_, n * v.y_}; }

Vector2D operator/(const Vector2D& v, float n) {
  n = 1.0f / n;
  return {v.x_ * n, v.y_ * n};
}
}  // namespace BBMaths
