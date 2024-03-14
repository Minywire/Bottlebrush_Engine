#include "Point2D.h"

namespace BBMaths {
Point2D& Point2D::operator=(const Point2D& p) {
  x_ = p.x_;
  y_ = p.y_;
  return (*this);
}

Point2D& Point2D::operator+=(const Point2D& p) {
  x_ += p.x_;
  y_ += p.y_;
  return (*this);
}

Point2D& Point2D::operator-=(const Point2D& p) {
  x_ -= p.x_;
  y_ -= p.y_;
  return (*this);
}

Point2D& Point2D::operator*=(float n) {
  x_ *= n;
  y_ *= n;
  return (*this);
}

Point2D& Point2D::operator/=(float n) {
  x_ /= n;
  y_ /= n;
  return (*this);
}

Point2D operator-(const Point2D& p) { return {-p.x_, -p.y_}; }

Point2D operator+(const Point2D& a, const Point2D& b) {
  return {a.x_ + b.x_, a.y_ + b.y_};
}

Point2D operator-(const Point2D& a, const Point2D& b) {
  return {a.x_ - b.x_, a.y_ - b.y_};
}

Point2D operator*(const Point2D& p, float n) { return {p.x_ * n, p.y_ * n}; }

Point2D operator*(float n, const Point2D& p) { return {n * p.x_, n * p.y_}; }

Point2D operator/(const Point2D& p, float n) {
  n = 1.0f / n;
  return {p.x_ * n, p.y_ * n};
}
}  // namespace BBMaths
