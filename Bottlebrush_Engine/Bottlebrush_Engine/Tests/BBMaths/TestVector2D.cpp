#include <numbers>
#include <tuple>

#include "Point2D.h"
#include "Vector2D.h"
#include "gtest/gtest.h"

namespace TestBBMaths::TestVector2D {

using namespace BBMaths;

const float kStart = -0.1f, kEnd = 0.1f, kStep = 0.1f, kTolerance = 0.0001f;

class TestVector2D : public ::testing::TestWithParam<std::tuple<float, float>> {
};

INSTANTIATE_TEST_SUITE_P(
    Vectors, TestVector2D,
    testing::Combine(testing::Range(kStart, kEnd + kStep, kStep),
                     testing::Range(kStart, kEnd + kStep, kStep)));

TEST_P(TestVector2D, TestAltCtor) {
  float a = std::get<0>(GetParam()), b = std::get<1>(GetParam());

  Vector2D v = Vector2D(a, b);

  EXPECT_EQ(a, v.x_);
  EXPECT_EQ(b, v.y_);
}

TEST_P(TestVector2D, TestCopyCtor) {
  float a = std::get<0>(GetParam()), b = std::get<1>(GetParam());

  Vector2D v = Vector2D(a, b), w = Vector2D(v);

  EXPECT_EQ(v.x_, w.x_);
  EXPECT_EQ(v.y_, w.y_);
}

TEST_P(TestVector2D, TestCopyCtorPoint2D) {
  float a = std::get<0>(GetParam()), b = std::get<1>(GetParam());

  auto p = Point2D(a, b);
  auto v = Vector2D(p);

  EXPECT_EQ(v.x_, p.x_);
  EXPECT_EQ(v.y_, p.y_);
}

TEST_P(TestVector2D, TestSet) {
  float a = std::get<0>(GetParam()), b = std::get<1>(GetParam());

  Vector2D v = Vector2D();

  v.Set(a, b);

  EXPECT_EQ(a, v.x_);
  EXPECT_EQ(b, v.y_);
}

TEST_P(TestVector2D, TestNormalise) {
  float a = std::get<0>(GetParam()), b = std::get<1>(GetParam()),
        magnitude = std::sqrt(a * a + b * b);

  Vector2D v = Vector2D(a, b);

  if (a == 0 && b == 0) {
    EXPECT_NO_FATAL_FAILURE(v.Normalise());
  } else {
    v.Normalise();

    EXPECT_NEAR(a / magnitude, v.x_, kTolerance);
    EXPECT_NEAR(b / magnitude, v.y_, kTolerance);
  }
}

TEST_P(TestVector2D, TestRotate) {
  float a = std::get<0>(GetParam()), b = std::get<1>(GetParam()),
        angle = std::numbers::pi;

  Vector2D v = Vector2D(a, b);

  v.Rotate(angle);

  EXPECT_NEAR(a * std::cos(angle) - b * std::sin(angle), v.x_, kTolerance);
  EXPECT_NEAR(a * std::sin(angle) + b * std::cos(angle), v.y_, kTolerance);
}

TEST_P(TestVector2D, TestAssignOp) {
  float a = std::get<0>(GetParam()), b = std::get<1>(GetParam());

  Vector2D v = Vector2D(a, b), w = v;

  EXPECT_EQ(v.x_, w.x_);
  EXPECT_EQ(v.y_, w.y_);
}

TEST_P(TestVector2D, TestAssignOpPoint2D) {
  float a = std::get<0>(GetParam()), b = std::get<1>(GetParam());

  auto p = Point2D(a, b);
  auto v = Vector2D(p);

  EXPECT_EQ(p.x_, v.x_);
  EXPECT_EQ(p.y_, v.y_);
}

TEST_P(TestVector2D, TestAddAssignOp) {
  float a = std::get<0>(GetParam()), b = std::get<1>(GetParam());

  Vector2D v = Vector2D(a, b), w = Vector2D(0.0f, 0.0f);

  w += v;

  EXPECT_EQ(0.0f + v.x_, w.x_);
  EXPECT_EQ(0.0f + v.y_, w.y_);
}

TEST_P(TestVector2D, TestSubtractAssignOp) {
  float a = std::get<0>(GetParam()), b = std::get<1>(GetParam());

  Vector2D v = Vector2D(a, b), w = Vector2D(0.0f, 0.0f);

  w -= v;

  EXPECT_EQ(0.0f - v.x_, w.x_);
  EXPECT_EQ(0.0f - v.y_, w.y_);
}

TEST_P(TestVector2D, TestMultiplyAssignOp) {
  float n = 2.0f, a = std::get<0>(GetParam()), b = std::get<1>(GetParam());

  Vector2D v = Vector2D(a, b);

  v *= n;

  EXPECT_EQ(a * n, v.x_);
  EXPECT_EQ(b * n, v.y_);
}

TEST_P(TestVector2D, TestDivideAssignOp) {
  float n = 2.0f, a = std::get<0>(GetParam()), b = std::get<1>(GetParam());

  Vector2D v = Vector2D(a, b);

  v /= n;

  EXPECT_EQ(a / n, v.x_);
  EXPECT_EQ(b / n, v.y_);
}

TEST_P(TestVector2D, TestDot) {
  float a = std::get<0>(GetParam()), b = std::get<1>(GetParam());

  Vector2D v = Vector2D(a, b), w = Vector2D(b, a);

  EXPECT_EQ(a * b + b * a, Dot(v, w));
}

TEST_P(TestVector2D, TestMagnitude) {
  float a = std::get<0>(GetParam()), b = std::get<1>(GetParam()),
        magnitude = std::sqrt(a * a + b * b);

  Vector2D v = Vector2D(a, b);

  EXPECT_NEAR(magnitude, Magnitude(v), kTolerance);
}

TEST_P(TestVector2D, TestInverseMagnitude) {
  float a = std::get<0>(GetParam()), b = std::get<1>(GetParam()),
        magnitude = std::sqrt(a * a + b * b);

  Vector2D v = Vector2D(a, b);

  if (a == 0 && b == 0) {
    EXPECT_NO_FATAL_FAILURE(InverseMagnitude(v));
  } else {
    EXPECT_NEAR(1.0f / magnitude, InverseMagnitude(v), kTolerance);
  }
}

TEST_P(TestVector2D, TestISquaredMagnitude) {
  float a = std::get<0>(GetParam()), b = std::get<1>(GetParam()),
        magnitude = std::sqrt(a * a + b * b);

  Vector2D v = Vector2D(a, b);

  EXPECT_NEAR(magnitude * magnitude, SquaredMagnitude(v), kTolerance);
}

TEST_P(TestVector2D, TestProjection) {
  float a = std::get<0>(GetParam()), b = std::get<1>(GetParam());

  Vector2D v = Vector2D(a, b), w = Vector2D(b, a);

  if (a == 0 && b == 0) {
    EXPECT_NO_FATAL_FAILURE(Projection(v, w));
  } else {
    Vector2D u = Projection(v, w);

    EXPECT_NEAR(b * ((a * b + b * a) / (b * b + a * a)), u.x_, kTolerance);
    EXPECT_NEAR(a * ((a * b + b * a) / (b * b + a * a)), u.y_, kTolerance);
  }
}

TEST_P(TestVector2D, TestRejection) {
  float a = std::get<0>(GetParam()), b = std::get<1>(GetParam());

  Vector2D v = Vector2D(a, b), w = Vector2D(b, a);

  if (a == 0 && b == 0) {
    EXPECT_NO_FATAL_FAILURE(Rejection(v, w));
  } else {
    Vector2D u = Rejection(v, w);

    EXPECT_NEAR(a - b * ((a * b + b * a) / (b * b + a * a)), u.x_, kTolerance);
    EXPECT_NEAR(b - a * ((a * b + b * a) / (b * b + a * a)), u.y_, kTolerance);
  }
}

TEST_P(TestVector2D, TestNegateOp) {
  float a = std::get<0>(GetParam()), b = std::get<1>(GetParam());

  Vector2D v = Vector2D(a, b), w = -v;

  EXPECT_EQ(-v.x_, w.x_);
  EXPECT_EQ(-v.y_, w.y_);
}

TEST_P(TestVector2D, TestAddOp) {
  float a = std::get<0>(GetParam()), b = std::get<1>(GetParam());

  Vector2D v = Vector2D(a, b), w = Vector2D(0.0f, 0.0f), u = v + w;

  EXPECT_EQ(v.x_ + w.x_, u.x_);
  EXPECT_EQ(v.y_ + w.y_, u.y_);
}

TEST_P(TestVector2D, TestSubtractOp) {
  float a = std::get<0>(GetParam()), b = std::get<1>(GetParam());

  Vector2D v = Vector2D(a, b), w = Vector2D(0.0f, 0.0f), u = v - w;

  EXPECT_EQ(v.x_ - w.x_, u.x_);
  EXPECT_EQ(v.y_ - w.y_, u.y_);
}

TEST_P(TestVector2D, TestMultiplyOpRight) {
  float n = 2.0f, a = std::get<0>(GetParam()), b = std::get<1>(GetParam());
  Vector2D v = Vector2D(a, b), w = v * n;

  EXPECT_EQ(v.x_ * n, w.x_);
  EXPECT_EQ(v.y_ * n, w.y_);
}

TEST_P(TestVector2D, TestMultiplyOpLeft) {
  float n = 2.0f, a = std::get<0>(GetParam()), b = std::get<1>(GetParam());
  Vector2D v = Vector2D(a, b), w = n * v;

  EXPECT_EQ(n * v.x_, w.x_);
  EXPECT_EQ(n * v.y_, w.y_);
}

TEST_P(TestVector2D, TestDivideOp) {
  float n = 2.0f, a = std::get<0>(GetParam()), b = std::get<1>(GetParam());
  Vector2D v = Vector2D(a, b), w = v / n;

  EXPECT_EQ(v.x_ / n, w.x_);
  EXPECT_EQ(v.y_ / n, w.y_);
}

}  // namespace TestBBMaths::TestVector2D
