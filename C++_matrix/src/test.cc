#include <gtest/gtest.h>

#include "s21_matrix_oop.h"

TEST(Constructor, matrix) {
  S21Matrix a;
  ASSERT_EQ(a.GetRows(), 0);
  ASSERT_EQ(a.GetCols(), 0);
}

TEST(Constructor, matrix_size) {
  S21Matrix a(4, 4);
  ASSERT_EQ(a.GetRows(), 4);
  ASSERT_EQ(a.GetCols(), 4);
  for (int i = 0; i < 4; ++i) {
    for (int j = 0; j < 4; ++j) {
      ASSERT_NEAR(a(i, j), 0.0, 1e-6);
    }
  }
}

TEST(Constructor, matrix_neg_rows) { ASSERT_ANY_THROW(S21Matrix a(-3, 1)); }

TEST(Constructor, matrix_neg_cols) { ASSERT_ANY_THROW(S21Matrix a(1, -3)); }

TEST(Constructor, copy) {
  S21Matrix a(5, 5);
  double x = 1.0;
  for (int i = 0; i < a.GetRows(); i++) {
    for (int j = 0; j < a.GetCols(); j++) {
      a(i, j) = x;
      x++;
    }
  }
  S21Matrix b(a);
  for (int i = 0; i < a.GetRows(); i++) {
    for (int j = 0; j < a.GetCols(); j++) {
      ASSERT_NEAR(a(i, j), b(i, j), 1e-6);
    }
  }
}

TEST(Constructor, move) {
  S21Matrix a(5, 5);
  int x = 1;
  int y = 1;
  for (int i = 0; i < a.GetRows(); i++) {
    for (int j = 0; j < a.GetCols(); j++) {
      a(i, j) = x;
      x++;
    }
  }
  S21Matrix b(std::move(a));
  ASSERT_EQ(b.GetRows(), 5);
  ASSERT_EQ(b.GetCols(), 5);
  for (int i = 0; i < b.GetRows(); i++) {
    for (int j = 0; j < b.GetCols(); j++) {
      ASSERT_EQ(y, b(i, j));
      y++;
    }
  }
  ASSERT_EQ(a.GetRows(), 0);
  ASSERT_EQ(a.GetCols(), 0);
}

TEST(Operations, Equal) {
  S21Matrix a(5, 5);
  S21Matrix b(5, 5);
  S21Matrix c(5, 5);
  S21Matrix d(6, 5);
  S21Matrix e;
  double x = 1;
  for (int i = 0; i < a.GetRows(); i++) {
    for (int j = 0; j < a.GetCols(); j++) {
      a(i, j) = x;
      b(i, j) = x;
      c(i, j) = x;
      d(i, j) = x + 1;
      x++;
    }
  }
  c(4, 4) = 1;
  EXPECT_TRUE(a == b);
  EXPECT_FALSE(a == c);
  EXPECT_FALSE(a == d);
  EXPECT_FALSE(a == e);
}

TEST(Operations, Equal1) {
  S21Matrix a;
  S21Matrix b(5, 5);
  EXPECT_FALSE(a == b);
}

TEST(Operations, Equal2) {
  S21Matrix b;
  S21Matrix a(5, 5);
  EXPECT_FALSE(b == a);
}

TEST(Operations, SumMatrix) {
  S21Matrix a(5, 5);
  S21Matrix b(5, 5);
  S21Matrix c(5, 5);
  double x = 1.0;
  for (int i = 0; i < a.GetRows(); i++) {
    for (int j = 0; j < a.GetCols(); j++) {
      a(i, j) = x;
      b(i, j) = x;
      c(i, j) = x + x;
      x++;
    }
  }
  a.SumMatrix(b);
  for (int i = 0; i < a.GetRows(); i++) {
    for (int j = 0; j < a.GetCols(); j++) {
      ASSERT_NEAR(a(i, j), c(i, j), 1e-6);
    }
  }
}

