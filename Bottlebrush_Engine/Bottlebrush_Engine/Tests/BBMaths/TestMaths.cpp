#include "Maths.h"
#include "gtest/gtest.h"

namespace TestBBMaths::TestMaths {

using namespace BBMaths;

const float kTolerance = 0.0001f;

TEST(TestMaths, TestCosMinimum) {
  float expect = -1.0f, a = kPi;
  EXPECT_NEAR(expect, Cos(a), kTolerance);
}

TEST(TestMaths, TestCosMaximum) {
  float expect = 1.0f, a = 0.0f;
  EXPECT_NEAR(expect, Cos(a), kTolerance);
}

TEST(TestMaths, TestCosInflection) {
  float expect = 0.0f, a = kPiOver2, b = k3PiOver2;
  EXPECT_NEAR(expect, Cos(a), kTolerance);
  EXPECT_NEAR(expect, Cos(b), kTolerance);
}

TEST(TestMaths, TestSinMinimum) {
  float expect = -1.0f, a = k3PiOver2;
  EXPECT_NEAR(expect, Sin(a), kTolerance);
}

TEST(TestMaths, TestSinMaximum) {
  float expect = 1.0f, a = kPiOver2;
  EXPECT_NEAR(expect, Sin(a), kTolerance);
}

TEST(TestMaths, TestSinInflection) {
  float expect = 0.0f, a = 0.0f;
  EXPECT_NEAR(expect, Sin(a), kTolerance);
  EXPECT_NEAR(expect, Sin(a), kTolerance);
}

TEST(TestMaths, TestTanMinimum) {
  float expect = 0.0f, a = 0.0f, b = kPi;
  EXPECT_NEAR(expect, Tan(a), kTolerance);
  EXPECT_NEAR(expect, Tan(b), kTolerance);
}

TEST(TestMaths, TestTanMaximum) {
  float expect = 1.0f, a = kPiOver4;
  EXPECT_NEAR(expect, Tan(a), kTolerance);
}

TEST(TestMaths, TestTanVariation) {
  float aExpect = 1.0f / std::sqrt(3), bExpect = std::sqrt(3), a = kPiOver6,
        b = kPiOver3;
  EXPECT_NEAR(aExpect, Tan(a), kTolerance);
  EXPECT_NEAR(bExpect, Tan(b), kTolerance);
}

TEST(TestMaths, TestSqrtPositive) {
  float aExpect = 1.0f, bExpect = 1.4142f, cExpect = 2.0f, dExpect = 3.0f,
        a = 1.0f, b = 2.0f, c = 4.0f, d = 9.0f;
  EXPECT_NEAR(aExpect, Sqrt(a), kTolerance);
  EXPECT_NEAR(bExpect, Sqrt(b), kTolerance);
  EXPECT_NEAR(cExpect, Sqrt(c), kTolerance);
  EXPECT_NEAR(dExpect, Sqrt(d), kTolerance);
}

TEST(TestMaths, TestSqrtZero) {
  float expect = 0.0f, a = 0.0f;
  EXPECT_NEAR(expect, Sqrt(a), kTolerance);
}

TEST(TestMaths, TestSqrtNegative) {
  float a = -1.0f;
  EXPECT_HRESULT_FAILED(Sqrt(a));
}

TEST(TestMaths, TestInverseSqrtPositive) {
  float aExpect = 1.0f, bExpect = 0.7071f, cExpect = 0.5f, dExpect = 0.3333f,
        a = 1.0f, b = 2.0f, c = 4.0f, d = 9.0f;
  EXPECT_NEAR(aExpect, InverseSqrt(a), kTolerance);
  EXPECT_NEAR(bExpect, InverseSqrt(b), kTolerance);
  EXPECT_NEAR(cExpect, InverseSqrt(c), kTolerance);
  EXPECT_NEAR(dExpect, InverseSqrt(d), kTolerance);
}

TEST(TestMaths, TestInverseSqrtZero) {
  float a = 0.0f;
  EXPECT_NO_FATAL_FAILURE(InverseSqrt(a));
}

TEST(TestMaths, TestInverseSqrtNegative) {
  float a = -1.0f;
  EXPECT_NO_FATAL_FAILURE(InverseSqrt(a));
}

}  // namespace TestBBMaths::TestMaths
