#include "Point2D.h"

namespace BBMaths {

Point2D& Point2D::operator=(const Point2D& a) {
  x_ = a.x_;
  y_ = a.y_;
  return (*this);
}

Point2D& Point2D::operator+=(const Point2D& a) {
  x_ += a.x_;
  y_ += a.y_;
  return (*this);
}

Point2D& Point2D::operator-=(const Point2D& a) {
  x_ -= a.x_;
  y_ -= a.y_;
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

Point2D operator-(const Point2D& a) { return {-a.x_, -a.y_}; }

Point2D operator+(const Point2D& a, const Point2D& b) {
  return {a.x_ + b.x_, a.y_ + b.y_};
}

Point2D operator-(const Point2D& a, const Point2D& b) {
  return {a.x_ - b.x_, a.y_ - b.y_};
}

Point2D operator*(const Point2D& a, float n) { return {a.x_ * n, a.y_ * n}; }

Point2D operator*(float n, const Point2D& a) { return {n * a.x_, n * a.y_}; }

Point2D operator/(const Point2D& a, float n) {
  n = 1.0f / n;
  return {a.x_ * n, a.y_ * n};
}

}  // namespace BBMaths
