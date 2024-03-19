#include <tuple>

#include "Point3D.h"
#include "gtest/gtest.h"

namespace TestBBMaths::TestPoint3D {

using namespace BBMaths;

const float kStart = -0.1f, kEnd = 0.1f, kStep = 0.1f, kTolerance = 0.0001f;

class TestPoint3D
    : public ::testing::TestWithParam<std::tuple<float, float, float>> {};

INSTANTIATE_TEST_SUITE_P(
    Points, TestPoint3D,
    testing::Combine(testing::Range(kStart, kEnd + kStep, kStep),
                     testing::Range(kStart, kEnd + kStep, kStep),
                     testing::Range(kStart, kEnd + kStep, kStep)));

TEST_P(TestPoint3D, TestAltCtor) {
  float a = std::get<0>(GetParam()), b = std::get<1>(GetParam()),
        c = std::get<2>(GetParam());

  Point3D p = Point3D(a, b, c);

  EXPECT_EQ(a, p.x_);
  EXPECT_EQ(b, p.y_);
  EXPECT_EQ(c, p.z_);
}

TEST_P(TestPoint3D, TestCopyCtor) {
  float a = std::get<0>(GetParam()), b = std::get<1>(GetParam()),
        c = std::get<2>(GetParam());

  Point3D p = Point3D(a, b, c), q = Point3D(p);

  EXPECT_EQ(p.x_, q.x_);
  EXPECT_EQ(p.y_, q.y_);
  EXPECT_EQ(p.z_, q.z_);
}

TEST_P(TestPoint3D, TestAssignOp) {
  float a = std::get<0>(GetParam()), b = std::get<1>(GetParam()),
        c = std::get<2>(GetParam());

  Point3D p = Point3D(a, b, c), q = p;

  EXPECT_EQ(p.x_, q.x_);
  EXPECT_EQ(p.y_, q.y_);
  EXPECT_EQ(p.z_, q.z_);
}

TEST_P(TestPoint3D, TestAddAssignOp) {
  float a = std::get<0>(GetParam()), b = std::get<1>(GetParam()),
        c = std::get<2>(GetParam());

  Point3D p = Point3D(a, b, c), q = Point3D(0.0f, 0.0f, 0.0f);

  q += p;

  EXPECT_EQ(0.0f + p.x_, q.x_);
  EXPECT_EQ(0.0f + p.y_, q.y_);
  EXPECT_EQ(0.0f + p.z_, q.z_);
}

TEST_P(TestPoint3D, TestSubtractAssignOp) {
  float a = std::get<0>(GetParam()), b = std::get<1>(GetParam()),
        c = std::get<2>(GetParam());

  Point3D p = Point3D(a, b, c), q = Point3D(0.0f, 0.0f, 0.0f);

  q -= p;

  EXPECT_EQ(0.0f - p.x_, q.x_);
  EXPECT_EQ(0.0f - p.y_, q.y_);
  EXPECT_EQ(0.0f - p.z_, q.z_);
}

TEST_P(TestPoint3D, TestMultiplyAssignOp) {
  float n = 2.0f, a = std::get<0>(GetParam()), b = std::get<1>(GetParam()),
        c = std::get<2>(GetParam());

  Point3D p = Point3D(a, b, c);

  p *= n;

  EXPECT_EQ(a * n, p.x_);
  EXPECT_EQ(b * n, p.y_);
  EXPECT_EQ(c * n, p.z_);
}

TEST_P(TestPoint3D, TestDivideAssignOp) {
  float n = 2.0f, a = std::get<0>(GetParam()), b = std::get<1>(GetParam()),
        c = std::get<2>(GetParam());
  Point3D p = Point3D(a, b, c);

  p /= n;

  EXPECT_EQ(a / n, p.x_);
  EXPECT_EQ(b / n, p.y_);
  EXPECT_EQ(c / n, p.z_);
}

TEST_P(TestPoint3D, TestNegateOp) {
  float a = std::get<0>(GetParam()), b = std::get<1>(GetParam()),
        c = std::get<2>(GetParam());

  Point3D p = Point3D(a, b, c), q = -p;

  EXPECT_EQ(-p.x_, q.x_);
  EXPECT_EQ(-p.y_, q.y_);
  EXPECT_EQ(-p.z_, q.z_);
}

TEST_P(TestPoint3D, TestAddOp) {
  float a = std::get<0>(GetParam()), b = std::get<1>(GetParam()),
        c = std::get<2>(GetParam());

  Point3D p = Point3D(a, b, c), q = Point3D(0.0f, 0.0f, 0.0f), r = p + q;

  EXPECT_EQ(q.x_ + p.x_, r.x_);
  EXPECT_EQ(q.y_ + p.y_, r.y_);
  EXPECT_EQ(q.z_ + p.z_, r.z_);
}

TEST_P(TestPoint3D, TestSubtractOp) {
  float a = std::get<0>(GetParam()), b = std::get<1>(GetParam()),
        c = std::get<2>(GetParam());

  Point3D p = Point3D(a, b, c), q = Point3D(0.0f, 0.0f, 0.0f), r = p - q;

  EXPECT_EQ(p.x_ - q.x_, r.x_);
  EXPECT_EQ(p.y_ - q.y_, r.y_);
  EXPECT_EQ(p.z_ - q.z_, r.z_);
}

TEST_P(TestPoint3D, TestMultiplyOpRight) {
  float n = 2.0f, a = std::get<0>(GetParam()), b = std::get<1>(GetParam()),
        c = std::get<2>(GetParam());

  Point3D p = Point3D(a, b, c), q = p * n;

  EXPECT_EQ(p.x_ * n, q.x_);
  EXPECT_EQ(p.y_ * n, q.y_);
  EXPECT_EQ(p.z_ * n, q.z_);
}

TEST_P(TestPoint3D, TestMultiplyOpLeft) {
  float n = 2.0f, a = std::get<0>(GetParam()), b = std::get<1>(GetParam()),
        c = std::get<2>(GetParam());

  Point3D p = Point3D(a, b, c), q = n * p;

  EXPECT_EQ(n * p.x_, q.x_);
  EXPECT_EQ(n * p.y_, q.y_);
  EXPECT_EQ(n * p.z_, q.z_);
}

TEST_P(TestPoint3D, TestDivideOp) {
  float n = 2.0f, a = std::get<0>(GetParam()), b = std::get<1>(GetParam()),
        c = std::get<2>(GetParam());

  Point3D p = Point3D(a, b, c), q = p / n;

  EXPECT_EQ(p.x_ / n, q.x_);
  EXPECT_EQ(p.y_ / n, q.y_);
  EXPECT_EQ(p.z_ / n, q.z_);
}

}  // namespace TestBBMaths::TestPoint3D
