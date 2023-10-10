#ifndef XMATRIX_H
#define XMATRIX_H

#include <cmath>
#include <vector>
#include <iostream>

const double EPS = 1e-8;

class xMatrix {
public:
    xMatrix();
    xMatrix(int rows, int cols);
    xMatrix(const xMatrix& o);
    xMatrix(xMatrix&& o);
    ~xMatrix();

    int GetRows() const;
    int GetCols() const;

    void SetRows(const int r);
    void SetCols(const int c);
    void Resize(const int r, const int c);

    bool sEqMatrix(const xMatrix& other) const;
    void SumMatrix(const xMatrix& other);
    void SubMatrix(const xMatrix& other);
    void MulNumber(const double num);
    void MulMatrix(const xMatrix& other);
    xMatrix Transpose() const;
    xMatrix CalcComplements() const;
    double Determinant() const;
    xMatrix InverseMatrix() const;

    xMatrix operator-(const xMatrix& other) const;
    xMatrix operator+(const xMatrix& other) const;
    xMatrix operator*(const xMatrix& other) const;
    xMatrix operator*(const double num) const;
    friend xMatrix operator*(const double num, const xMatrix& mat);
    bool operator==(const xMatrix& other);
    xMatrix& operator=(const xMatrix& other);
    xMatrix& operator+=(const xMatrix& other);
    xMatrix& operator-=(const xMatrix& other);
    xMatrix& operator*=(const xMatrix& other);
    xMatrix& operator*=(const double num);
    double& operator()(const int r, const int c);
    
    void PrintMatrix();

private:
    int rows_, cols_;
    std::vector<std::vector<double>> matrix_;
    std::vector<std::vector<double>> CreateMatrix(int r, int c);
    void DeleteMatrix();
    void MinorMatrix(xMatrix* minor, int using_row, int using_col) const;
};

#endif  // XMATRIX_H
