#include <gtest/gtest.h>

#include "xmatrix.h"

// ReSharper disable CppNoDiscardExpression

using namespace xMatrix;

// Unit test for default constructor
TEST(xMatrixTest, DefaultConstructor) {
  const Matrix mat;

  EXPECT_EQ(mat.GetRows(), 3);
  EXPECT_EQ(mat.GetCols(), 3);
}

// Unit test for constructor with specified dimensions
TEST(xMatrixTest, ConstructorWithDimensions) {
  const Matrix mat(2, 4);

  EXPECT_EQ(mat.GetRows(), 2);
  EXPECT_EQ(mat.GetCols(), 4);
}

// Unit test for copy constructor
TEST(xMatrixTest, CopyConstructor) {
  Matrix mat1(2, 3);
  mat1(0, 0) = 1.0;
  mat1(0, 1) = 2.0;
  mat1(0, 2) = 3.0;
  mat1(1, 0) = 4.0;
  mat1(1, 1) = 5.0;
  mat1(1, 2) = 6.0;

  Matrix mat2(mat1);

  EXPECT_EQ(mat2.GetRows(), 2);
  EXPECT_EQ(mat2.GetCols(), 3);
  EXPECT_EQ(mat2(0, 0), 1.0);
  EXPECT_EQ(mat2(0, 1), 2.0);
  EXPECT_EQ(mat2(0, 2), 3.0);
  EXPECT_EQ(mat2(1, 0), 4.0);
  EXPECT_EQ(mat2(1, 1), 5.0);
  EXPECT_EQ(mat2(1, 2), 6.0);
}

// Unit test for move constructor
TEST(xMatrixTest, MoveConstructor) {
  Matrix mat1(2, 3);
  mat1(0, 0) = 1.0;
  mat1(0, 1) = 2.0;
  mat1(0, 2) = 3.0;
  mat1(1, 0) = 4.0;
  mat1(1, 1) = 5.0;
  mat1(1, 2) = 6.0;

  Matrix mat2(std::move(mat1));

  EXPECT_EQ(mat2.GetRows(), 2);
  EXPECT_EQ(mat2.GetCols(), 3);
  EXPECT_EQ(mat2(0, 0), 1.0);
  EXPECT_EQ(mat2(0, 1), 2.0);
  EXPECT_EQ(mat2(0, 2), 3.0);
  EXPECT_EQ(mat2(1, 0), 4.0);
  EXPECT_EQ(mat2(1, 1), 5.0);
  EXPECT_EQ(mat2(1, 2), 6.0);
}

// Unit test for GetRows function
TEST(xMatrixTest, GetRows) {
  const Matrix mat(2, 3);

  EXPECT_EQ(mat.GetRows(), 2);
}

// Unit test for GetCols function
TEST(xMatrixTest, GetCols) {
  Matrix mat(2, 3);

  EXPECT_EQ(mat.GetCols(), 3);
}

// Unit test for SetRows function
TEST(xMatrixTest, SetRows) {
  Matrix mat(2, 3);
  mat.SetRows(4);

  EXPECT_EQ(mat.GetRows(), 4);
  EXPECT_EQ(mat.GetCols(), 3);
}

// Unit test for SetCols function
TEST(xMatrixTest, SetCols) {
  Matrix mat(2, 3);
  mat.SetCols(4);

  EXPECT_EQ(mat.GetRows(), 2);
  EXPECT_EQ(mat.GetCols(), 4);
}

// Unit test for Resize function with larger dimensions
TEST(xMatrixTest, ResizeLarger) {
  Matrix mat(2, 3);
  mat(1, 1) = 1.0;
  mat.Resize(3, 4);

  EXPECT_EQ(mat.GetRows(), 3);
  EXPECT_EQ(mat.GetCols(), 4);
  EXPECT_EQ(mat(1, 1), 1.0);
}

// Unit test for Resize function with smaller dimensions
TEST(xMatrixTest, ResizeSmaller) {
  Matrix mat(2, 3);
  mat(0, 1) = 1.0;
  mat.Resize(1, 2);

  EXPECT_EQ(mat.GetRows(), 1);
  EXPECT_EQ(mat.GetCols(), 2);
  EXPECT_EQ(mat(0, 0), 0.0);
  EXPECT_EQ(mat(0, 1), 1.0);
}

