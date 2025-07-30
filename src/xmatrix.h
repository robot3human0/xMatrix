#ifndef XMATRIX_H
#define XMATRIX_H

#include <string>
#include <vector>

namespace xMatrix {

constexpr double EPS = 1e-8;

class Matrix {
 public:
  Matrix();
  Matrix(int rows, int cols);
  Matrix(const Matrix& o);
  Matrix(Matrix&& o) noexcept;
  ~Matrix();

  [[nodiscard]] int GetRows() const;
  [[nodiscard]] int GetCols() const;

  void SetRows(int r);
  void SetCols(int c);
  void Resize(int r, int c);

  [[nodiscard]] bool sEqMatrix(const Matrix& other) const;
  void SumMatrix(const Matrix& other);
  void SubMatrix(const Matrix& other);
  void MulNumber(double num);
  void MulMatrix(const Matrix& other);
  void LoadMatrixFromFile(const std::string& src);
  [[nodiscard]] Matrix Transpose() const;
  [[nodiscard]] Matrix CalcComplements() const;
  [[nodiscard]] double Determinant() const;
  [[nodiscard]] Matrix InverseMatrix() const;

  Matrix operator-(const Matrix& other) const;
  Matrix operator+(const Matrix& other) const;
  Matrix operator*(const Matrix& other) const;
  Matrix operator*(double num) const;
  friend Matrix operator*(double num, const Matrix& mat);
  bool operator==(const Matrix& other) const;
  Matrix& operator=(const Matrix& other);
  Matrix& operator+=(const Matrix& other);
  Matrix& operator-=(const Matrix& other);
  Matrix& operator*=(const Matrix& other);
  Matrix& operator*=(double num);
  double& operator()(int r, int c);

  void PrintMatrix() const;

 private:
  int rows_, cols_;
  std::vector<std::vector<double>> matrix_;
  std::vector<std::vector<double>> CreateMatrix(int r, int c);
  void DeleteMatrix();
  void MinorMatrix(Matrix* minor, int using_row, int using_col) const;
};

}  // namespace xMatrix
#endif  // XMATRIX_H
