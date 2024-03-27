#include <numbers>

#include "Maths.h"
#include "gtest/gtest.h"

namespace TestBBMaths::TestMaths {

using namespace BBMaths;

const float kTolerance = 0.0001f;

TEST(TestMaths, TestDegToRad) {
  float aExpect = 0.0f, bExpect = std::numbers::pi / 2.0f,
        cExpect = std::numbers::pi, dExpect = 3.0f * std::numbers::pi / 2.0f,
        eExpect = 2.0f * std::numbers::pi, a = 0.0f, b = 90.0f, c = 180.0f,
        d = 270.0f, e = 360.0f;
  EXPECT_NEAR(aExpect, DegToRad(a), kTolerance);
  EXPECT_NEAR(bExpect, DegToRad(b), kTolerance);
  EXPECT_NEAR(cExpect, DegToRad(c), kTolerance);
  EXPECT_NEAR(dExpect, DegToRad(d), kTolerance);
  EXPECT_NEAR(eExpect, DegToRad(e), kTolerance);
}

TEST(TestMaths, TestRadToDeg) {
  float aExpect = 0.0f, bExpect = 90.0f, cExpect = 180.0f, dExpect = 270.0f,
        eExpect = 360.0f, a = 0.0f, b = std::numbers::pi / 2.0f,
        c = std::numbers::pi, d = 3.0f * std::numbers::pi / 2.0f,
        e = 2.0f * std::numbers::pi;
  EXPECT_NEAR(aExpect, RadToDeg(a), kTolerance);
  EXPECT_NEAR(bExpect, RadToDeg(b), kTolerance);
  EXPECT_NEAR(cExpect, RadToDeg(c), kTolerance);
  EXPECT_NEAR(dExpect, RadToDeg(d), kTolerance);
  EXPECT_NEAR(eExpect, RadToDeg(e), kTolerance);
}

}  // namespace TestBBMaths::TestMaths