// Unit test for Resize function with same dimensions
TEST(xMatrixTest, ResizeSame) {
  Matrix mat(2, 3);
  mat(1, 1) = 1.0;
  mat.Resize(2, 3);

  EXPECT_EQ(mat.GetRows(), 2);
  EXPECT_EQ(mat.GetCols(), 3);
  EXPECT_EQ(mat(1, 1), 1.0);
}

// Unit test for exception in SetRows function
TEST(xMatrixTest, SetRowsException) {
  Matrix mat(2, 3);

  EXPECT_THROW(mat.SetRows(-1), std::invalid_argument);
}

// Unit test for exception in SetCols function
TEST(xMatrixTest, SetColsException) {
  Matrix mat(2, 3);

  EXPECT_THROW(mat.SetCols(0), std::invalid_argument);
}

// Unit test for sEqMatrix function with equal matrices
TEST(xMatrixTest, sEqMatrixEqual) {
  Matrix mat1(2, 2);
  mat1(0, 0) = 1.0;
  mat1(0, 1) = 2.0;
  mat1(1, 0) = 3.0;
  mat1(1, 1) = 4.0;

  Matrix mat2(2, 2);
  mat2(0, 0) = 1.0;
  mat2(0, 1) = 2.0;
  mat2(1, 0) = 3.0;
  mat2(1, 1) = 4.0;

  EXPECT_TRUE(mat1.IsEqual(mat2));
}

// Unit test for sEqMatrix function with different matrices
TEST(xMatrixTest, sEqMatrixDifferent) {
  Matrix mat1(2, 2);
  mat1(0, 0) = 1.0;
  mat1(0, 1) = 2.0;
  mat1(1, 0) = 3.0;
  mat1(1, 1) = 4.0;

  Matrix mat2(2, 2);
  mat2(0, 0) = 1.0;
  mat2(0, 1) = 2.0;
  mat2(1, 0) = 3.0;
  mat2(1, 1) = 5.0;

  EXPECT_FALSE(mat1.IsEqual(mat2));
}

// Unit test for sEqMatrix function with different dimensions
TEST(xMatrixTest, sEqMatrixDifferentDimensions) {
  Matrix mat1(2, 2);
  mat1(0, 0) = 1.0;
  mat1(0, 1) = 2.0;
  mat1(1, 0) = 3.0;
  mat1(1, 1) = 4.0;

  Matrix mat2(3, 3);
  mat2(0, 0) = 1.0;
  mat2(0, 1) = 2.0;
  mat2(0, 2) = 3.0;
  mat2(1, 0) = 4.0;
  mat2(1, 1) = 5.0;
  mat2(1, 2) = 6.0;
  mat2(2, 0) = 7.0;
  mat2(2, 1) = 8.0;
  mat2(2, 2) = 9.0;

  EXPECT_FALSE(mat1.IsEqual(mat2));
}

// Unit test for SumMatrix function with matrices of the same size
TEST(xMatrixTest, SumMatrixSameSize) {
  Matrix mat1(2, 2);
  mat1(0, 0) = 1.0;
  mat1(0, 1) = 2.0;
  mat1(1, 0) = 3.0;
  mat1(1, 1) = 4.0;

  Matrix mat2(2, 2);
  mat2(0, 0) = 5.0;
  mat2(0, 1) = 6.0;
  mat2(1, 0) = 7.0;
  mat2(1, 1) = 8.0;

  mat1.SumMatrix(mat2);

  EXPECT_DOUBLE_EQ(mat1(0, 0), 6.0);
  EXPECT_DOUBLE_EQ(mat1(0, 1), 8.0);
  EXPECT_DOUBLE_EQ(mat1(1, 0), 10.0);
  EXPECT_DOUBLE_EQ(mat1(1, 1), 12.0);
}

