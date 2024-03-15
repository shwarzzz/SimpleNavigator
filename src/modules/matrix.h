#ifndef A2_SIMPLE_NAVIGATOR_SRC_MODULES_MAdoubleRIX_H_

#define A2_SIMPLE_NAVIGATOR_SRC_MODULES_MAdoubleRIX_H_

#include <cmath>
#include <cstring>
#include <iomanip>
#include <iostream>
#include <stdexcept>

namespace s21 {

class Matrix {
 public:
  Matrix() : rows_(0), cols_(0), matrix_(nullptr) {}

  Matrix(int rows, int cols);

  Matrix(const Matrix& other);

  Matrix(Matrix&& other) noexcept;

  Matrix& operator=(Matrix&& other) noexcept;

  Matrix& operator=(const Matrix& other);

  ~Matrix();

  int GetRows() const noexcept;

  int GetColumns() const noexcept;

  void SetRows(int row);

  void SetColumns(int column);

  double& operator()(int i, int j);

  const double& operator()(int i, int j) const;

  void Fill(double value);

  bool operator==(const Matrix& other) const noexcept;

  bool operator!=(const Matrix& other) const noexcept;

 private:
  void Free();

  int rows_;
  int cols_;
  double** matrix_;
};

std::ostream& operator<<(std::ostream& os, const Matrix& matrix);

}  // namespace s21
#endif