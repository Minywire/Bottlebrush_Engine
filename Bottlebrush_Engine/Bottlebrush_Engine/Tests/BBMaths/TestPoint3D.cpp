#include "Point3D.h"
#include "gtest/gtest.h"

namespace TestBBMaths::TestPoint3D {

using namespace BBMaths;

const float A[11] = {-5.0f, -4.0f, -3.0f, -2.0f, -1.0f, 0.0f,
                     1.0f,  2.0f,  3.0f,  4.0f,  5.0f};
const float B[11] = {-5.0f, -4.0f, -3.0f, -2.0f, -1.0f, 0.0f,
                     1.0f,  2.0f,  3.0f,  4.0f,  5.0f};
const float C[11] = {-5.0f, -4.0f, -3.0f, -2.0f, -1.0f, 0.0f,
                     1.0f,  2.0f,  3.0f,  4.0f,  5.0f};

TEST(TestPoint3D, TestAltCtor) {
  for (float a : A) {
    for (float b : B) {
      for (float c : C) {
        Point3D p = Point3D(a, b, c);

        EXPECT_EQ(a, p.x_);
        EXPECT_EQ(b, p.y_);
        EXPECT_EQ(c, p.z_);
      }
    }
  }
}

TEST(TestPoint3D, TestCopyCtor) {
  for (float a : A) {
    for (float b : B) {
      for (float c : C) {
        Point3D p = Point3D(a, b, c), q = Point3D(p);

        EXPECT_EQ(p.x_, q.x_);
        EXPECT_EQ(p.y_, q.y_);
        EXPECT_EQ(p.z_, q.z_);
      }
    }
  }
}

TEST(TestPoint3D, TestAssignOp) {
  for (float a : A) {
    for (float b : B) {
      for (float c : C) {
        Point3D p = Point3D(a, b, c), q = p;

        EXPECT_EQ(p.x_, q.x_);
        EXPECT_EQ(p.y_, q.y_);
        EXPECT_EQ(p.z_, q.z_);
      }
    }
  }
}

TEST(TestPoint3D, TestAddAssignOp) {
  for (float a : A) {
    for (float b : B) {
      for (float c : C) {
        Point3D p = Point3D(a, b, c), q = Point3D(0.0f, 0.0f, 0.0f);

        q += p;

        EXPECT_EQ(0.0f + p.x_, q.x_);
        EXPECT_EQ(0.0f + p.y_, q.y_);
        EXPECT_EQ(0.0f + p.z_, q.z_);
      }
    }
  }
}

TEST(TestPoint3D, TestSubtractAssignOp) {
  for (float a : A) {
    for (float b : B) {
      for (float c : C) {
        Point3D p = Point3D(a, b, c), q = Point3D(0.0f, 0.0f, 0.0f);

        q -= p;

        EXPECT_EQ(0.0f - p.x_, q.x_);
        EXPECT_EQ(0.0f - p.y_, q.y_);
        EXPECT_EQ(0.0f - p.z_, q.z_);
      }
    }
  }
}

TEST(TestPoint3D, TestMultiplyAssignOp) {
  float n = 2.0f;

  for (float a : A) {
    for (float b : B) {
      for (float c : C) {
        Point3D p = Point3D(a, b, c);

        p *= n;

        EXPECT_EQ(a * n, p.x_);
        EXPECT_EQ(b * n, p.y_);
        EXPECT_EQ(c * n, p.z_);
      }
    }
  }
}

TEST(TestPoint3D, TestDivideAssignOp) {
  float n = 2.0f;

  for (float a : A) {
    for (float b : B) {
      for (float c : C) {
        Point3D p = Point3D(a, b, c);

        p /= n;

        EXPECT_EQ(a / n, p.x_);
        EXPECT_EQ(b / n, p.y_);
        EXPECT_EQ(c / n, p.z_);
      }
    }
  }
}

TEST(TestPoint3D, TestNegateOp) {
  for (float a : A) {
    for (float b : B) {
      for (float c : C) {
        Point3D p = Point3D(a, b, c), q = -p;

        EXPECT_EQ(-p.x_, q.x_);
        EXPECT_EQ(-p.y_, q.y_);
        EXPECT_EQ(-p.z_, q.z_);
      }
    }
  }
}

TEST(TestPoint3D, TestAddOp) {
  for (float a : A) {
    for (float b : B) {
      for (float c : C) {
        Point3D p = Point3D(a, b, c), q = Point3D(0.0f, 0.0f, 0.0f), r = p + q;

        EXPECT_EQ(q.x_ + p.x_, r.x_);
        EXPECT_EQ(q.y_ + p.y_, r.y_);
        EXPECT_EQ(q.z_ + p.z_, r.z_);
      }
    }
  }
}

TEST(TestPoint3D, TestSubtractOp) {
  for (float a : A) {
    for (float b : B) {
      for (float c : C) {
        Point3D p = Point3D(a, b, c), q = Point3D(0.0f, 0.0f, 0.0f), r = p - q;

        EXPECT_EQ(p.x_ - q.x_, r.x_);
        EXPECT_EQ(p.y_ - q.y_, r.y_);
        EXPECT_EQ(p.z_ - q.z_, r.z_);
      }
    }
  }
}

TEST(TestPoint3D, TestMultiplyOpRight) {
  float n = 2.0f;

  for (float a : A) {
    for (float b : B) {
      for (float c : C) {
        Point3D p = Point3D(a, b, c), q = p * n;

        EXPECT_EQ(p.x_ * n, q.x_);
        EXPECT_EQ(p.y_ * n, q.y_);
        EXPECT_EQ(p.z_ * n, q.z_);
      }
    }
  }
}

TEST(TestPoint3D, TestMultiplyOpLeft) {
  float n = 2.0f;

  for (float a : A) {
    for (float b : B) {
      for (float c : C) {
        Point3D p = Point3D(a, b, c), q = n * p;

        EXPECT_EQ(n * p.x_, q.x_);
        EXPECT_EQ(n * p.y_, q.y_);
        EXPECT_EQ(n * p.z_, q.z_);
      }
    }
  }
}

TEST(TestPoint3D, TestDivideOp) {
  float n = 2.0f;

  for (float a : A) {
    for (float b : B) {
      for (float c : C) {
        Point3D p = Point3D(a, b, c), q = p / n;

        EXPECT_EQ(p.x_ / n, q.x_);
        EXPECT_EQ(p.y_ / n, q.y_);
        EXPECT_EQ(p.z_ / n, q.z_);
      }
    }
  }
}

}  // namespace TestBBMaths::TestPoint3D