// Unit test for SumMatrix function with matrices of different sizes
TEST(xMatrixTest, SumMatrixDifferentSize) {
  Matrix mat1(2, 2);
  const Matrix mat2(3, 3);

  EXPECT_THROW(mat1.SumMatrix(mat2), std::invalid_argument);
}

// Unit test for SubMatrix function with matrices of the same size
TEST(xMatrixTest, SubMatrixSameSize) {
  Matrix mat1(2, 2);
  mat1(0, 0) = 1.0;
  mat1(0, 1) = 2.0;
  mat1(1, 0) = 3.0;
  mat1(1, 1) = 4.0;

  Matrix mat2(2, 2);
  mat2(0, 0) = 5.0;
  mat2(0, 1) = 6.0;
  mat2(1, 0) = 7.0;
  mat2(1, 1) = 8.0;

  mat1.SubMatrix(mat2);

  EXPECT_DOUBLE_EQ(mat1(0, 0), -4.0);
  EXPECT_DOUBLE_EQ(mat1(0, 1), -4.0);
  EXPECT_DOUBLE_EQ(mat1(1, 0), -4.0);
  EXPECT_DOUBLE_EQ(mat1(1, 1), -4.0);
}

// Unit test for SubMatrix function with matrices of different sizes
TEST(xMatrixTest, SubMatrixDifferentSize) {
  Matrix mat1(2, 2);
  const Matrix mat2(3, 3);

  EXPECT_THROW(mat1.SubMatrix(mat2), std::invalid_argument);
}

// Unit test for MulNumber function with a positive number
TEST(xMatrixTest, MulNumberPositive) {
  Matrix mat1(2, 2);
  mat1(0, 0) = 1.0;
  mat1(0, 1) = 2.0;
  mat1(1, 0) = 3.0;
  mat1(1, 1) = 4.0;

  mat1.MulNumber(2.0);

  EXPECT_DOUBLE_EQ(mat1(0, 0), 2.0);
  EXPECT_DOUBLE_EQ(mat1(0, 1), 4.0);
  EXPECT_DOUBLE_EQ(mat1(1, 0), 6.0);
  EXPECT_DOUBLE_EQ(mat1(1, 1), 8.0);
}

// Unit test for MulNumber function with a negative number
TEST(xMatrixTest, MulNumberNegative) {
  Matrix mat1(2, 2);
  mat1(0, 0) = 1.0;
  mat1(0, 1) = 2.0;
  mat1(1, 0) = 3.0;
  mat1(1, 1) = 4.0;

  mat1.MulNumber(-2.0);

  EXPECT_DOUBLE_EQ(mat1(0, 0), -2.0);
  EXPECT_DOUBLE_EQ(mat1(0, 1), -4.0);
  EXPECT_DOUBLE_EQ(mat1(1, 0), -6.0);
  EXPECT_DOUBLE_EQ(mat1(1, 1), -8.0);
}

// Unit test for MulNumber function with a very large number
TEST(xMatrixTest, MulNumberLargeNumber) {
  Matrix mat1(2, 2);
  mat1(0, 0) = 1.0;
  mat1(0, 1) = 2.0;
  mat1(1, 0) = 3.0;
  mat1(1, 1) = 4.0;

  constexpr double largeNum = 1e20;

  mat1.MulNumber(largeNum);

  EXPECT_DOUBLE_EQ(mat1(0, 0), 1e20);
  EXPECT_DOUBLE_EQ(mat1(0, 1), 2e20);
  EXPECT_DOUBLE_EQ(mat1(1, 0), 3e20);
  EXPECT_DOUBLE_EQ(mat1(1, 1), 4e20);
}