TEST(Operations, SumMatrix2) {
  S21Matrix a(3, 6);
  S21Matrix b(3, 7);
  ASSERT_ANY_THROW(a.SumMatrix(b));
}

TEST(Operations, SubMatrix) {
  S21Matrix a(5, 5);
  S21Matrix b(5, 5);
  S21Matrix c(5, 5);
  double x = 2.0;
  double y = 1.0;
  for (int i = 0; i < a.GetRows(); i++) {
    for (int j = 0; j < a.GetCols(); j++) {
      a(i, j) = x;
      b(i, j) = y;
      c(i, j) = x - y;
      x++;
    }
  }
  a.SubMatrix(b);
  for (int i = 0; i < a.GetRows(); i++) {
    for (int j = 0; j < a.GetCols(); j++) {
      ASSERT_NEAR(a(i, j), c(i, j), 1e-6);
    }
  }
}

TEST(Operations, SubMatrix2) {
  S21Matrix a(3, 6);
  S21Matrix b(3, 7);
  S21Matrix c;
  ASSERT_ANY_THROW(a.SubMatrix(b));
  ASSERT_ANY_THROW(a.SubMatrix(c));
  ASSERT_ANY_THROW(c.SubMatrix(a));
}

TEST(Operations, MulNumber) {
  S21Matrix a(5, 5);
  S21Matrix b(5, 5);
  double x = 1.0;
  double y = 2.0;
  for (int i = 0; i < a.GetRows(); i++) {
    for (int j = 0; j < a.GetCols(); j++) {
      a(i, j) = x;
      b(i, j) = x * y;
      x++;
    }
  }
  a.MulNumber(y);
  EXPECT_TRUE(a == b);
}

TEST(Operations, MulNumber2) {
  S21Matrix a;
  ASSERT_ANY_THROW(a.MulNumber(2));
}

TEST(Operations, MulMatrix) {
  S21Matrix a(5, 3);
  S21Matrix b(3, 5);
  S21Matrix c(5, 5);
  double x = 2.0;
  double y = 3.0;
  for (int i = 0; i < a.GetRows(); i++) {
    for (int j = 0; j < a.GetCols(); j++) {
      a(i, j) = x;
    }
  }
  for (int i = 0; i < b.GetRows(); i++) {
    for (int j = 0; j < b.GetCols(); j++) {
      b(i, j) = y;
    }
  }
  a.MulMatrix(b);
  for (int i = 0; i < c.GetRows(); i++) {
    for (int j = 0; j < c.GetCols(); j++) {
      c(i, j) = 18;
    }
  }
  ASSERT_EQ(a.GetRows(), c.GetRows());
  ASSERT_EQ(a.GetCols(), c.GetCols());
  for (int i = 0; i < c.GetRows(); i++) {
    for (int j = 0; j < c.GetCols(); j++) {
      ASSERT_NEAR(a(i, j), c(i, j), 1e-6);
    }
  }
}

TEST(Operations, MulMatrix0) {
  S21Matrix a(2, 3);
  S21Matrix b(3, 2);
  S21Matrix c(2, 2);
  double x = 2.0;
  double y = 3.0;
  for (int i = 0; i < a.GetRows(); i++) {
    for (int j = 0; j < a.GetCols(); j++) {
      a(i, j) = x;
    }
  }
  a(1, 2) = 5;
  for (int i = 0; i < b.GetRows(); i++) {
    for (int j = 0; j < b.GetCols(); j++) {
      b(i, j) = y;
    }
  }
  a.MulMatrix(b);
  c(0, 0) = 18;
  c(0, 1) = 18;
  c(1, 0) = 27;
  c(1, 1) = 27;
  ASSERT_EQ(a.GetRows(), c.GetRows());
  ASSERT_EQ(a.GetCols(), c.GetCols());
  for (int i = 0; i < c.GetRows(); i++) {
    for (int j = 0; j < c.GetCols(); j++) {
      ASSERT_NEAR(a(i, j), c(i, j), 1e-6);
    }
  }
}

