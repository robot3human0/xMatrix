#include "xmatrix.h"

// CONSTRUCTORS & DESTRUCTORS
xMatrix::xMatrix() : rows_(3), cols_(3) {
    matrix_ = CreateMatrix(rows_, cols_);
}

xMatrix::xMatrix(int rows, int cols) : rows_(rows), cols_(cols) {
    matrix_ = CreateMatrix(rows, cols);
}

xMatrix::xMatrix(const xMatrix& o) : rows_(o.rows_), cols_(o.cols_) {
    matrix_ = CreateMatrix(o.rows_, o.cols_);
    if (matrix_.size()) {
        for (int i = 0; i < o.rows_; i++) {
            for (int j = 0; j < o.cols_; j++) {
                matrix_[i][j] = o.matrix_[i][j];
            }
        }
    } else {
        throw std::invalid_argument("The input matrix is incorect size");
    }
}

xMatrix::xMatrix(xMatrix&& o) : rows_(o.rows_), cols_(o.cols_) {
    matrix_ = o.matrix_;
    o.DeleteMatrix();
}

xMatrix::~xMatrix() {
    DeleteMatrix();
}

// ACCESSORS
int xMatrix::GetRows() const { return rows_; }

int xMatrix::GetCols() const { return cols_; }

// MUTATORS
void xMatrix::SetRows(const int r) {
    if (r < 1) {
        throw std::invalid_argument("Rows must be a positive integer");
    } else if (r == rows_) {
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

void xMatrix::SetCols(const int c) {
    if (c < 1) {
        throw std::invalid_argument("Cols must be a positive integer");
    } else if (c == cols_) {
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

void xMatrix::Resize(const int r, const int c) {
    if (r == rows_ && c == cols_) {
        return;
    } else {
        std::vector<std::vector<double>> new_matrix = CreateMatrix(r, c);
        if (new_matrix.size()) {
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
}

// MATRIX FUNCTIONS
bool xMatrix::sEqMatrix(const xMatrix& other) const{
    if (this->rows_ == other.rows_ && this->cols_ == other.cols_) {
        for (int i = 0; i < rows_; i++) {
            for (int j = 0; j < cols_; j++) {
                if (fabs(this->matrix_[i][j] - other.matrix_[i][j]) >= EPS) {
                    return false;
                    break;
                }
            }
        }
    } else {
        return false;
    }
    return true;
}

void xMatrix::SumMatrix(const xMatrix& other) {
    if (rows_ != other.rows_ || cols_ != other.cols_) {
        throw std::invalid_argument("Matrices are not of the same size");
    } else {
        for (int i = 0; i < rows_; i++) {
            for (int j = 0; j < cols_; j++) {
                matrix_[i][j] += other.matrix_[i][j];
            }
        }
    }
}

void xMatrix::SubMatrix(const xMatrix& other) {
    if (rows_ != other.rows_ || cols_ != other.cols_) {
        throw std::invalid_argument("Matrices are not of the same size");
    } else {
        for (int i = 0; i < rows_; i++) {
            for (int j = 0; j < cols_; j++) {
                matrix_[i][j] -= other.matrix_[i][j];
            }
        }
    }
}

void xMatrix::MulNumber(const double num) {
    for (int i = 0; i < rows_; i++) {
        for (int j = 0; j < cols_; j++) {
            matrix_[i][j] *= num;
        }
    }
}

void xMatrix::MulMatrix(const xMatrix& other) {
    if (rows_ != other.cols_) {
        throw std::invalid_argument(
            "Num of cols in the first matrix must be equal the num of rows in the "
            "second matrix");
    }
    xMatrix result(rows_, other.cols_);
    for (int i = 0; i < result.rows_; i++) {
        for (int j = 0; j < result.cols_; j++) {
            for (int f = 0; f < cols_; f++) {
                result.matrix_[i][j] += matrix_[i][f] * other.matrix_[f][j];
            }
        }
    }
    *this = result;
}

xMatrix xMatrix::Transpose() const{
    xMatrix result(cols_, rows_);
    for (int i = 0; i < cols_; i++) {
        for (int j = 0; j < rows_; j++) {
            result.matrix_[i][j] = matrix_[j][i];
        }
    }
    return result;
}

xMatrix xMatrix::CalcComplements() const{
    xMatrix result(rows_, cols_);
    if (this->rows_ == 1) {
        result.matrix_[0][0] = 1;
    } else {
        xMatrix minor(rows_ - 1, cols_ - 1);
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

void xMatrix::MinorMatrix(xMatrix* minor, int using_row, int using_col) const{
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

double xMatrix::Determinant() const{
    double result = 0;
    if (rows_ < 1 || rows_ != cols_) {
        throw std::invalid_argument("Incorect size");
    } else {
        if (rows_ == 1) {
            result = matrix_[0][0];
        } else if (rows_ == 2) {
            result += matrix_[0][0] * matrix_[1][1];
            result += matrix_[0][1] * matrix_[1][0] * -1;
        } else {
            double temp_result = 0;
            char minus_flag = 1;
            xMatrix minor(rows_ - 1, cols_ - 1);
            for (int i = 0; i < rows_; i++) {
                MinorMatrix(&minor, 0, i);
                temp_result = minor.Determinant();
                result += temp_result * minus_flag * matrix_[0][i];
                minus_flag = -minus_flag;
            }
        }
    }
    return result;
}

xMatrix xMatrix::InverseMatrix() const{
    xMatrix result(rows_, cols_);
    if (matrix_.size() == 0 || rows_ < 1 || rows_ != cols_) {
        throw std::invalid_argument("Incorect values.");
    } else if (rows_ == 1) {
        result.matrix_[0][0] = 1 / matrix_[0][0];
    } else {
        double det = 0;
        det = this->Determinant();
        if (det != 0.0) {
            xMatrix temp1(rows_, cols_);
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
xMatrix xMatrix::operator+(const xMatrix& other) const{
    xMatrix result = other;
    result.SumMatrix(*this);
    return result;
}

xMatrix xMatrix::operator-(const xMatrix& other) const{
    xMatrix result = *this;
    result.SubMatrix(other);
    return result;
}

xMatrix xMatrix::operator*(const xMatrix& other) const{
    xMatrix result = *this;
    result.MulMatrix(other);
    return result;
}

xMatrix xMatrix::operator*(const double num) const{
    xMatrix result = *this;
    result.MulNumber(num);
    return result;
}



bool xMatrix::operator==(const xMatrix& other) {
    return this->sEqMatrix(other);
}

xMatrix& xMatrix::operator=(const xMatrix& other) {
    this->Resize(other.rows_, other.cols_);
    for (int i = 0; i < other.rows_; i++) {
        for (int j = 0; j < other.cols_; j++) {
            matrix_[i][j] = other.matrix_[i][j];
        }
    }
    return *this;
}

xMatrix& xMatrix::operator+=(const xMatrix& other) {
    this->SumMatrix(other);
    return *this;
}

xMatrix& xMatrix::operator-=(const xMatrix& other) {
    this->SubMatrix(other);
    return *this;
}

xMatrix& xMatrix::operator*=(const xMatrix& other) {
    this->MulMatrix(other);
    return *this;
}

xMatrix& xMatrix::operator*=(const double num) {
    this->MulNumber(num);
    return *this;
}

double& xMatrix::operator()(const int r, const int c) {
    if (r >= rows_ || c >= cols_ || r < 0 || c < 0) {
        throw std::invalid_argument("Incorect index");
    }
    return matrix_[r][c];
}

//  SUPPORT FUNCTION
std::vector<std::vector<double>> xMatrix::CreateMatrix(int r, int c) {
    std::vector<std::vector<double>> matrix;
    if (r < 1 || c < 1) {
        throw std::invalid_argument(
            "Input arguments must be positive and not equal to zero");
    } else {
        matrix.resize(r);
        for (int i = 0; i < r; i++) {
            matrix[i].resize(c);
        }
    }
    return matrix;
}

void xMatrix::DeleteMatrix() {
    if (matrix_.size() || !matrix_.empty()) {
        for (int i = 0; i < rows_; i++) {
            matrix_[i].clear();
        }
        matrix_.clear();
    }
}

void xMatrix::PrintMatrix() {
    for (int i = 0; i < rows_; ++i) {
        for (int j = 0; j < cols_; ++j) {
            std::cout << matrix_[i][j] << " ";
        }
        std::cout << std::endl;
    }
}

xMatrix operator*(const double num, const xMatrix& mat) {
    xMatrix result = mat * num;
    return result;
}

void xMatrix::LoadMatrixFromFile(const std::string &src) {
    std::ifstream openFile;
    openFile.open(src);
    char c;
    if (openFile.is_open()) {
        for (int i = 0; i < rows_; ++i) {
            for (int j = 0; j < cols_; ++j) {
                c = openFile.get();
                if (c == '0') {
                    matrix_[i][j] = 0;
                } else if (c == '1') {
                    matrix_[i][j] = 1;
                }
            }
        }
    } else {
        throw std::invalid_argument("Something goes wrong, make sure that the file exist");
        return;
    }
}