// Unit test for MulMatrix function with valid matrices
TEST(xMatrixTest, MulMatrixValid) {
  Matrix mat1(2, 3);
  mat1(0, 0) = 1.0;
  mat1(0, 1) = 2.0;
  mat1(0, 2) = 3.0;
  mat1(1, 0) = 4.0;
  mat1(1, 1) = 5.0;
  mat1(1, 2) = 6.0;

  Matrix mat2(3, 2);
  mat2(0, 0) = 7.0;
  mat2(0, 1) = 8.0;
  mat2(1, 0) = 9.0;
  mat2(1, 1) = 10.0;
  mat2(2, 0) = 11.0;
  mat2(2, 1) = 12.0;

  mat1.MulMatrix(mat2);

  EXPECT_DOUBLE_EQ(mat1(0, 0), 58.0);
  EXPECT_DOUBLE_EQ(mat1(0, 1), 64.0);
  EXPECT_DOUBLE_EQ(mat1(1, 0), 139.0);
  EXPECT_DOUBLE_EQ(mat1(1, 1), 154.0);
}

// Unit test for MulMatrix function with invalid matrices
TEST(xMatrixTest, MulMatrixInvalid) {
  Matrix mat1(2, 3);
  Matrix mat2(3, 4);

  EXPECT_THROW(mat1.MulMatrix(mat2), std::invalid_argument);
}

// Unit test for MulMatrix function with a very large matrix
TEST(xMatrixTest, MulMatrixLargeMatrix) {
  constexpr size_t size = 500;

  Matrix mat1(size, size);
  Matrix mat2(size, size);

  for (int i = 0; i < size; i++) {
    for (int j = 0; j < size; j++) {
      mat1(i, j) = 1.0;
      mat2(i, j) = 2.0;
    }
  }

  mat1.MulMatrix(mat2);

  for (size_t i = 0; i < size; i++) {
    for (size_t j = 0; j < size; j++) {
      EXPECT_DOUBLE_EQ(mat1(i, j), 2.0 * size);
    }
  }
}

// Unit test for Transpose function with a square matrix
TEST(xMatrixTest, TransposeSquare) {
  Matrix mat1(3, 3);
  mat1(0, 0) = 1.0;
  mat1(0, 1) = 2.0;
  mat1(0, 2) = 3.0;
  mat1(1, 0) = 4.0;
  mat1(1, 1) = 5.0;
  mat1(1, 2) = 6.0;
  mat1(2, 0) = 7.0;
  mat1(2, 1) = 8.0;
  mat1(2, 2) = 9.0;

  Matrix result = mat1.Transpose();
  EXPECT_DOUBLE_EQ(result(0, 0), 1.0);
  EXPECT_DOUBLE_EQ(result(0, 1), 4.0);
  EXPECT_DOUBLE_EQ(result(0, 2), 7.0);
  EXPECT_DOUBLE_EQ(result(1, 0), 2.0);
  EXPECT_DOUBLE_EQ(result(1, 1), 5.0);
  EXPECT_DOUBLE_EQ(result(1, 2), 8.0);
  EXPECT_DOUBLE_EQ(result(2, 0), 3.0);
  EXPECT_DOUBLE_EQ(result(2, 1), 6.0);
  EXPECT_DOUBLE_EQ(result(2, 2), 9.0);
}

// Unit test for Transpose function with a rectangular matrix
TEST(xMatrixTest, TransposeRectangular) {
  Matrix mat1(2, 3);
  mat1(0, 0) = 1.0;
  mat1(0, 1) = 2.0;
  mat1(0, 2) = 3.0;
  mat1(1, 0) = 4.0;
  mat1(1, 1) = 5.0;
  mat1(1, 2) = 6.0;

  Matrix result = mat1.Transpose();

  EXPECT_DOUBLE_EQ(result(0, 0), 1.0);
  EXPECT_DOUBLE_EQ(result(0, 1), 4.0);
  EXPECT_DOUBLE_EQ(result(1, 0), 2.0);
  EXPECT_DOUBLE_EQ(result(1, 1), 5.0);
  EXPECT_DOUBLE_EQ(result(2, 0), 3.0);
  EXPECT_DOUBLE_EQ(result(2, 1), 6.0);
}

// Unit test for CalcComplements function with a 1x1 matrix
TEST(xMatrixTest, CalcComplements1x1) {
  Matrix mat1(1, 1);
  mat1(0, 0) = 3.0;

  Matrix result = mat1.CalcComplements();

  EXPECT_DOUBLE_EQ(result(0, 0), 1.0);
}