TEST(Operations, MulMatrix1) {
  S21Matrix a(3, 5);
  S21Matrix b(3, 5);
  ASSERT_ANY_THROW(a.MulMatrix(b));
}
TEST(Operations, MulMatrix2) {
  S21Matrix a;
  S21Matrix b(3, 5);
  S21Matrix c;
  ASSERT_ANY_THROW(a.MulMatrix(b));
  ASSERT_ANY_THROW(b.MulMatrix(c));
}

TEST(Operations, Transpose) {
  S21Matrix a(3, 3);
  a(0, 0) = 1;
  a(0, 1) = 2;
  a(0, 2) = 3;
  a(1, 0) = 4;
  a(1, 1) = 5;
  a(1, 2) = 6;
  a(2, 0) = 7;
  a(2, 1) = 2;
  a(2, 2) = 6;
  S21Matrix b = a.Transpose();
  ASSERT_NEAR(b(0, 0), 1, 1e-6);
  ASSERT_NEAR(b(0, 1), 4, 1e-6);
  ASSERT_NEAR(b(0, 2), 7, 1e-6);
  ASSERT_NEAR(b(1, 0), 2, 1e-6);
  ASSERT_NEAR(b(1, 1), 5, 1e-6);
  ASSERT_NEAR(b(1, 2), 2, 1e-6);
  ASSERT_NEAR(b(2, 0), 3, 1e-6);
  ASSERT_NEAR(b(2, 1), 6, 1e-6);
  ASSERT_NEAR(b(2, 2), 6, 1e-6);
}

TEST(Operations, Transpose1) {
  S21Matrix a(2, 4);
  S21Matrix b(4, 2);
  double x = 1;
  for (int i = 0; i < a.GetRows(); i++) {
    for (int j = 0; j < a.GetCols(); j++) {
      a(i, j) = x;
      x++;
    }
  }
  double y = 1;
  for (int i = 0; i < a.GetRows(); i++) {
    for (int j = 0; j < a.GetCols(); j++) {
      b(j, i) = y;
      y++;
    }
  }
  S21Matrix c(a.Transpose());
  ASSERT_TRUE(c == b);
}

TEST(Operations, Transpose2) {
  S21Matrix a(1, 1);
  S21Matrix c;
  a(0, 0) = 21;
  S21Matrix b = a.Transpose();
  ASSERT_NEAR(b(0, 0), 21, 1e-6);
  ASSERT_ANY_THROW(c.Transpose());
}

TEST(Operations, CalcComplements) {
  S21Matrix a(3, 3);
  a(0, 0) = 1;
  a(0, 1) = 2;
  a(0, 2) = 3;
  a(1, 0) = 0;
  a(1, 1) = 4;
  a(1, 2) = 2;
  a(2, 0) = 5;
  a(2, 1) = 2;
  a(2, 2) = 1;
  S21Matrix b = a.CalcComplements();
  ASSERT_NEAR(b(0, 0), 0, 1e-6);
  ASSERT_NEAR(b(0, 1), 10, 1e-6);
  ASSERT_NEAR(b(0, 2), -20, 1e-6);
  ASSERT_NEAR(b(1, 0), 4, 1e-6);
  ASSERT_NEAR(b(1, 1), -14, 1e-6);
  ASSERT_NEAR(b(1, 2), 8, 1e-6);
  ASSERT_NEAR(b(2, 0), -8, 1e-6);
  ASSERT_NEAR(b(2, 1), -2, 1e-6);
  ASSERT_NEAR(b(2, 2), 4, 1e-6);
}

TEST(Operations, CalcComplements2) {
  S21Matrix a(1, 1);
  a(0, 0) = 21;
  S21Matrix b = a.CalcComplements();
  ASSERT_NEAR(b(0, 0), 1, 1e-6);
}

