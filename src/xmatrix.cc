#include "xmatrix.h"

#include <cmath>
#include <fstream>
#include <iostream>

namespace xMatrix {
// CONSTRUCTORS & DESTRUCTORS
Matrix::Matrix() : rows_(3), cols_(3) { matrix_ = CreateMatrix(rows_, cols_); }

Matrix::Matrix(const int rows, const int cols) : rows_(rows), cols_(cols) {
  matrix_ = CreateMatrix(rows, cols);
}

Matrix::Matrix(const Matrix& o) : rows_(o.rows_), cols_(o.cols_) {
  matrix_ = CreateMatrix(o.rows_, o.cols_);

  if (!matrix_.empty()) {
    for (int i = 0; i < o.rows_; i++) {
      for (int j = 0; j < o.cols_; j++) {
        matrix_[i][j] = o.matrix_[i][j];
      }
    }
  } else {
    throw std::invalid_argument("The input matrix is incorrect size");
  }
}

Matrix::Matrix(Matrix&& o) noexcept : rows_(o.rows_), cols_(o.cols_) {
  matrix_ = o.matrix_;
  o.DeleteMatrix();
}

Matrix::~Matrix() { DeleteMatrix(); }

// ACCESSORS
int Matrix::GetRows() const { return rows_; }

int Matrix::GetCols() const { return cols_; }

// MUTATORS
void Matrix::SetRows(const int r) {
  if (r < 1) {
    throw std::invalid_argument("Rows must be a positive integer");
  }

  if (r == rows_) {
    return;
  }

  std::vector<std::vector<double>> new_matrix = CreateMatrix(r, cols_);
  for (int i = 0; i < std::min(r, rows_); i++) {
    for (int j = 0; j < cols_; j++) {
      new_matrix[i][j] = matrix_[i][j];
    }
  }

  this->DeleteMatrix();
  matrix_ = new_matrix;
  rows_ = r;
}

void Matrix::SetCols(const int c) {
  if (c < 1) {
    throw std::invalid_argument("Cols must be a positive integer");
  }

  if (c == cols_) {
    return;
  }

  std::vector<std::vector<double>> new_matrix = CreateMatrix(rows_, c);
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < std::min(c, cols_); j++) {
      new_matrix[i][j] = matrix_[i][j];
    }
  }

  this->DeleteMatrix();
  matrix_ = new_matrix;
  cols_ = c;
}

void Matrix::Resize(const int r, const int c) {
  if (r == rows_ && c == cols_) {
    return;
  }

  std::vector<std::vector<double>> new_matrix = CreateMatrix(r, c);

  if (!new_matrix.empty()) {
    for (int i = 0; i < std::min(r, rows_); i++) {
      for (int j = 0; j < std::min(c, cols_); j++) {
        new_matrix[i][j] = matrix_[i][j];
      }
    }
  }

  this->DeleteMatrix();
  matrix_ = new_matrix;
  rows_ = r;
  cols_ = c;
}

// MATRIX FUNCTIONS
bool Matrix::sEqMatrix(const Matrix& other) const {
  if (this->rows_ == other.rows_ && this->cols_ == other.cols_) {
    for (int i = 0; i < rows_; i++)
      for (int j = 0; j < cols_; j++)
        if (fabs(this->matrix_[i][j] - other.matrix_[i][j]) >= EPS)
          return false;
  } else {
    return false;
  }

  return true;
}

void Matrix::SumMatrix(const Matrix& other) {
  if (rows_ != other.rows_ || cols_ != other.cols_) {
    throw std::invalid_argument("Matrices are not of the same size");
  }

  for (int i = 0; i < rows_; i++)
    for (int j = 0; j < cols_; j++)
      matrix_[i][j] += other.matrix_[i][j];
}

void Matrix::SubMatrix(const Matrix& other) {
  if (rows_ != other.rows_ || cols_ != other.cols_) {
    throw std::invalid_argument("Matrices are not of the same size");
  }

  for (int i = 0; i < rows_; i++)
    for (int j = 0; j < cols_; j++)
      matrix_[i][j] -= other.matrix_[i][j];
}

void Matrix::MulNumber(const double num) {
  for (int i = 0; i < rows_; i++)
    for (int j = 0; j < cols_; j++)
      matrix_[i][j] *= num;
}

void Matrix::MulMatrix(const Matrix& other) {
  if (rows_ != other.cols_) {
    throw std::invalid_argument(
        "Num of cols in the first matrix must be equal the num of rows in the "
        "second matrix");
  }

  Matrix result(rows_, other.cols_);

  for (int i = 0; i < result.rows_; i++)
    for (int j = 0; j < result.cols_; j++)
      for (int f = 0; f < cols_; f++)
        result.matrix_[i][j] += matrix_[i][f] * other.matrix_[f][j];

  *this = result;
}

Matrix Matrix::Transpose() const {
  Matrix result(cols_, rows_);

  for (int i = 0; i < cols_; i++)
    for (int j = 0; j < rows_; j++)
      result.matrix_[i][j] = matrix_[j][i];

  return result;
}

Matrix Matrix::CalcComplements() const {
  Matrix result(rows_, cols_);

  if (this->rows_ == 1) {
    result.matrix_[0][0] = 1;
  } else {
    Matrix minor(rows_ - 1, cols_ - 1);

    for (int i = 0; i < rows_; i++) {
      for (int j = 0; j < cols_; j++) {
        MinorMatrix(&minor, i, j);
        double det = minor.Determinant();
        double sign = ((i + j) % 2 == 0) ? 1 : -1;
        result.matrix_[i][j] = sign * det;
      }
    }
  }

  return result;
}