// Unit test for CalcComplements function with a 2x2 matrix
TEST(xMatrixTest, CalcComplements2x2) {
  Matrix mat1(2, 2);
  mat1(0, 0) = 1.0;
  mat1(0, 1) = 2.0;
  mat1(1, 0) = 3.0;
  mat1(1, 1) = 4.0;

  Matrix result = mat1.CalcComplements();

  EXPECT_DOUBLE_EQ(result(0, 0), 4.0);
  EXPECT_DOUBLE_EQ(result(0, 1), -3.0);
  EXPECT_DOUBLE_EQ(result(1, 0), -2.0);
  EXPECT_DOUBLE_EQ(result(1, 1), 1.0);
}

// Unit test for CalcComplements function with a 3x3 matrix
TEST(xMatrixTest, CalcComplements3x3) {
  Matrix mat1(3, 3);
  mat1(0, 0) = 1.0;
  mat1(0, 1) = 2.0;
  mat1(0, 2) = 3.0;
  mat1(1, 0) = 4.0;
  mat1(1, 1) = 5.0;
  mat1(1, 2) = 6.0;
  mat1(2, 0) = 7.0;
  mat1(2, 1) = 8.0;
  mat1(2, 2) = 9.0;

  Matrix result = mat1.CalcComplements();

  EXPECT_DOUBLE_EQ(result(0, 0), -3.0);
  EXPECT_DOUBLE_EQ(result(0, 1), 6.0);
  EXPECT_DOUBLE_EQ(result(0, 2), -3.0);
  EXPECT_DOUBLE_EQ(result(1, 0), 6.0);
  EXPECT_DOUBLE_EQ(result(1, 1), -12.0);
  EXPECT_DOUBLE_EQ(result(1, 2), 6.0);
  EXPECT_DOUBLE_EQ(result(2, 0), -3.0);
  EXPECT_DOUBLE_EQ(result(2, 1), 6.0);
  EXPECT_DOUBLE_EQ(result(2, 2), -3.0);
}

// Unit test for Determinant function with a 1x1 matrix
TEST(xMatrixTest, Determinant_1x1) {
  Matrix mat1(1, 1);
  mat1(0, 0) = 5.0;

  const double det = mat1.Determinant();

  EXPECT_DOUBLE_EQ(det, 5.0);
}

// Unit test for Determinant function with a 2x2 matrix
TEST(xMatrixTest, Determinant_2x2) {
  Matrix mat1(2, 2);
  mat1(0, 0) = 1.0;
  mat1(0, 1) = 2.0;
  mat1(1, 0) = 3.0;
  mat1(1, 1) = 4.0;

  const double det = mat1.Determinant();

  EXPECT_DOUBLE_EQ(det, -2.0);
}

// Unit test for Determinant function with a 3x3 matrix
TEST(xMatrixTest, Determinant_3x3) {
  Matrix mat1(3, 3);
  mat1(0, 0) = 1.0;
  mat1(0, 1) = 2.0;
  mat1(0, 2) = 3.0;
  mat1(1, 0) = 4.0;
  mat1(1, 1) = 5.0;
  mat1(1, 2) = 6.0;
  mat1(2, 0) = 7.0;
  mat1(2, 1) = 8.0;
  mat1(2, 2) = 9.0;

  const double det = mat1.Determinant();

  EXPECT_DOUBLE_EQ(det, 0.0);
}

// Unit test for Determinant function with a 4x4 matrix
TEST(xMatrixTest, Determinant_4x4) {
  Matrix mat1(4, 4);
  mat1(0, 0) = 1.0;
  mat1(0, 1) = 2.0;
  mat1(0, 2) = 3.0;
  mat1(0, 3) = 4.0;
  mat1(1, 0) = 5.0;
  mat1(1, 1) = 6.0;
  mat1(1, 2) = 7.0;
  mat1(1, 3) = 8.0;
  mat1(2, 0) = 9.0;
  mat1(2, 1) = 10.0;
  mat1(2, 2) = 11.0;
  mat1(2, 3) = 12.0;
  mat1(3, 0) = 13.0;
  mat1(3, 1) = 14.0;
  mat1(3, 2) = 15.0;
  mat1(3, 3) = 16.0;

  const double det = mat1.Determinant();

  EXPECT_DOUBLE_EQ(det, 0.0);
}

