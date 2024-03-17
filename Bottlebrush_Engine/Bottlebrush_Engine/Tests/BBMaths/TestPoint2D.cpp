#include <tuple>

#include "Point2D.h"
#include "gtest/gtest.h"

namespace TestBBMaths::TestPoint2D {

using namespace BBMaths;

const float kStart = -0.1f, kEnd = 0.1f, kStep = 0.1f, kTolerance = 0.0001f;

class TestPoint2D : public ::testing::TestWithParam<std::tuple<float, float>> {
};

INSTANTIATE_TEST_SUITE_P(
    Points, TestPoint2D,
    testing::Combine(testing::Range(kStart, kEnd + kStep, kStep),
                     testing::Range(kStart, kEnd + kStep, kStep)));

TEST_P(TestPoint2D, TestAltCtor) {
  float a = std::get<0>(GetParam()), b = std::get<1>(GetParam());

  Point2D p = Point2D(a, b);

  EXPECT_EQ(a, p.x_);
  EXPECT_EQ(b, p.y_);
}

TEST_P(TestPoint2D, TestCopyCtor) {
  float a = std::get<0>(GetParam()), b = std::get<1>(GetParam());

  Point2D p = Point2D(a, b), q = Point2D(p);

  EXPECT_EQ(p.x_, q.x_);
  EXPECT_EQ(p.y_, q.y_);
}

TEST_P(TestPoint2D, TestAssignOp) {
  float a = std::get<0>(GetParam()), b = std::get<1>(GetParam());

  Point2D p = Point2D(a, b), q = p;

  EXPECT_EQ(p.x_, q.x_);
  EXPECT_EQ(p.y_, q.y_);
}

TEST_P(TestPoint2D, TestAddAssignOp) {
  float a = std::get<0>(GetParam()), b = std::get<1>(GetParam());

  Point2D p = Point2D(a, b), q = Point2D(0.0f, 0.0f);

  q += p;

  EXPECT_EQ(0.0f + p.x_, q.x_);
  EXPECT_EQ(0.0f + p.y_, q.y_);
}

TEST_P(TestPoint2D, TestSubtractAssignOp) {
  float a = std::get<0>(GetParam()), b = std::get<1>(GetParam());

  Point2D p = Point2D(a, b), q = Point2D(0.0f, 0.0f);

  q -= p;

  EXPECT_EQ(0.0f - p.x_, q.x_);
  EXPECT_EQ(0.0f - p.y_, q.y_);
}

TEST_P(TestPoint2D, TestMultiplyAssignOp) {
  float n = 2.0f, a = std::get<0>(GetParam()), b = std::get<1>(GetParam());

  Point2D p = Point2D(a, b);

  p *= n;

  EXPECT_EQ(a * n, p.x_);
  EXPECT_EQ(b * n, p.y_);
}

TEST_P(TestPoint2D, TestDivideAssignOp) {
  float n = 2.0f, a = std::get<0>(GetParam()), b = std::get<1>(GetParam());

  Point2D p = Point2D(a, b);

  p /= n;

  EXPECT_EQ(a / n, p.x_);
  EXPECT_EQ(b / n, p.y_);
}

TEST_P(TestPoint2D, TestNegateOp) {
  float a = std::get<0>(GetParam()), b = std::get<1>(GetParam());

  Point2D p = Point2D(a, b), q = -p;

  EXPECT_EQ(-p.x_, q.x_);
  EXPECT_EQ(-p.y_, q.y_);
}

TEST_P(TestPoint2D, TestAddOp) {
  float a = std::get<0>(GetParam()), b = std::get<1>(GetParam());

  Point2D p = Point2D(a, b), q = Point2D(0.0f, 0.0f), r = p + q;

  EXPECT_EQ(q.x_ + p.x_, r.x_);
  EXPECT_EQ(q.y_ + p.y_, r.y_);
}

TEST_P(TestPoint2D, TestSubtractOp) {
  float a = std::get<0>(GetParam()), b = std::get<1>(GetParam());

  Point2D p = Point2D(a, b), q = Point2D(0.0f, 0.0f), r = p - q;

  EXPECT_EQ(p.x_ - q.x_, r.x_);
  EXPECT_EQ(p.y_ - q.y_, r.y_);
}

TEST_P(TestPoint2D, TestMultiplyOpRight) {
  float n = 2.0f, a = std::get<0>(GetParam()), b = std::get<1>(GetParam());
  Point2D p = Point2D(a, b), q = p * n;

  EXPECT_EQ(p.x_ * n, q.x_);
  EXPECT_EQ(p.y_ * n, q.y_);
}

TEST_P(TestPoint2D, TestMultiplyOpLeft) {
  float n = 2.0f, a = std::get<0>(GetParam()), b = std::get<1>(GetParam());
  Point2D p = Point2D(a, b), q = n * p;

  EXPECT_EQ(n * p.x_, q.x_);
  EXPECT_EQ(n * p.y_, q.y_);
}

TEST_P(TestPoint2D, TestDivideOp) {
  float n = 2.0f, a = std::get<0>(GetParam()), b = std::get<1>(GetParam());
  Point2D p = Point2D(a, b), q = p / n;

  EXPECT_EQ(p.x_ / n, q.x_);
  EXPECT_EQ(p.y_ / n, q.y_);
}

}  // namespace TestBBMaths::TestPoint2D
