#include <numbers>
#include <tuple>

#include "Point2D.h"
#include "Point3D.h"
#include "Vector2D.h"
#include "Vector3D.h"
#include "Vector4D.h"
#include "gtest/gtest.h"

namespace TestBBMaths::TestVector4D {

using namespace BBMaths;

const float kStart = -0.1f, kEnd = 0.1f, kStep = 0.1f, kTolerance = 0.0001f;

class TestVector4D
    : public ::testing::TestWithParam<std::tuple<float, float, float, float>> {
};

INSTANTIATE_TEST_SUITE_P(
    Vectors, TestVector4D,
    testing::Combine(testing::Range(kStart, kEnd + kStep, kStep),
                     testing::Range(kStart, kEnd + kStep, kStep),
                     testing::Range(kStart, kEnd + kStep, kStep),
                     testing::Range(kStart, kEnd + kStep, kStep)));

TEST_P(TestVector4D, TestAltCtor) {
  float a = std::get<0>(GetParam()), b = std::get<1>(GetParam()),
        c = std::get<2>(GetParam()), d = std::get<3>(GetParam());

  Vector4D v = Vector4D(a, b, c, d);

  EXPECT_EQ(a, v.x_);
  EXPECT_EQ(b, v.y_);
  EXPECT_EQ(c, v.z_);
  EXPECT_EQ(d, v.w_);
}

TEST_P(TestVector4D, TestCopyCtor) {
  float a = std::get<0>(GetParam()), b = std::get<1>(GetParam()),
        c = std::get<2>(GetParam()), d = std::get<3>(GetParam());

  Vector4D v = Vector4D(a, b, c, d), w = Vector4D(v);

  EXPECT_EQ(v.x_, w.x_);
  EXPECT_EQ(v.y_, w.y_);
  EXPECT_EQ(v.z_, w.z_);
  EXPECT_EQ(v.w_, w.w_);
}

TEST_P(TestVector4D, TestCopyCtorVector3D) {
  float a = std::get<0>(GetParam()), b = std::get<1>(GetParam()),
        c = std::get<2>(GetParam());

  auto v = Vector3D(a, b, c);
  auto w = Vector4D(v);

  EXPECT_EQ(w.x_, v.x_);
  EXPECT_EQ(w.y_, v.y_);
  EXPECT_EQ(w.z_, v.z_);
  EXPECT_EQ(w.w_, 0.0f);
}

TEST_P(TestVector4D, TestCopyAltCtorVector3D) {
  float a = std::get<0>(GetParam()), b = std::get<1>(GetParam()),
        c = std::get<2>(GetParam()), d = std::get<3>(GetParam());

  auto v = Vector3D(a, b, c);
  auto w = Vector4D(v, d);

  EXPECT_EQ(w.x_, v.x_);
  EXPECT_EQ(w.y_, v.y_);
  EXPECT_EQ(w.z_, v.z_);
  EXPECT_EQ(w.w_, d);
}

TEST_P(TestVector4D, TestCopyCtorPoint3D) {
  float a = std::get<0>(GetParam()), b = std::get<1>(GetParam()),
        c = std::get<2>(GetParam());

  auto p = Point3D(a, b, c);
  auto v = Vector4D(p);

  EXPECT_EQ(v.x_, p.x_);
  EXPECT_EQ(v.y_, p.y_);
  EXPECT_EQ(v.z_, p.z_);
  EXPECT_EQ(v.w_, 1.0f);
}

TEST_P(TestVector4D, TestCopyAltCtorPoint3D) {
  float a = std::get<0>(GetParam()), b = std::get<1>(GetParam()),
        c = std::get<2>(GetParam()), d = std::get<3>(GetParam());

  auto p = Point3D(a, b, c);
  auto v = Vector4D(p, d);

  EXPECT_EQ(v.x_, p.x_);
  EXPECT_EQ(v.y_, p.y_);
  EXPECT_EQ(v.z_, p.z_);
  EXPECT_EQ(v.w_, d);
}

TEST_P(TestVector4D, TestCopyCtorVector2D) {
  float a = std::get<0>(GetParam()), b = std::get<1>(GetParam());

  auto v = Vector2D(a, b);
  auto w = Vector4D(v);

  EXPECT_EQ(w.x_, v.x_);
  EXPECT_EQ(w.y_, v.y_);
  EXPECT_EQ(w.z_, 0.0f);
  EXPECT_EQ(w.w_, 0.0f);
}

TEST_P(TestVector4D, TestCopyAltCtorVector2D) {
  float a = std::get<0>(GetParam()), b = std::get<1>(GetParam()),
        c = std::get<2>(GetParam()), d = std::get<3>(GetParam());

  auto v = Vector2D(a, b);
  auto w = Vector4D(v, c, d);

  EXPECT_EQ(w.x_, v.x_);
  EXPECT_EQ(w.y_, v.y_);
  EXPECT_EQ(w.z_, c);
  EXPECT_EQ(w.w_, d);
}

TEST_P(TestVector4D, TestCopyCtorPoint2D) {
  float a = std::get<0>(GetParam()), b = std::get<1>(GetParam());

  auto p = Point2D(a, b);
  auto v = Vector4D(p);

  EXPECT_EQ(v.x_, p.x_);
  EXPECT_EQ(v.y_, p.y_);
  EXPECT_EQ(v.z_, 0.0f);
  EXPECT_EQ(v.w_, 1.0f);
}

TEST_P(TestVector4D, TestCopyAltCtorPoint2D) {
  float a = std::get<0>(GetParam()), b = std::get<1>(GetParam()),
        c = std::get<2>(GetParam()), d = std::get<3>(GetParam());

  auto p = Point2D(a, b);
  auto v = Vector4D(p, c, d);

  EXPECT_EQ(v.x_, p.x_);
  EXPECT_EQ(v.y_, p.y_);
  EXPECT_EQ(v.z_, c);
  EXPECT_EQ(v.w_, d);
}

TEST_P(TestVector4D, TestSet) {
  float a = std::get<0>(GetParam()), b = std::get<1>(GetParam()),
        c = std::get<2>(GetParam()), d = std::get<3>(GetParam());

  Vector4D v = Vector4D();

  v.Set(a, b, c, d);

  EXPECT_EQ(a, v.x_);
  EXPECT_EQ(b, v.y_);
  EXPECT_EQ(c, v.z_);
  EXPECT_EQ(d, v.w_);
}

TEST_P(TestVector4D, TestNormalise) {
  float a = std::get<0>(GetParam()), b = std::get<1>(GetParam()),
        c = std::get<2>(GetParam()), d = std::get<3>(GetParam()),
        magnitude = std::sqrt(a * a + b * b + c * c + d * d);

  Vector4D v = Vector4D(a, b, c, d);

  if (a == 0 && b == 0 && c == 0 && d == 0) {
    EXPECT_NO_FATAL_FAILURE(v.Normalise());
  } else {
    v.Normalise();

    EXPECT_NEAR(a / magnitude, v.x_, kTolerance);
    EXPECT_NEAR(b / magnitude, v.y_, kTolerance);
    EXPECT_NEAR(c / magnitude, v.z_, kTolerance);
    EXPECT_NEAR(d / magnitude, v.w_, kTolerance);
  }
}

TEST_P(TestVector4D, TestRotateAboutX) {
  float a = std::get<0>(GetParam()), b = std::get<1>(GetParam()),
        c = std::get<2>(GetParam()), d = std::get<3>(GetParam()),
        angle = std::numbers::pi;

  Vector4D v = Vector4D(a, b, c, d);

  v.RotateAboutX(angle);

  EXPECT_EQ(a, v.x_);
  EXPECT_NEAR(b * std::cos(angle) - c * std::sin(angle), v.y_, kTolerance);
  EXPECT_NEAR(b * std::sin(angle) + c * std::cos(angle), v.z_, kTolerance);
  EXPECT_EQ(d, v.w_);
}

TEST_P(TestVector4D, TestRotateAboutY) {
  float a = std::get<0>(GetParam()), b = std::get<1>(GetParam()),
        c = std::get<2>(GetParam()), d = std::get<3>(GetParam()),
        angle = std::numbers::pi;

  Vector4D v = Vector4D(a, b, c, d);

  v.RotateAboutY(angle);

  EXPECT_NEAR(a * std::cos(angle) + c * std::sin(angle), v.x_, kTolerance);
  EXPECT_EQ(b, v.y_);
  EXPECT_NEAR(c * std::cos(angle) - a * std::sin(angle), v.z_, kTolerance);
  EXPECT_EQ(d, v.w_);
}

TEST_P(TestVector4D, TestRotateAboutZ) {
  float a = std::get<0>(GetParam()), b = std::get<1>(GetParam()),
        c = std::get<2>(GetParam()), d = std::get<3>(GetParam()),
        angle = std::numbers::pi;

  Vector4D v = Vector4D(a, b, c, d);

  v.RotateAboutZ(angle);

  EXPECT_NEAR(a * std::cos(angle) - b * std::sin(angle), v.x_, kTolerance);
  EXPECT_NEAR(a * std::sin(angle) + b * std::cos(angle), v.y_, kTolerance);
  EXPECT_EQ(c, v.z_);
  EXPECT_EQ(d, v.w_);
}

TEST_P(TestVector4D, TestAssignOp) {
  float a = std::get<0>(GetParam()), b = std::get<1>(GetParam()),
        c = std::get<2>(GetParam()), d = std::get<3>(GetParam());

  Vector4D v = Vector4D(a, b, c, d), w = v;

  EXPECT_EQ(v.x_, w.x_);
  EXPECT_EQ(v.y_, w.y_);
  EXPECT_EQ(v.z_, w.z_);
  EXPECT_EQ(v.w_, w.w_);
}

TEST_P(TestVector4D, TestAssignOpVector3D) {
  float a = std::get<0>(GetParam()), b = std::get<1>(GetParam()),
        c = std::get<2>(GetParam());

  auto v = Vector3D(a, b, c);
  auto w = Vector4D();

  w = v;

  EXPECT_EQ(v.x_, w.x_);
  EXPECT_EQ(v.y_, w.y_);
  EXPECT_EQ(v.z_, w.z_);
  EXPECT_EQ(0.0f, w.w_);
}

TEST_P(TestVector4D, TestAssignOpPoint3D) {
  float a = std::get<0>(GetParam()), b = std::get<1>(GetParam()),
        c = std::get<2>(GetParam());

  auto p = Point3D(a, b, c);
  auto v = Vector4D();

  v = p;

  EXPECT_EQ(p.x_, v.x_);
  EXPECT_EQ(p.y_, v.y_);
  EXPECT_EQ(p.z_, v.z_);
  EXPECT_EQ(1.0f, v.w_);
}

TEST_P(TestVector4D, TestAssignOpVector2D) {
  float a = std::get<0>(GetParam()), b = std::get<1>(GetParam());

  auto v = Vector2D(a, b);
  auto w = Vector4D();

  w = v;

  EXPECT_EQ(v.x_, w.x_);
  EXPECT_EQ(v.y_, w.y_);
  EXPECT_EQ(0.0f, w.z_);
  EXPECT_EQ(0.0f, w.w_);
}

TEST_P(TestVector4D, TestAssignOpPoint2D) {
  float a = std::get<0>(GetParam()), b = std::get<1>(GetParam());

  auto p = Point2D(a, b);
  auto v = Vector4D();

  v = p;

  EXPECT_EQ(p.x_, v.x_);
  EXPECT_EQ(p.y_, v.y_);
  EXPECT_EQ(0.0f, v.z_);
  EXPECT_EQ(1.0f, v.w_);
}

TEST_P(TestVector4D, TestAddAssignOp) {
  float a = std::get<0>(GetParam()), b = std::get<1>(GetParam()),
        c = std::get<2>(GetParam()), d = std::get<3>(GetParam());

  Vector4D v = Vector4D(a, b, c, d), w = Vector4D(0.0f, 0.0f, 0.0f, 0.0f);

  w += v;

  EXPECT_EQ(0.0f + v.x_, w.x_);
  EXPECT_EQ(0.0f + v.y_, w.y_);
  EXPECT_EQ(0.0f + v.z_, w.z_);
  EXPECT_EQ(0.0f + v.w_, w.w_);
}

TEST_P(TestVector4D, TestSubtractAssignOp) {
  float a = std::get<0>(GetParam()), b = std::get<1>(GetParam()),
        c = std::get<2>(GetParam()), d = std::get<3>(GetParam());

  Vector4D v = Vector4D(a, b, c, d), w = Vector4D(0.0f, 0.0f, 0.0f, 0.0f);

  w -= v;

  EXPECT_EQ(0.0f - v.x_, w.x_);
  EXPECT_EQ(0.0f - v.y_, w.y_);
  EXPECT_EQ(0.0f - v.z_, w.z_);
  EXPECT_EQ(0.0f - v.w_, w.w_);
}

TEST_P(TestVector4D, TestMultiplyAssignOp) {
  float n = 2.0f, a = std::get<0>(GetParam()), b = std::get<1>(GetParam()),
        c = std::get<2>(GetParam()), d = std::get<3>(GetParam());

  Vector4D v = Vector4D(a, b, c, d);

  v *= n;

  EXPECT_EQ(a * n, v.x_);
  EXPECT_EQ(b * n, v.y_);
  EXPECT_EQ(c * n, v.z_);
  EXPECT_EQ(d * n, v.w_);
}

TEST_P(TestVector4D, TestDivideAssignOp) {
  float n = 2.0f, a = std::get<0>(GetParam()), b = std::get<1>(GetParam()),
        c = std::get<2>(GetParam()), d = std::get<3>(GetParam());

  Vector4D v = Vector4D(a, b, c, d);

  v /= n;

  EXPECT_EQ(a / n, v.x_);
  EXPECT_EQ(b / n, v.y_);
  EXPECT_EQ(c / n, v.z_);
  EXPECT_EQ(d / n, v.w_);
}

TEST_P(TestVector4D, TestDot) {
  float a = std::get<0>(GetParam()), b = std::get<1>(GetParam()),
        c = std::get<2>(GetParam()), d = std::get<3>(GetParam());

  Vector4D v = Vector4D(a, b, c, d), w = Vector4D(d, c, b, a);

  EXPECT_EQ(d * a + b * c + c * b + d * a, Dot(v, w));
}

TEST_P(TestVector4D, TestMagnitude) {
  float a = std::get<0>(GetParam()), b = std::get<1>(GetParam()),
        c = std::get<2>(GetParam()), d = std::get<3>(GetParam()),
        magnitude = std::sqrt(a * a + b * b + c * c + d * d);

  Vector4D v = Vector4D(a, b, c, d);

  EXPECT_NEAR(magnitude, Magnitude(v), kTolerance);
}

TEST_P(TestVector4D, TestInverseMagnitude) {
  float a = std::get<0>(GetParam()), b = std::get<1>(GetParam()),
        c = std::get<2>(GetParam()), d = std::get<3>(GetParam()),
        magnitude = std::sqrt(a * a + b * b + c * c + d * d);

  Vector4D v = Vector4D(a, b, c, d);

  if (a == 0 && b == 0 && c == 0 && d == 0) {
    EXPECT_NO_FATAL_FAILURE(InverseMagnitude(v));
  } else {
    EXPECT_NEAR(1.0f / magnitude, InverseMagnitude(v), kTolerance);
  }
}

TEST_P(TestVector4D, TestISquaredMagnitude) {
  float a = std::get<0>(GetParam()), b = std::get<1>(GetParam()),
        c = std::get<2>(GetParam()), d = std::get<3>(GetParam()),
        magnitude = std::sqrt(a * a + b * b + c * c + d * d);

  Vector4D v = Vector4D(a, b, c, d);

  EXPECT_NEAR(magnitude * magnitude, SquaredMagnitude(v), kTolerance);
}

TEST_P(TestVector4D, TestProjection) {
  float a = std::get<0>(GetParam()), b = std::get<1>(GetParam()),
        c = std::get<2>(GetParam()), d = std::get<3>(GetParam());

  Vector4D v = Vector4D(a, b, c, d), w = Vector4D(d, c, b, a);

  if (a == 0 && b == 0 && c == 0 && d == 0) {
    EXPECT_NO_FATAL_FAILURE(Projection(v, w));
  } else {
    Vector4D u = Projection(v, w);

    EXPECT_NEAR(
        d * ((a * d + b * c + c * b + d * a) / (d * d + c * c + b * b + a * a)),
        u.x_, kTolerance);
    EXPECT_NEAR(
        c * ((a * d + b * c + c * b + d * a) / (d * d + c * c + b * b + a * a)),
        u.y_, kTolerance);
    EXPECT_NEAR(
        b * ((a * d + b * c + c * b + d * a) / (d * d + c * c + b * b + a * a)),
        u.z_, kTolerance);
    EXPECT_NEAR(
        a * ((a * d + b * c + c * b + d * a) / (d * d + c * c + b * b + a * a)),
        u.w_, kTolerance);
  }
}

TEST_P(TestVector4D, TestRejection) {
  float a = std::get<0>(GetParam()), b = std::get<1>(GetParam()),
        c = std::get<2>(GetParam()), d = std::get<3>(GetParam());

  Vector4D v = Vector4D(a, b, c, d), w = Vector4D(d, c, b, a);

  if (a == 0 && b == 0 && c == 0 && d == 0) {
    EXPECT_NO_FATAL_FAILURE(Rejection(v, w));
  } else {
    Vector4D u = Rejection(v, w);

    EXPECT_NEAR(a - d * ((a * d + b * c + c * b + d * a) /
                         (d * d + c * c + b * b + a * a)),
                u.x_, kTolerance);
    EXPECT_NEAR(b - c * ((a * d + b * c + c * b + d * a) /
                         (d * d + c * c + b * b + a * a)),
                u.y_, kTolerance);
    EXPECT_NEAR(c - b * ((a * d + b * c + c * b + d * a) /
                         (d * d + c * c + b * b + a * a)),
                u.z_, kTolerance);
    EXPECT_NEAR(d - a * ((a * d + b * c + c * b + d * a) /
                         (d * d + c * c + b * b + a * a)),
                u.w_, kTolerance);
  }
}

TEST_P(TestVector4D, TestNegateOp) {
  float a = std::get<0>(GetParam()), b = std::get<1>(GetParam()),
        c = std::get<2>(GetParam()), d = std::get<3>(GetParam());

  Vector4D v = Vector4D(a, b, c, d), w = -v;

  EXPECT_EQ(-v.x_, w.x_);
  EXPECT_EQ(-v.y_, w.y_);
  EXPECT_EQ(-v.z_, w.z_);
  EXPECT_EQ(-v.w_, w.w_);
}

TEST_P(TestVector4D, TestAddOp) {
  float a = std::get<0>(GetParam()), b = std::get<1>(GetParam()),
        c = std::get<2>(GetParam()), d = std::get<3>(GetParam());

  Vector4D v = Vector4D(a, b, c, d), w = Vector4D(0.0f, 0.0f, 0.0f, 0.0f),
           u = v + w;

  EXPECT_EQ(v.x_ + w.x_, u.x_);
  EXPECT_EQ(v.y_ + w.y_, u.y_);
  EXPECT_EQ(v.z_ + w.z_, u.z_);
  EXPECT_EQ(v.w_ + w.w_, u.w_);
}

TEST_P(TestVector4D, TestSubtractOp) {
  float a = std::get<0>(GetParam()), b = std::get<1>(GetParam()),
        c = std::get<2>(GetParam()), d = std::get<3>(GetParam());

  Vector4D v = Vector4D(a, b, c, d), w = Vector4D(0.0f, 0.0f, 0.0f, 0.0f),
           u = v - w;

  EXPECT_EQ(v.x_ - w.x_, u.x_);
  EXPECT_EQ(v.y_ - w.y_, u.y_);
  EXPECT_EQ(v.z_ - w.z_, u.z_);
  EXPECT_EQ(v.w_ - w.w_, u.w_);
}

TEST_P(TestVector4D, TestMultiplyOpRight) {
  float n = 2.0f, a = std::get<0>(GetParam()), b = std::get<1>(GetParam()),
        c = std::get<2>(GetParam()), d = std::get<3>(GetParam());
  Vector4D v = Vector4D(a, b, c, d), w = v * n;

  EXPECT_EQ(v.x_ * n, w.x_);
  EXPECT_EQ(v.y_ * n, w.y_);
  EXPECT_EQ(v.z_ * n, w.z_);
  EXPECT_EQ(v.w_ * n, w.w_);
}

TEST_P(TestVector4D, TestMultiplyOpLeft) {
  float n = 2.0f, a = std::get<0>(GetParam()), b = std::get<1>(GetParam()),
        c = std::get<2>(GetParam()), d = std::get<3>(GetParam());
  Vector4D v = Vector4D(a, b, c, d), w = n * v;

  EXPECT_EQ(n * v.x_, w.x_);
  EXPECT_EQ(n * v.y_, w.y_);
  EXPECT_EQ(n * v.z_, w.z_);
  EXPECT_EQ(n * v.w_, w.w_);
}

TEST_P(TestVector4D, TestDivideOp) {
  float n = 2.0f, a = std::get<0>(GetParam()), b = std::get<1>(GetParam()),
        c = std::get<2>(GetParam()), d = std::get<3>(GetParam());
  Vector4D v = Vector4D(a, b, c, d), w = v / n;

  EXPECT_EQ(v.x_ / n, w.x_);
  EXPECT_EQ(v.y_ / n, w.y_);
  EXPECT_EQ(v.z_ / n, w.z_);
  EXPECT_EQ(v.w_ / n, w.w_);
}

}  // namespace TestBBMaths::TestVector4D