// Unit test for InverseMatrix function with a 1x1 matrix
TEST(xMatrixTest, InverseMatrix_1x1) {
  Matrix mat1(1, 1);
  mat1(0, 0) = 5.0;

  Matrix inv_mat = mat1.InverseMatrix();

  EXPECT_DOUBLE_EQ(inv_mat(0, 0), 0.2);
}

// Unit test for InverseMatrix function with a 2x2 matrix
TEST(xMatrixTest, InverseMatrix_2x2) {
  Matrix mat1(2, 2);
  mat1(0, 0) = 1.0;
  mat1(0, 1) = 2.0;
  mat1(1, 0) = 3.0;
  mat1(1, 1) = 4.0;

  Matrix inv_mat = mat1.InverseMatrix();

  EXPECT_DOUBLE_EQ(inv_mat(0, 0), -2.0);
  EXPECT_DOUBLE_EQ(inv_mat(0, 1), 1.0);
  EXPECT_DOUBLE_EQ(inv_mat(1, 0), 1.5);
  EXPECT_DOUBLE_EQ(inv_mat(1, 1), -0.5);
}

// Unit test for InverseMatrix function with a 3x3 matrix
TEST(xMatrixTest, InverseMatrix_3x3) {
  Matrix mat1(3, 3);
  mat1(0, 0) = 1.0;
  mat1(0, 1) = 2.0;
  mat1(0, 2) = 3.0;
  mat1(1, 0) = 4.0;
  mat1(1, 1) = 5.0;
  mat1(1, 2) = 6.0;
  mat1(2, 0) = 7.0;
  mat1(2, 1) = 8.0;
  mat1(2, 2) = 9.0;

  EXPECT_THROW(mat1.InverseMatrix(), std::invalid_argument);
}

// Unit test for InverseMatrix function with a singular matrix
TEST(xMatrixTest, InverseMatrix_Singular) {
  Matrix mat1(2, 2);
  mat1(0, 0) = 1.0;
  mat1(0, 1) = 2.0;
  mat1(1, 0) = 2.0;
  mat1(1, 1) = 4.0;

  EXPECT_THROW(mat1.InverseMatrix(), std::invalid_argument);
}

// Unit test for operator+ function
TEST(xMatrixTest, OperatorPlus) {
  Matrix mat1(2, 2);
  mat1(0, 0) = 1.0;
  mat1(0, 1) = 2.0;
  mat1(1, 0) = 3.0;
  mat1(1, 1) = 4.0;

  Matrix mat2(2, 2);
  mat2(0, 0) = 5.0;
  mat2(0, 1) = 6.0;
  mat2(1, 0) = 7.0;
  mat2(1, 1) = 8.0;

  Matrix result = mat1 + mat2;

  EXPECT_EQ(result(0, 0), 6.0);
  EXPECT_EQ(result(0, 1), 8.0);
  EXPECT_EQ(result(1, 0), 10.0);
  EXPECT_EQ(result(1, 1), 12.0);
}

// Unit test for operator-()
TEST(xMatrixTest, OperatorMinus) {
  Matrix mat1(2, 2);
  mat1(0, 0) = 1.0;
  mat1(0, 1) = 2.0;
  mat1(1, 0) = 3.0;
  mat1(1, 1) = 4.0;

  Matrix mat2(2, 2);
  mat2(0, 0) = 5.0;
  mat2(0, 1) = 6.0;
  mat2(1, 0) = 7.0;
  mat2(1, 1) = 8.0;

  Matrix result = mat2 - mat1;

  EXPECT_EQ(result(0, 0), 4.0);
  EXPECT_EQ(result(0, 1), 4.0);
  EXPECT_EQ(result(1, 0), 4.0);
  EXPECT_EQ(result(1, 1), 4.0);
}

