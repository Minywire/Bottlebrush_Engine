#include "Point2D.h"
#include "gtest/gtest.h"

namespace TestBBMaths::TestPoint2D {

using namespace BBMaths;

const float A[11] = {-5.0f, -4.0f, -3.0f, -2.0f, -1.0f, 0.0f,
                     1.0f,  2.0f,  3.0f,  4.0f,  5.0f};
const float B[11] = {-5.0f, -4.0f, -3.0f, -2.0f, -1.0f, 0.0f,
                     1.0f,  2.0f,  3.0f,  4.0f,  5.0f};

TEST(TestPoint2D, TestAltCtor) {
  for (float a : A) {
    for (float b : B) {
      Point2D p = Point2D(a, b);

      EXPECT_EQ(a, p.x_);
      EXPECT_EQ(b, p.y_);
    }
  }
}

TEST(TestPoint2D, TestCopyCtor) {
  for (float a : A) {
    for (float b : B) {
      Point2D p = Point2D(a, b), q = Point2D(p);

      EXPECT_EQ(p.x_, q.x_);
      EXPECT_EQ(p.y_, q.y_);
    }
  }
}

TEST(TestPoint2D, TestAssignOp) {
  for (float a : A) {
    for (float b : B) {
      Point2D p = Point2D(a, b), q = p;

      EXPECT_EQ(p.x_, q.x_);
      EXPECT_EQ(p.y_, q.y_);
    }
  }
}

TEST(TestPoint2D, TestAddAssignOp) {
  for (float a : A) {
    for (float b : B) {
      Point2D p = Point2D(a, b), q = Point2D(0.0f, 0.0f);

      q += p;

      EXPECT_EQ(0.0f + p.x_, q.x_);
      EXPECT_EQ(0.0f + p.y_, q.y_);
    }
  }
}

TEST(TestPoint2D, TestSubtractAssignOp) {
  for (float a : A) {
    for (float b : B) {
      Point2D p = Point2D(a, b), q = Point2D(0.0f, 0.0f);

      q -= p;

      EXPECT_EQ(0.0f - p.x_, q.x_);
      EXPECT_EQ(0.0f - p.y_, q.y_);
    }
  }
}

TEST(TestPoint2D, TestMultiplyAssignOp) {
  float n = 2.0f;

  for (float a : A) {
    for (float b : B) {
      Point2D p = Point2D(a, b);

      p *= n;

      EXPECT_EQ(a * n, p.x_);
      EXPECT_EQ(b * n, p.y_);
    }
  }
}

TEST(TestPoint2D, TestDivideAssignOp) {
  float n = 2.0f;

  for (float a : A) {
    for (float b : B) {
      Point2D p = Point2D(a, b);

      p /= n;

      EXPECT_EQ(a / n, p.x_);
      EXPECT_EQ(b / n, p.y_);
    }
  }
}

TEST(TestPoint2D, TestNegateOp) {
  for (float a : A) {
    for (float b : B) {
      Point2D p = Point2D(a, b), q = -p;

      EXPECT_EQ(-p.x_, q.x_);
      EXPECT_EQ(-p.y_, q.y_);
    }
  }
}

TEST(TestPoint2D, TestAddOp) {
  for (float a : A) {
    for (float b : B) {
      Point2D p = Point2D(a, b), q = Point2D(0.0f, 0.0f), r = p + q;

      EXPECT_EQ(q.x_ + p.x_, r.x_);
      EXPECT_EQ(q.y_ + p.y_, r.y_);
    }
  }
}

TEST(TestPoint2D, TestSubtractOp) {
  for (float a : A) {
    for (float b : B) {
      Point2D p = Point2D(a, b), q = Point2D(0.0f, 0.0f), r = p - q;

      EXPECT_EQ(p.x_ - q.x_, r.x_);
      EXPECT_EQ(p.y_ - q.y_, r.y_);
    }
  }
}

TEST(TestPoint2D, TestMultiplyOpRight) {
  float n = 2.0f;

  for (float a : A) {
    for (float b : B) {
      Point2D p = Point2D(a, b), q = p * n;

      EXPECT_EQ(p.x_ * n, q.x_);
      EXPECT_EQ(p.y_ * n, q.y_);
    }
  }
}

TEST(TestPoint2D, TestMultiplyOpLeft) {
  float n = 2.0f;

  for (float a : A) {
    for (float b : B) {
      Point2D p = Point2D(a, b), q = n * p;

      EXPECT_EQ(n * p.x_, q.x_);
      EXPECT_EQ(n * p.y_, q.y_);
    }
  }
}

TEST(TestPoint2D, TestDivideOp) {
  float n = 2.0f;

  for (float a : A) {
    for (float b : B) {
      Point2D p = Point2D(a, b), q = p / n;

      EXPECT_EQ(p.x_ / n, q.x_);
      EXPECT_EQ(p.y_ / n, q.y_);
    }
  }
}

}  // namespace TestBBMaths::TestPoint2D
