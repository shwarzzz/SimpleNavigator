#include "matrix.h"

namespace s21 {
Matrix::Matrix(int rows, int cols) : rows_(rows), cols_(cols) {
  if (rows_ < 0 || cols_ < 0) {
    throw std::length_error(
        "Error: The number of rows and columns must be greater than zero!");
  }
  matrix_ = new double*[rows_];
  for (int i = 0; i < rows_; i++) {
    try {
      matrix_[i] = new double[cols_]();
    } catch (...) {
      for (int j = 0; j < i; j++) {
        delete[] matrix_[i];
      }
      delete[] matrix_;
      throw;
    }
  }
}

Matrix::Matrix(const Matrix& other) : rows_(other.rows_), cols_(other.cols_) {
  matrix_ = new double*[rows_];
  for (int i = 0; i < rows_; i++) {
    try {
      matrix_[i] = new double[cols_]();
    } catch (...) {
      for (int j = 0; j < i; j++) {
        delete[] matrix_[i];
      }
      delete[] matrix_;
      throw;
    }
    std::memcpy(matrix_[i], other.matrix_[i], cols_ * sizeof(double));
  }
}

Matrix::Matrix(Matrix&& other) noexcept
    : rows_(other.rows_), cols_(other.cols_), matrix_(other.matrix_) {
  other.rows_ = 0;
  other.cols_ = 0;
  other.matrix_ = nullptr;
}

Matrix& Matrix::operator=(Matrix&& other) noexcept {
  if (this != &other) {
    Free();
    rows_ = other.rows_;
    cols_ = other.cols_;
    matrix_ = other.matrix_;
    other.rows_ = 0;
    other.cols_ = 0;
    other.matrix_ = nullptr;
  }
  return *this;
}

Matrix& Matrix::operator=(const Matrix& other) {
  if (this != &other) {
    Matrix tmp(other);
    *this = std::move(tmp);
  }
  return *this;
}

Matrix::~Matrix() {
  Free();
  cols_ = 0;
  rows_ = 0;
}

int Matrix::GetRows() const noexcept { return rows_; }

int Matrix::GetColumns() const noexcept { return cols_; }

void Matrix::SetRows(int row) {
  if (rows_ != row) {
    if (row < 0) {
      throw std::length_error("Error: Rows must be > 0");
    }
    double** new_matrix = new double*[row];
    for (int i = rows_; i < row; i++) {
      try {
        new_matrix[i] = new double[cols_]();
      } catch (...) {
        for (int j = rows_; j < i; j++) {
          delete[] new_matrix[j];
          delete[] new_matrix;
          throw;
        }
      }
    }
    for (int i = 0; i < rows_; i++) {
      if (i < row) {
        new_matrix[i] = matrix_[i];
      } else {
        delete[] matrix_[i];
      }
      matrix_[i] = nullptr;
    }
    delete[] matrix_;
    matrix_ = new_matrix;
    rows_ = row;
  }
}

void Matrix::SetColumns(int column) {
  if (cols_ != column) {
    Matrix newMatrix(rows_, column);
    for (int i = 0; i < rows_; i++) {
      for (int j = 0; j < column && j < cols_; j++) {
        newMatrix.matrix_[i][j] = matrix_[i][j];
      }
    }
    *this = std::move(newMatrix);
  }
}

double& Matrix::operator()(int i, int j) {
  if (i >= rows_ || j >= cols_ || i < 0 || j < 0) {
    throw std::out_of_range("Error: Index out of bounds");
  }
  return matrix_[i][j];
}

const double& Matrix::operator()(int i, int j) const {
  if (i >= rows_ || j >= cols_ || i < 0 || j < 0) {
    throw std::out_of_range("Error: Index out of bounds");
  }
  return matrix_[i][j];
}

bool Matrix::operator==(const Matrix& other) const noexcept {
  if (rows_ != other.rows_ || cols_ != other.cols_) {
    return false;
  }
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      if (matrix_[i][j] - other.matrix_[i][j] > 1e-7) {
        return false;
      }
    }
  }
  return true;
}

bool Matrix::operator!=(const Matrix& other) const noexcept {
  return !(*this == other);
}

std::ostream& operator<<(std::ostream& os, const Matrix& matrix) {
  for (int i = 0; i < matrix.GetRows(); i++) {
    for (int j = 0; j < matrix.GetColumns(); j++) {
      os << std::setw(4) << matrix(i, j);
      os << " ";
    }
    os << "\n";
  }
  return os;
}

void Matrix::Free() {
  for (int i = 0; i < rows_; i++) {
    delete[] matrix_[i];
    matrix_[i] = nullptr;
  }
  delete[] matrix_;
  matrix_ = nullptr;
}

void Matrix::Fill(double value) {
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      matrix_[i][j] = value;
    }
  }
}
}  // namespace s21