// Unit test for operator* function
TEST(xMatrixTest, OperatorMultiply) {
  Matrix mat1(2, 2);
  mat1(0, 0) = 1.0;
  mat1(0, 1) = 2.0;
  mat1(1, 0) = 3.0;
  mat1(1, 1) = 4.0;

  Matrix mat2(2, 2);
  mat2(0, 0) = 5.0;
  mat2(0, 1) = 6.0;
  mat2(1, 0) = 7.0;
  mat2(1, 1) = 8.0;

  Matrix result = mat1 * mat2;

  EXPECT_EQ(result(0, 0), 19.0);
  EXPECT_EQ(result(0, 1), 22.0);
  EXPECT_EQ(result(1, 0), 43.0);
  EXPECT_EQ(result(1, 1), 50.0);
}

// Unit test for operator* function
TEST(xMatrixTest, OperatorMultiplyNum) {
  Matrix mat(2, 2);
  mat(0, 0) = 1.0;
  mat(0, 1) = 2.0;
  mat(1, 0) = 3.0;
  mat(1, 1) = 4.0;

  constexpr double val = 4;

  Matrix result = mat * val;

  EXPECT_EQ(result(0, 0), 4.0);
  EXPECT_EQ(result(0, 1), 8.0);
  EXPECT_EQ(result(1, 0), 12.0);
  EXPECT_EQ(result(1, 1), 16.0);
}

// Unit test for operator== function
TEST(xMatrixTest, OperatorEqual) {
  Matrix mat1(2, 2);
  mat1(0, 0) = 1.0;
  mat1(0, 1) = 2.0;
  mat1(1, 0) = 3.0;
  mat1(1, 1) = 4.0;

  Matrix mat2(2, 2);
  mat2(0, 0) = 1.0;
  mat2(0, 1) = 2.0;
  mat2(1, 0) = 3.0;
  mat2(1, 1) = 4.0;

  const bool result = mat1 == mat2;

  EXPECT_TRUE(result);
}

// Unit test for operator= function
TEST(xMatrixTest, OperatorAssignment) {
  Matrix mat1(2, 2);
  mat1(0, 0) = 1.0;
  mat1(0, 1) = 2.0;
  mat1(1, 0) = 3.0;
  mat1(1, 1) = 4.0;

  Matrix mat2(2, 2);
  mat2 = mat1;

  EXPECT_EQ(mat2(0, 0), 1.0);
  EXPECT_EQ(mat2(0, 1), 2.0);
  EXPECT_EQ(mat2(1, 0), 3.0);
  EXPECT_EQ(mat2(1, 1), 4.0);
}

// Unit test for operator+= function
TEST(xMatrixTest, OperatorPlusEqual) {
  Matrix mat1(2, 2);
  mat1(0, 0) = 1.0;
  mat1(0, 1) = 2.0;
  mat1(1, 0) = 3.0;
  mat1(1, 1) = 4.0;

  Matrix mat2(2, 2);
  mat2(0, 0) = 5.0;
  mat2(0, 1) = 6.0;
  mat2(1, 0) = 7.0;
  mat2(1, 1) = 8.0;

  mat1 += mat2;

  EXPECT_EQ(mat1(0, 0), 6.0);
  EXPECT_EQ(mat1(0, 1), 8.0);
  EXPECT_EQ(mat1(1, 0), 10.0);
  EXPECT_EQ(mat1(1, 1), 12.0);
}

