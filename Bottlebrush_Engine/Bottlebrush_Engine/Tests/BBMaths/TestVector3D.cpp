#include <tuple>

#include "Point2D.h"
#include "Point3D.h"
#include "Vector2D.h"
#include "Vector3D.h"
#include "gtest/gtest.h"

namespace TestBBMaths::TestVector3D {

using namespace BBMaths;

const float kStart = -0.1f, kEnd = 0.1f, kStep = 0.1f, kTolerance = 0.0001f;

class TestVector3D
    : public ::testing::TestWithParam<std::tuple<float, float, float>> {};

INSTANTIATE_TEST_SUITE_P(
    Vectors, TestVector3D,
    testing::Combine(testing::Range(kStart, kEnd + kStep, kStep),
                     testing::Range(kStart, kEnd + kStep, kStep),
                     testing::Range(kStart, kEnd + kStep, kStep)));

TEST_P(TestVector3D, TestAltCtor) {
  float a = std::get<0>(GetParam()), b = std::get<1>(GetParam()),
        c = std::get<2>(GetParam());

  Vector3D v = Vector3D(a, b, c);

  EXPECT_EQ(a, v.x_);
  EXPECT_EQ(b, v.y_);
  EXPECT_EQ(c, v.z_);
}

TEST_P(TestVector3D, TestCopyCtor) {
  float a = std::get<0>(GetParam()), b = std::get<1>(GetParam()),
        c = std::get<2>(GetParam());

  Vector3D v = Vector3D(a, b, c), w = Vector3D(v);

  EXPECT_EQ(v.x_, w.x_);
  EXPECT_EQ(v.y_, w.y_);
  EXPECT_EQ(v.z_, w.z_);
}

TEST_P(TestVector3D, TestCopyCtorPoint3D) {
  float a = std::get<0>(GetParam()), b = std::get<1>(GetParam()),
        c = std::get<2>(GetParam());

  auto p = Point3D(a, b, c);
  auto v = Vector3D(p);

  EXPECT_EQ(v.x_, p.x_);
  EXPECT_EQ(v.y_, p.y_);
  EXPECT_EQ(v.z_, p.z_);
}

TEST_P(TestVector3D, TestCopyCtorVector2D) {
  float a = std::get<0>(GetParam()), b = std::get<1>(GetParam());

  auto v = Vector2D(a, b);
  auto w = Vector3D(v);

  EXPECT_EQ(w.x_, v.x_);
  EXPECT_EQ(w.y_, v.y_);
  EXPECT_EQ(w.z_, 0.0f);
}

TEST_P(TestVector3D, TestCopyAltCtorVector2D) {
  float a = std::get<0>(GetParam()), b = std::get<1>(GetParam()),
        c = std::get<2>(GetParam());

  auto v = Vector2D(a, b);
  auto w = Vector3D(v, c);

  EXPECT_EQ(w.x_, v.x_);
  EXPECT_EQ(w.y_, v.y_);
  EXPECT_EQ(w.z_, c);
}

TEST_P(TestVector3D, TestCopyCtorPoint2D) {
  float a = std::get<0>(GetParam()), b = std::get<1>(GetParam());

  auto p = Point2D(a, b);
  auto v = Vector3D(p);

  EXPECT_EQ(v.x_, p.x_);
  EXPECT_EQ(v.y_, p.y_);
  EXPECT_EQ(v.z_, 0.0f);
}

TEST_P(TestVector3D, TestCopyAltCtorPoint2D) {
  float a = std::get<0>(GetParam()), b = std::get<1>(GetParam()),
        c = std::get<2>(GetParam());

  auto p = Point2D(a, b);
  auto v = Vector3D(p, c);

  EXPECT_EQ(v.x_, p.x_);
  EXPECT_EQ(v.y_, p.y_);
  EXPECT_EQ(v.z_, c);
}

TEST_P(TestVector3D, TestSet) {
  float a = std::get<0>(GetParam()), b = std::get<1>(GetParam()),
        c = std::get<2>(GetParam());

  Vector3D v = Vector3D();

  v.Set(a, b, c);

  EXPECT_EQ(a, v.x_);
  EXPECT_EQ(b, v.y_);
  EXPECT_EQ(c, v.z_);
}

TEST_P(TestVector3D, TestNormalise) {
  float a = std::get<0>(GetParam()), b = std::get<1>(GetParam()),
        c = std::get<2>(GetParam()),
        magnitude = std::sqrt(a * a + b * b + c * c);

  Vector3D v = Vector3D(a, b, c);

  if (a == 0 && b == 0 && c == 0) {
    EXPECT_NO_FATAL_FAILURE(v.Normalise());
  } else {
    v.Normalise();

    EXPECT_NEAR(a / magnitude, v.x_, kTolerance);
    EXPECT_NEAR(b / magnitude, v.y_, kTolerance);
    EXPECT_NEAR(c / magnitude, v.z_, kTolerance);
  }
}

TEST_P(TestVector3D, TestRotateAboutX) {
  float a = std::get<0>(GetParam()), b = std::get<1>(GetParam()),
        c = std::get<2>(GetParam()), angle = M_PI;

  Vector3D v = Vector3D(a, b, c);

  v.RotateAboutX(angle);

  EXPECT_EQ(a, v.x_);
  EXPECT_NEAR(b * std::cos(angle) - c * std::sin(angle), v.y_, kTolerance);
  EXPECT_NEAR(b * std::sin(angle) + c * std::cos(angle), v.z_, kTolerance);
}

TEST_P(TestVector3D, TestRotateAboutY) {
  float a = std::get<0>(GetParam()), b = std::get<1>(GetParam()),
        c = std::get<2>(GetParam()), angle = M_PI;

  Vector3D v = Vector3D(a, b, c);

  v.RotateAboutY(angle);

  EXPECT_NEAR(a * std::cos(angle) + c * std::sin(angle), v.x_, kTolerance);
  EXPECT_EQ(b, v.y_);
  EXPECT_NEAR(c * std::cos(angle) - a * std::sin(angle), v.z_, kTolerance);
}

TEST_P(TestVector3D, TestRotateAboutZ) {
  float a = std::get<0>(GetParam()), b = std::get<1>(GetParam()),
        c = std::get<2>(GetParam()), angle = M_PI;

  Vector3D v = Vector3D(a, b, c);

  v.RotateAboutZ(angle);

  EXPECT_NEAR(a * std::cos(angle) - b * std::sin(angle), v.x_, kTolerance);
  EXPECT_NEAR(a * std::sin(angle) + b * std::cos(angle), v.y_, kTolerance);
  EXPECT_EQ(c, v.z_);
}

TEST_P(TestVector3D, TestAssignOp) {
  float a = std::get<0>(GetParam()), b = std::get<1>(GetParam()),
        c = std::get<2>(GetParam());

  Vector3D v = Vector3D(a, b, c), w = v;

  EXPECT_EQ(v.x_, w.x_);
  EXPECT_EQ(v.y_, w.y_);
  EXPECT_EQ(v.z_, w.z_);
}

TEST_P(TestVector3D, TestAssignOpPoint3D) {
  float a = std::get<0>(GetParam()), b = std::get<1>(GetParam()),
        c = std::get<2>(GetParam());

  auto p = Point3D(a, b, c);
  auto v = Vector3D();

  v = p;

  EXPECT_EQ(p.x_, v.x_);
  EXPECT_EQ(p.y_, v.y_);
  EXPECT_EQ(p.z_, v.z_);
}

TEST_P(TestVector3D, TestAssignOpVector2D) {
  float a = std::get<0>(GetParam()), b = std::get<1>(GetParam());

  auto v = Vector2D(a, b);
  auto w = Vector3D();

  w = v;

  EXPECT_EQ(v.x_, w.x_);
  EXPECT_EQ(v.y_, w.y_);
  EXPECT_EQ(0.0f, w.z_);
}

TEST_P(TestVector3D, TestAssignOpPoint2D) {
  float a = std::get<0>(GetParam()), b = std::get<1>(GetParam());

  auto p = Point2D(a, b);
  auto v = Vector3D();

  v = p;

  EXPECT_EQ(p.x_, v.x_);
  EXPECT_EQ(p.y_, v.y_);
  EXPECT_EQ(0.0f, v.z_);
}

TEST_P(TestVector3D, TestAddAssignOp) {
  float a = std::get<0>(GetParam()), b = std::get<1>(GetParam()),
        c = std::get<2>(GetParam());

  Vector3D v = Vector3D(a, b, c), w = Vector3D(0.0f, 0.0f, 0.0f);

  w += v;

  EXPECT_EQ(0.0f + v.x_, w.x_);
  EXPECT_EQ(0.0f + v.y_, w.y_);
  EXPECT_EQ(0.0f + v.z_, w.z_);
}

TEST_P(TestVector3D, TestSubtractAssignOp) {
  float a = std::get<0>(GetParam()), b = std::get<1>(GetParam()),
        c = std::get<2>(GetParam());

  Vector3D v = Vector3D(a, b, c), w = Vector3D(0.0f, 0.0f, 0.0f);

  w -= v;

  EXPECT_EQ(0.0f - v.x_, w.x_);
  EXPECT_EQ(0.0f - v.y_, w.y_);
  EXPECT_EQ(0.0f - v.z_, w.z_);
}

TEST_P(TestVector3D, TestMultiplyAssignOp) {
  float n = 2.0f, a = std::get<0>(GetParam()), b = std::get<1>(GetParam()),
        c = std::get<2>(GetParam());

  Vector3D v = Vector3D(a, b, c);

  v *= n;

  EXPECT_EQ(a * n, v.x_);
  EXPECT_EQ(b * n, v.y_);
  EXPECT_EQ(c * n, v.z_);
}

TEST_P(TestVector3D, TestDivideAssignOp) {
  float n = 2.0f, a = std::get<0>(GetParam()), b = std::get<1>(GetParam()),
        c = std::get<2>(GetParam());

  Vector3D v = Vector3D(a, b, c);

  v /= n;

  EXPECT_EQ(a / n, v.x_);
  EXPECT_EQ(b / n, v.y_);
  EXPECT_EQ(c / n, v.z_);
}

TEST_P(TestVector3D, TestDot) {
  float a = std::get<0>(GetParam()), b = std::get<1>(GetParam()),
        c = std::get<2>(GetParam());

  Vector3D v = Vector3D(a, b, c), w = Vector3D(c, b, a);

  EXPECT_EQ(a * c + b * b + c * a, Dot(v, w));
}

TEST_P(TestVector3D, TestMagnitude) {
  float a = std::get<0>(GetParam()), b = std::get<1>(GetParam()),
        c = std::get<2>(GetParam()),
        magnitude = std::sqrt(a * a + b * b + c * c);

  Vector3D v = Vector3D(a, b, c);

  EXPECT_NEAR(magnitude, Magnitude(v), kTolerance);
}

TEST_P(TestVector3D, TestInverseMagnitude) {
  float a = std::get<0>(GetParam()), b = std::get<1>(GetParam()),
        c = std::get<2>(GetParam()),
        magnitude = std::sqrt(a * a + b * b + c * c);

  Vector3D v = Vector3D(a, b, c);

  if (a == 0 && b == 0 && c == 0) {
    EXPECT_NO_FATAL_FAILURE(InverseMagnitude(v));
  } else {
    EXPECT_NEAR(1.0f / magnitude, InverseMagnitude(v), kTolerance);
  }
}

TEST_P(TestVector3D, TestISquaredMagnitude) {
  float a = std::get<0>(GetParam()), b = std::get<1>(GetParam()),
        c = std::get<2>(GetParam()),
        magnitude = std::sqrt(a * a + b * b + c * c);

  Vector3D v = Vector3D(a, b, c);

  EXPECT_NEAR(magnitude * magnitude, SquaredMagnitude(v), kTolerance);
}

TEST_P(TestVector3D, TestProjection) {
  float a = std::get<0>(GetParam()), b = std::get<1>(GetParam()),
        c = std::get<2>(GetParam());

  Vector3D v = Vector3D(a, b, c), w = Vector3D(c, b, a);

  if (a == 0 && b == 0 && c == 0) {
    EXPECT_NO_FATAL_FAILURE(Projection(v, w));
  } else {
    Vector3D u = Projection(v, w);

    EXPECT_NEAR(c * ((a * c + b * b + c * a) / (c * c + b * b + a * a)), u.x_,
                kTolerance);
    EXPECT_NEAR(b * ((a * c + b * b + c * a) / (c * c + b * b + a * a)), u.y_,
                kTolerance);
    EXPECT_NEAR(a * ((a * c + b * b + c * a) / (c * c + b * b + a * a)), u.z_,
                kTolerance);
  }
}

TEST_P(TestVector3D, TestRejection) {
  float a = std::get<0>(GetParam()), b = std::get<1>(GetParam()),
        c = std::get<2>(GetParam());

  Vector3D v = Vector3D(a, b, c), w = Vector3D(c, b, a);

  if (a == 0 && b == 0 && c == 0) {
    EXPECT_NO_FATAL_FAILURE(Rejection(v, w));
  } else {
    Vector3D u = Rejection(v, w);

    EXPECT_NEAR(a - c * ((a * c + b * b + c * a) / (c * c + b * b + a * a)),
                u.x_, kTolerance);
    EXPECT_NEAR(b - b * ((a * c + b * b + c * a) / (c * c + b * b + a * a)),
                u.y_, kTolerance);
    EXPECT_NEAR(c - a * ((a * c + b * b + c * a) / (c * c + b * b + a * a)),
                u.z_, kTolerance);
  }
}

TEST_P(TestVector3D, TestNegateOp) {
  float a = std::get<0>(GetParam()), b = std::get<1>(GetParam()),
        c = std::get<2>(GetParam());

  Vector3D v = Vector3D(a, b, c), w = -v;

  EXPECT_EQ(-v.x_, w.x_);
  EXPECT_EQ(-v.y_, w.y_);
  EXPECT_EQ(-v.z_, w.z_);
}

TEST_P(TestVector3D, TestAddOp) {
  float a = std::get<0>(GetParam()), b = std::get<1>(GetParam()),
        c = std::get<2>(GetParam());

  Vector3D v = Vector3D(a, b, c), w = Vector3D(0.0f, 0.0f, 0.0f), u = v + w;

  EXPECT_EQ(v.x_ + w.x_, u.x_);
  EXPECT_EQ(v.y_ + w.y_, u.y_);
  EXPECT_EQ(v.z_ + w.z_, u.z_);
}

TEST_P(TestVector3D, TestSubtractOp) {
  float a = std::get<0>(GetParam()), b = std::get<1>(GetParam()),
        c = std::get<2>(GetParam());

  Vector3D v = Vector3D(a, b, c), w = Vector3D(0.0f, 0.0f, 0.0f), u = v - w;

  EXPECT_EQ(v.x_ - w.x_, u.x_);
  EXPECT_EQ(v.y_ - w.y_, u.y_);
  EXPECT_EQ(v.z_ - w.z_, u.z_);
}

TEST_P(TestVector3D, TestMultiplyOpRight) {
  float n = 2.0f, a = std::get<0>(GetParam()), b = std::get<1>(GetParam()),
        c = std::get<2>(GetParam());
  Vector3D v = Vector3D(a, b, c), w = v * n;

  EXPECT_EQ(v.x_ * n, w.x_);
  EXPECT_EQ(v.y_ * n, w.y_);
  EXPECT_EQ(v.z_ * n, w.z_);
}

TEST_P(TestVector3D, TestMultiplyOpLeft) {
  float n = 2.0f, a = std::get<0>(GetParam()), b = std::get<1>(GetParam()),
        c = std::get<2>(GetParam());
  Vector3D v = Vector3D(a, b, c), w = n * v;

  EXPECT_EQ(n * v.x_, w.x_);
  EXPECT_EQ(n * v.y_, w.y_);
  EXPECT_EQ(n * v.z_, w.z_);
}

TEST_P(TestVector3D, TestDivideOp) {
  float n = 2.0f, a = std::get<0>(GetParam()), b = std::get<1>(GetParam()),
        c = std::get<2>(GetParam());
  Vector3D v = Vector3D(a, b, c), w = v / n;

  EXPECT_EQ(v.x_ / n, w.x_);
  EXPECT_EQ(v.y_ / n, w.y_);
  EXPECT_EQ(v.z_ / n, w.z_);
}

}  // namespace TestBBMaths::TestVector3D