void Matrix::MinorMatrix(Matrix* minor, const int using_row,
                         const int using_col) const {
  int i, j, k, l;

  for (i = 0, k = 0; k < minor->rows_; i++) {

    if (using_row == i) continue;

    for (j = 0, l = 0; l < minor->rows_; j++) {

      if (using_col == j) continue;

      minor->matrix_[k][l] = matrix_[i][j];
      l++;
    }

    k++;
  }
}

double Matrix::Determinant() const {
  double result = 0;

  if (rows_ < 1 || rows_ != cols_) {
    throw std::invalid_argument("Incorect size");
  }

  if (rows_ == 1) {
    result = matrix_[0][0];
  } else if (rows_ == 2) {
    result += matrix_[0][0] * matrix_[1][1];
    result += matrix_[0][1] * matrix_[1][0] * -1;
  } else {
    double temp_result = 0;
    char minus_flag = 1;
    Matrix minor(rows_ - 1, cols_ - 1);

    for (int i = 0; i < rows_; i++) {
      MinorMatrix(&minor, 0, i);
      temp_result = minor.Determinant();
      result += temp_result * minus_flag * matrix_[0][i];
      minus_flag = -minus_flag;
    }
  }

  return result;
}

Matrix Matrix::InverseMatrix() const {
  Matrix result(rows_, cols_);

  if (matrix_.empty() || rows_ < 1 || rows_ != cols_) {
    throw std::invalid_argument("Incorrect values.");
  }

  if (rows_ == 1) {
    result.matrix_[0][0] = 1 / matrix_[0][0];
  } else {
    double det = 0;
    det = this->Determinant();

    if (det != 0.0) {
      Matrix temp1(rows_, cols_);

      temp1 = this->CalcComplements();

      result = temp1.Transpose();
      result.MulNumber(1 / det);
    } else {
      throw std::invalid_argument("Determinant is equal to zero");
    }
  }

  return result;
}

// OVERLOAD FUNCTIONS
Matrix Matrix::operator+(const Matrix& other) const {
  Matrix result = other;
  result.SumMatrix(*this);
  return result;
}

Matrix Matrix::operator-(const Matrix& other) const {
  Matrix result = *this;
  result.SubMatrix(other);
  return result;
}

Matrix Matrix::operator*(const Matrix& other) const {
  Matrix result = *this;
  result.MulMatrix(other);
  return result;
}

Matrix Matrix::operator*(const double num) const {
  Matrix result = *this;
  result.MulNumber(num);
  return result;
}

bool Matrix::operator==(const Matrix& other) const {
  return this->sEqMatrix(other);
}

Matrix& Matrix::operator=(const Matrix& other) {
  this->Resize(other.rows_, other.cols_);

  for (int i = 0; i < other.rows_; i++)
    for (int j = 0; j < other.cols_; j++)
      matrix_[i][j] = other.matrix_[i][j];

  return *this;
}

Matrix& Matrix::operator+=(const Matrix& other) {
  this->SumMatrix(other);
  return *this;
}

Matrix& Matrix::operator-=(const Matrix& other) {
  this->SubMatrix(other);
  return *this;
}

Matrix& Matrix::operator*=(const Matrix& other) {
  this->MulMatrix(other);
  return *this;
}

Matrix& Matrix::operator*=(const double num) {
  this->MulNumber(num);
  return *this;
}

double& Matrix::operator()(const int r, const int c) {
  if (r >= rows_ || c >= cols_ || r < 0 || c < 0) {
    throw std::invalid_argument("Incorrect index");
  }

  return matrix_[r][c];
}

//  SUPPORT FUNCTION
std::vector<std::vector<double>> Matrix::CreateMatrix(const int r,
                                                      const int c) {
  std::vector<std::vector<double>> matrix;

  if (r < 1 || c < 1) {
    throw std::invalid_argument(
        "Input arguments must be positive and not equal to zero");
  }

  matrix.resize(r);

  for (int i = 0; i < r; i++)
    matrix[i].resize(c);

  return matrix;
}

void Matrix::DeleteMatrix() {
  if (matrix_.size() || !matrix_.empty()) {
    for (int i = 0; i < rows_; i++) matrix_[i].clear();

    matrix_.clear();
  }
}

void Matrix::PrintMatrix() const {
  for (int i = 0; i < rows_; ++i) {
    for (int j = 0; j < cols_; ++j) { std::cout << matrix_[i][j] << " "; }

    std::cout << std::endl;
  }
}

Matrix operator*(const double num, const Matrix& mat) {
  Matrix result = mat * num;
  return result;
}

void Matrix::LoadMatrixFromFile(const std::string& src) {
  std::ifstream file(src);

  if (!file.is_open()) {
    throw std::invalid_argument(
        "Something goes wrong, make sure that the file exist");
  }

  for (int i = 0; i < rows_; ++i) {
    for (int j = 0; j < cols_; ++j) {
      const char c = file.get();

      if (c == '0') {
        matrix_[i][j] = 0;
      } else if (c == '1') {
        matrix_[i][j] = 1;
      }
    }
  }
}

}  // namespace xMatrix