TEST(Operations, CalcComplements3) {
  S21Matrix a(2, 3);
  ASSERT_ANY_THROW(a.CalcComplements());
}
TEST(Operations, CalcComplements4) {
  S21Matrix a;
  ASSERT_ANY_THROW(a.CalcComplements());
}

TEST(Operations, Determinant) {
  S21Matrix a(3, 3);
  a(0, 0) = 0;
  a(0, 1) = 9;
  a(0, 2) = 5;
  a(1, 0) = 4;
  a(1, 1) = 3;
  a(1, 2) = -5;
  a(2, 0) = -1;
  a(2, 1) = 6;
  a(2, 2) = -4;
  ASSERT_NEAR(a.Determinant(), 324.0, 1e-6);
}

TEST(Operations, Determinant0) {
  S21Matrix a(50, 50);
  double x = 1;
  for (int i = 0; i < a.GetRows(); i++) {
    for (int j = 0; j < a.GetCols(); j++) {
      a(i, j) = x;
      x++;
    }
  }
  ASSERT_NEAR(a.Determinant(), 0.0, 1e-6);
}

TEST(Operations, Determinant1) {
  S21Matrix a(4, 4);
  a(0, 0) = 1;
  a(0, 1) = 2;
  a(0, 2) = 3;
  a(0, 3) = 4;
  a(1, 0) = 5;
  a(1, 1) = 6;
  a(1, 2) = 7;
  a(1, 3) = 8;
  a(2, 0) = 9;
  a(2, 1) = -1;
  a(2, 2) = -2;
  a(2, 3) = -3;
  a(3, 0) = -14;
  a(3, 1) = 1;
  a(3, 2) = 1;
  a(3, 3) = -17;
  ASSERT_NEAR(a.Determinant(), 648, 1e-6);
}

TEST(Operations, Determinant2) {
  S21Matrix a(1, 1);
  a(0, 0) = 21.0;
  ASSERT_NEAR(a.Determinant(), 21.0, 1e-6);
}

TEST(Operations, Determinant3) {
  S21Matrix a(2, 3);
  ASSERT_ANY_THROW(a.Determinant());
}
TEST(Operations, Determinant4) {
  S21Matrix a;
  ASSERT_ANY_THROW(a.Determinant());
}

TEST(Operations, InverseMatrix) {
  S21Matrix a(3, 3);
  a(0, 0) = 2;
  a(0, 1) = 5;
  a(0, 2) = 7;
  a(1, 0) = 6;
  a(1, 1) = 3;
  a(1, 2) = 4;
  a(2, 0) = 5;
  a(2, 1) = -2;
  a(2, 2) = -3;
  S21Matrix b = a.InverseMatrix();
  ASSERT_NEAR(b(0, 1), -1, 1e-6);
  ASSERT_NEAR(b(0, 2), 1, 1e-6);
  ASSERT_NEAR(b(0, 0), 1, 1e-6);
  ASSERT_NEAR(b(1, 0), -38, 1e-6);
  ASSERT_NEAR(b(1, 1), 41, 1e-6);
  ASSERT_NEAR(b(1, 2), -34, 1e-6);
  ASSERT_NEAR(b(2, 0), 27, 1e-6);
  ASSERT_NEAR(b(2, 1), -29, 1e-6);
  ASSERT_NEAR(b(2, 2), 24, 1e-6);
}
TEST(Operations, InverseMatrix1) {
  S21Matrix a(1, 1);
  a(0, 0) = 2;

  S21Matrix b = a.InverseMatrix();
  ASSERT_NEAR(b(0, 0), 0.5, 1e-6);
}

TEST(Operations, InverseMatrix2) {
  S21Matrix a(4, 4);
  ASSERT_ANY_THROW(a.InverseMatrix());
}

