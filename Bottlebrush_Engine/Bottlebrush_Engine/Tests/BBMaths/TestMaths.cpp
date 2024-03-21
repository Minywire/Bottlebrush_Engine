#include <limits>

#include "Maths.h"
#include "gtest/gtest.h"

namespace TestBBMaths::TestMaths {

using namespace BBMaths;

const float kTolerance = 0.0001f;

TEST(TestMaths, TestCosMin) {
  float expect = -1.0f, a = kPi;
  EXPECT_NEAR(expect, Cos(a), kTolerance);
}

TEST(TestMaths, TestCosMax) {
  float expect = 1.0f, a = 0.0f;
  EXPECT_NEAR(expect, Cos(a), kTolerance);
}

TEST(TestMaths, TestCosInflection) {
  float expect = 0.0f, a = kPiOver2, b = k3PiOver2;
  EXPECT_NEAR(expect, Cos(a), kTolerance);
  EXPECT_NEAR(expect, Cos(b), kTolerance);
}

TEST(TestMaths, TestSinMin) {
  float expect = -1.0f, a = k3PiOver2;
  EXPECT_NEAR(expect, Sin(a), kTolerance);
}

TEST(TestMaths, TestSinMax) {
  float expect = 1.0f, a = kPiOver2;
  EXPECT_NEAR(expect, Sin(a), kTolerance);
}

TEST(TestMaths, TestSinInflection) {
  float expect = 0.0f, a = 0.0f;
  EXPECT_NEAR(expect, Sin(a), kTolerance);
  EXPECT_NEAR(expect, Sin(a), kTolerance);
}

TEST(TestMaths, TestTanMin) {
  float expect = 0.0f, a = 0.0f, b = kPi;
  EXPECT_NEAR(expect, Tan(a), kTolerance);
  EXPECT_NEAR(expect, Tan(b), kTolerance);
}

TEST(TestMaths, TestTanMax) {
  float expect = 1.0f, a = kPiOver4;
  EXPECT_NEAR(expect, Tan(a), kTolerance);
}

TEST(TestMaths, TestTanVariation) {
  float aExpect = 1.0f / std::sqrt(3), bExpect = std::sqrt(3), a = kPiOver6,
        b = kPiOver3;
  EXPECT_NEAR(aExpect, Tan(a), kTolerance);
  EXPECT_NEAR(bExpect, Tan(b), kTolerance);
}

TEST(TestMaths, TestArcCosMin) {
  float expect = kPi, a = -1.0f;
  EXPECT_NEAR(expect, ArcCos(a), kTolerance);
}

TEST(TestMaths, TestArcCosMax) {
  float expect = 0.0f, a = 1.0f;
  EXPECT_NEAR(expect, ArcCos(a), kTolerance);
}

TEST(TestMaths, TestArcCosOutOfBound) {
  float a = -1.1f, b = 1.1f;
  EXPECT_NO_FATAL_FAILURE(ArcCos(a));
  EXPECT_NO_FATAL_FAILURE(ArcCos(b));
}

TEST(TestMaths, TestArcSinMin) {
  float expect = -kPiOver2, a = -1.0f;
  EXPECT_NEAR(expect, ArcSin(a), kTolerance);
}

TEST(TestMaths, TestArcSinMax) {
  float expect = kPiOver2, a = 1.0f;
  EXPECT_NEAR(expect, ArcSin(a), kTolerance);
}

TEST(TestMaths, TestArcSinOutOfBound) {
  float a = -1.1f, b = 1.1f;
  EXPECT_NO_FATAL_FAILURE(ArcSin(a));
  EXPECT_NO_FATAL_FAILURE(ArcSin(b));
}

TEST(TestMaths, TestArcTanVariation) {
  float aExpect = 1.0038f, bExpect = 1.2626f, cExpect = 1.3616f,
        dExpect = 1.4129f, a = kPiOver2, b = kPi, c = k3PiOver2, d = k2Pi;
  EXPECT_NEAR(aExpect, ArcTan(a), kTolerance);
  EXPECT_NEAR(bExpect, ArcTan(b), kTolerance);
  EXPECT_NEAR(cExpect, ArcTan(c), kTolerance);
  EXPECT_NEAR(dExpect, ArcTan(d), kTolerance);
}

TEST(TestMaths, TestLogZero) {
  float a = 0.0f;
  EXPECT_NO_FATAL_FAILURE(Log(a));
}

TEST(TestMaths, TestLogOne) {
  float a = 1.0f;
  EXPECT_EQ(0.0f, Log(a));
}

TEST(TestMaths, TestLogPos) {
  float expect = 1.0f, a = 2.7182f;
  EXPECT_NEAR(expect, Log(a), kTolerance);
}

TEST(TestMaths, TestLogNeg) {
  float a = -1.0f;
  EXPECT_NO_FATAL_FAILURE(Log(a));
}

TEST(TestMaths, TestLog10Zero) {
  float a = 0.0f;
  EXPECT_NO_FATAL_FAILURE(Log10(a));
}

TEST(TestMaths, TestLog10One) {
  float a = 1.0f;
  EXPECT_EQ(0.0f, Log10(a));
}

TEST(TestMaths, TestLog10Pos) {
  float expect = 1.0f, a = 10.0f;
  EXPECT_NEAR(expect, Log10(a), kTolerance);
}

TEST(TestMaths, TestLog10Neg) {
  float a = -1.0f;
  EXPECT_NO_FATAL_FAILURE(Log10(a));
}

TEST(TestMaths, TestLog2Zero) {
  float a = 0.0f;
  EXPECT_NO_FATAL_FAILURE(Log2(a));
}

TEST(TestMaths, TestLog2One) {
  float a = 1.0f;
  EXPECT_EQ(0.0f, Log2(a));
}

TEST(TestMaths, TestLog2Pos) {
  float expect = 1.0f, a = 2.0f;
  EXPECT_NEAR(expect, Log2(a), kTolerance);
}

TEST(TestMaths, TestLog2Neg) {
  float a = -1.0f;
  EXPECT_NO_FATAL_FAILURE(Log2(a));
}

TEST(TestMaths, TestExpZero) {
  float a = 0.0f;
  EXPECT_EQ(1.0f, Exp(a));
}

TEST(TestMaths, TestExpNegInf) {
  float a = -std::numeric_limits<float>::infinity();
  EXPECT_EQ(0.0f, Exp(a));
}

TEST(TestMaths, TestExpPosInf) {
  float a = std::numeric_limits<float>::infinity();
  EXPECT_EQ(std::numeric_limits<float>::infinity(), Exp(a));
}

TEST(TestMaths, TestExpPos) {
  float a = 1.0f;
  EXPECT_NEAR(2.7182f, Exp(a), kTolerance);
}

TEST(TestMaths, TestExpNeg) {
  float a = -1.0f;
  EXPECT_NEAR(0.3678f, Exp(a), kTolerance);
}

TEST(TestMaths, TestExp2Zero) {
  float a = 0.0f;
  EXPECT_EQ(1.0f, Exp2(a));
}

TEST(TestMaths, TestExp2NegInf) {
  float a = -std::numeric_limits<float>::infinity();
  EXPECT_EQ(0.0f, Exp2(a));
}

TEST(TestMaths, TestExp2PosInf) {
  float a = std::numeric_limits<float>::infinity();
  EXPECT_EQ(std::numeric_limits<float>::infinity(), Exp2(a));
}

TEST(TestMaths, TestExp2Pos) {
  float a = 1.0f;
  EXPECT_NEAR(2.0f, Exp2(a), kTolerance);
}

TEST(TestMaths, TestExp2Neg) {
  float a = -1.0f;
  EXPECT_NEAR(0.5f, Exp2(a), kTolerance);
}

TEST(TestMaths, TestSqrtPos) {
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

TEST(TestMaths, TestSqrtNeg) {
  float a = -1.0f;
  EXPECT_NO_FATAL_FAILURE(Sqrt(a));
}

TEST(TestMaths, TestInverseSqrtPos) {
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

TEST(TestMaths, TestInverseSqrtNeg) {
  float a = -1.0f;
  EXPECT_NO_FATAL_FAILURE(InverseSqrt(a));
}

TEST(TestMaths, TestDegToRad) {
  float aExpect = 0.0f, bExpect = kPiOver2, cExpect = kPi, dExpect = k3PiOver2,
        eExpect = k2Pi, a = 0.0f, b = 90.0f, c = 180.0f, d = 270.0f, e = 360.0f;
  EXPECT_NEAR(aExpect, DegToRad(a), kTolerance);
  EXPECT_NEAR(bExpect, DegToRad(b), kTolerance);
  EXPECT_NEAR(cExpect, DegToRad(c), kTolerance);
  EXPECT_NEAR(dExpect, DegToRad(d), kTolerance);
  EXPECT_NEAR(eExpect, DegToRad(e), kTolerance);
}

TEST(TestMaths, TestRadToDeg) {
  float aExpect = 0.0f, bExpect = 90.0f, cExpect = 180.0f, dExpect = 270.0f,
        eExpect = 360.0f, a = 0.0f, b = kPiOver2, c = kPi, d = k3PiOver2,
        e = k2Pi;
  EXPECT_NEAR(aExpect, RadToDeg(a), kTolerance);
  EXPECT_NEAR(bExpect, RadToDeg(b), kTolerance);
  EXPECT_NEAR(cExpect, RadToDeg(c), kTolerance);
  EXPECT_NEAR(dExpect, RadToDeg(d), kTolerance);
  EXPECT_NEAR(eExpect, RadToDeg(e), kTolerance);
}

}  // namespace TestBBMaths::TestMaths
