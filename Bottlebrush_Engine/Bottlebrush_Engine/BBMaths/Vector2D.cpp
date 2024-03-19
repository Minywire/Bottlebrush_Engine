#include "Vector2D.h"

namespace BBMaths {

Vector2D& Vector2D::Set(float a, float b) {
  x_ = a;
  y_ = b;
  return (*this);
}

Vector2D& Vector2D::Normalise() {
  float n = InverseMagnitude(*this);
  x_ = x_ * n;
  y_ = y_ * n;
  return (*this);
}

Vector2D& Vector2D::Rotate(float angle) {
  float x = x_, y = y_;
  x_ = x * Cos(angle) - y * Sin(angle);
  y_ = x * Sin(angle) + y * Cos(angle);
  return (*this);
}

Vector2D& Vector2D::operator=(const Vector2D& a) {
  x_ = a.x_;
  y_ = a.y_;
  return (*this);
}

Vector2D& Vector2D::operator=(const Point2D& a) {
  x_ = a.x_;
  y_ = a.y_;
  return (*this);
}

Vector2D& Vector2D::operator+=(const Vector2D& a) {
  x_ += a.x_;
  y_ += a.y_;
  return (*this);
}

Vector2D& Vector2D::operator-=(const Vector2D& a) {
  x_ -= a.x_;
  y_ -= a.y_;
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

float Magnitude(const Vector2D& a) { return (Sqrt(a.x_ * a.x_ + a.y_ * a.y_)); }

float InverseMagnitude(const Vector2D& a) {
  return (InverseSqrt(a.x_ * a.x_ + a.y_ * a.y_));
}

float SquaredMagnitude(const Vector2D& a) {
  return (a.x_ * a.x_ + a.y_ * a.y_);
}

Vector2D Projection(const Vector2D& a, const Vector2D& b) {
  return (b * Dot(a, b) * 1.0f / Dot(b, b));
}

Vector2D Rejection(const Vector2D& a, const Vector2D& b) {
  return (a - b * Dot(a, b) * 1.0f / Dot(b, b));
}

Vector2D operator-(const Vector2D& a) { return {-a.x_, -a.y_}; }

Vector2D operator+(const Vector2D& a, const Vector2D& b) {
  return {a.x_ + b.x_, a.y_ + b.y_};
}

Vector2D operator-(const Vector2D& a, const Vector2D& b) {
  return {a.x_ - b.x_, a.y_ - b.y_};
}

Vector2D operator*(const Vector2D& a, float n) { return {a.x_ * n, a.y_ * n}; }

Vector2D operator*(float n, const Vector2D& a) { return {n * a.x_, n * a.y_}; }

Vector2D operator/(const Vector2D& a, float n) {
  n = 1.0f / n;
  return {a.x_ * n, a.y_ * n};
}

}  // namespace BBMaths