// Unit test for operator-= function
TEST(xMatrixTest, OperatorMinusEqual) {
  Matrix mat1(2, 2);
  mat1(0, 0) = 1.0;
  mat1(0, 1) = 2.0;
  mat1(1, 0) = 3.0;
  mat1(1, 1) = 4.0;

  Matrix mat2(2, 2);
  mat2(0, 0) = 5.0;
  mat2(0, 1) = 6.0;
  mat2(1, 0) = 7.0;
  mat2(1, 1) = 8.0;

  mat1 -= mat2;

  EXPECT_EQ(mat1(0, 0), -4.0);
  EXPECT_EQ(mat1(0, 1), -4.0);
  EXPECT_EQ(mat1(1, 0), -4.0);
  EXPECT_EQ(mat1(1, 1), -4.0);
}
// Unit test for operator*= function
TEST(xMatrixTest, OperatorMultiplyEqualMatrix) {
  Matrix mat1(2, 2);
  mat1(0, 0) = 1.0;
  mat1(0, 1) = 2.0;
  mat1(1, 0) = 3.0;
  mat1(1, 1) = 4.0;

  Matrix mat2(2, 2);
  mat2(0, 0) = 5.0;
  mat2(0, 1) = 6.0;
  mat2(1, 0) = 7.0;
  mat2(1, 1) = 8.0;

  mat1 *= mat2;

  EXPECT_EQ(mat1(0, 0), 19.0);
  EXPECT_EQ(mat1(0, 1), 22.0);
  EXPECT_EQ(mat1(1, 0), 43.0);
  EXPECT_EQ(mat1(1, 1), 50.0);
}

// Unit test for operator*= function
TEST(xMatrixTest, OperatorMultiplyEqualNum) {
  Matrix mat(2, 2);
  mat(0, 0) = 1.0;
  mat(0, 1) = 2.0;
  mat(1, 0) = 3.0;
  mat(1, 1) = 4.0;

  mat *= 3;

  EXPECT_EQ(mat(0, 0), 3);
  EXPECT_EQ(mat(0, 1), 6);
  EXPECT_EQ(mat(1, 0), 9);
  EXPECT_EQ(mat(1, 1), 12);
}

// Unit test for operator() function
TEST(xMatrixTest, OperatorParentheses) {
  Matrix mat(2, 2);
  mat(0, 0) = 1.0;
  mat(0, 1) = 2.0;
  mat(1, 0) = 3.0;
  mat(1, 1) = 4.0;

  EXPECT_EQ(mat(0, 0), 1.0);
  EXPECT_EQ(mat(0, 1), 2.0);
  EXPECT_EQ(mat(1, 0), 3.0);
  EXPECT_EQ(mat(1, 1), 4.0);

  EXPECT_THROW(mat(-1, 0), std::invalid_argument);
  EXPECT_THROW(mat(0, -1), std::invalid_argument);
  EXPECT_THROW(mat(2, 0), std::invalid_argument);
  EXPECT_THROW(mat(0, 2), std::invalid_argument);
}

// Unit test for PrintMatrix function
TEST(xMatrixTest, PrintMatrix) {
  Matrix mat(2, 3);
  mat(0, 0) = 1.0;
  mat(0, 1) = 2.0;
  mat(0, 2) = 3.0;
  mat(1, 0) = 4.0;
  mat(1, 1) = 5.0;
  mat(1, 2) = 6.0;

  testing::internal::CaptureStdout();

  mat.PrintMatrix();
  const std::string output = testing::internal::GetCapturedStdout();

  EXPECT_EQ(output, "1 2 3 \n4 5 6 \n");
}

// Unit test for friend function
TEST(xMatrixTest, FriendOperatorMul) {
  Matrix mat(3, 3);
  mat(0, 0) = 1;
  mat(0, 1) = 2;
  mat(0, 2) = 3;
  mat(1, 0) = 4;
  mat(1, 1) = 5;
  mat(1, 2) = 6;
  mat(2, 0) = 7;
  mat(2, 1) = 8;
  mat(2, 2) = 9;

  constexpr double val = 2.5;

  Matrix result = val * mat;

  EXPECT_DOUBLE_EQ(result(0, 0), 2.5);
  EXPECT_DOUBLE_EQ(result(0, 1), 5);
  EXPECT_DOUBLE_EQ(result(0, 2), 7.5);
  EXPECT_DOUBLE_EQ(result(1, 0), 10);
  EXPECT_DOUBLE_EQ(result(1, 1), 12.5);
  EXPECT_DOUBLE_EQ(result(1, 2), 15);
  EXPECT_DOUBLE_EQ(result(2, 0), 17.5);
  EXPECT_DOUBLE_EQ(result(2, 1), 20);
  EXPECT_DOUBLE_EQ(result(2, 2), 22.5);
}

/////////////////////////////////
int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
/////////////////////////////////