TEST(Operations, InverseMatrix3) {
  S21Matrix a(4, 2);
  ASSERT_ANY_THROW(a.InverseMatrix());
}

TEST(Operators, plus) {
  S21Matrix a(5, 5);
  S21Matrix b(5, 5);
  S21Matrix c(5, 5);
  S21Matrix d;
  double x = 1.0;
  double y = 2.0;
  for (int i = 0; i < a.GetRows(); i++) {
    for (int j = 0; j < a.GetCols(); j++) {
      a(i, j) = x;
      b(i, j) = y;
      c(i, j) = x + y;
      x++;
      y++;
    }
  }
  EXPECT_TRUE((a + b) == c);
  ASSERT_ANY_THROW(a + d);
  ASSERT_ANY_THROW(d + a);
  EXPECT_TRUE((a += b) == c);
}

TEST(Operators, minus) {
  S21Matrix a(5, 5);
  S21Matrix b(5, 5);
  S21Matrix c(5, 5);
  S21Matrix d;
  double x = 2.0;
  double y = 1.0;
  for (int i = 0; i < a.GetRows(); i++) {
    for (int j = 0; j < a.GetCols(); j++) {
      a(i, j) = x;
      b(i, j) = y;
      c(i, j) = x - y;
      x++;
      y++;
    }
  }
  EXPECT_TRUE((a - b) == c);
  ASSERT_ANY_THROW(a + d);
  ASSERT_ANY_THROW(d + a);
  EXPECT_TRUE((a -= b) == c);
}

TEST(Operators, mul_N) {
  S21Matrix a(5, 5);
  S21Matrix c(5, 5);
  double x = 2.0;
  for (int i = 0; i < a.GetRows(); i++) {
    for (int j = 0; j < a.GetCols(); j++) {
      a(i, j) = x;
      c(i, j) = x * 2;
      x++;
    }
  }
  EXPECT_TRUE((a * 2) == c);
  EXPECT_TRUE((2 * a) == c);
  EXPECT_TRUE((a *= 2) == c);
}

TEST(Operators, mul_m) {
  S21Matrix a(2, 3);
  S21Matrix b(3, 2);
  S21Matrix c(2, 2);
  double x = 2.0;
  double y = 3.0;
  for (int i = 0; i < a.GetRows(); i++) {
    for (int j = 0; j < a.GetCols(); j++) {
      a(i, j) = x;
    }
  }
  a(1, 2) = 5;
  for (int i = 0; i < b.GetRows(); i++) {
    for (int j = 0; j < b.GetCols(); j++) {
      b(i, j) = y;
    }
  }
  c(0, 0) = 18;
  c(0, 1) = 18;
  c(1, 0) = 27;
  c(1, 1) = 27;
  EXPECT_TRUE((a * b) == c);
  EXPECT_TRUE((a *= b) == c);
}

TEST(Operators, index) {
  S21Matrix a(4, 4);
  a(0, 0) = 21;
  ASSERT_NEAR(a(0, 0), 21, 1e-6);
  ASSERT_ANY_THROW(a(3, 4));
  ASSERT_ANY_THROW(a(4, 3));
  ASSERT_ANY_THROW(a(1, -1));
  ASSERT_ANY_THROW(a(-2, 2));
}

TEST(Operators, set_Rows_Cols) {
  S21Matrix a(5, 5);
  S21Matrix b(2, 2);
  S21Matrix c(5, 5);
  a.SetRows(3);
  a.SetCols(4);
  b.SetRows(3);
  b.SetCols(4);
  ASSERT_EQ(a.GetRows(), 3);
  ASSERT_EQ(a.GetCols(), 4);
  ASSERT_EQ(a.GetRows(), 3);
  ASSERT_EQ(a.GetCols(), 4);
  ASSERT_ANY_THROW(c.SetRows(0));
  ASSERT_ANY_THROW(c.SetCols(0));
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
