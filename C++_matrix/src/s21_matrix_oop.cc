#include "s21_matrix_oop.h"

// ========================= SOME METHODS ============================

S21Matrix::S21Matrix() {
  rows_ = 0;
  cols_ = 0;
  matrix_ = nullptr;
}

S21Matrix::S21Matrix(int rows, int cols) {
  rows_ = rows;
  cols_ = cols;
  if (rows_ < 1 || cols_ < 1) {
    throw std::out_of_range("Error");
  } else {
    CreateMatrix();
  }
}

S21Matrix::S21Matrix(const S21Matrix& other) {
  rows_ = other.rows_;
  cols_ = other.cols_;
  CreateMatrix();
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      matrix_[i][j] = other.matrix_[i][j];
    }
  }
}

// noexcept из функции не будет выброшено исключение
S21Matrix::S21Matrix(S21Matrix&& other) noexcept {
  rows_ = other.rows_;
  cols_ = other.cols_;
  matrix_ = other.matrix_;
  other.rows_ = 0;
  other.cols_ = 0;
  other.matrix_ = nullptr;
}

S21Matrix::~S21Matrix() {
  if (matrix_) {
    for (int i = 0; i < rows_; i++) {
      delete[] matrix_[i];
    }
    delete[] matrix_;
  }
  rows_ = 0;
  cols_ = 0;
  matrix_ = nullptr;
}

// ========================= SOME OPERATIONS =========================

bool S21Matrix::EqMatrix(const S21Matrix& other) noexcept {
  bool res = 0;
  if (!matrix_ || rows_ < 1 || cols_ < 1) {
    res = 0;
  } else if (!other.matrix_ || other.rows_ < 1 || other.cols_ < 1) {
    res = 0;
  } else if ((rows_ == other.rows_) && (cols_ == other.cols_)) {
    res = 1;
    // совпадают размерности, проверяем числа
    for (int i = 0; i < rows_; i++) {
      for (int j = 0; j < cols_; j++) {
        if (fabs(matrix_[i][j] - other.matrix_[i][j]) > 1e-6) {
          res = 0;
          break;
        }
      }
    }
  }
  return res;
}

void S21Matrix::SumMatrix(const S21Matrix& other) {
  int err = 0;
  if (!matrix_ || rows_ < 1 || cols_ < 1) {
    err = 1;
  } else if (!other.matrix_ || other.rows_ < 1 || other.cols_ < 1) {
    err = 1;
  } else if ((rows_ != other.rows_) || (cols_ != other.cols_)) {
    err = 1;
  }
  if (err != 0) {
    throw std::out_of_range("Error");
  }
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      matrix_[i][j] = matrix_[i][j] + other.matrix_[i][j];
    }
  }
}

void S21Matrix::SubMatrix(const S21Matrix& other) {
  int err = 0;
  if (!matrix_ || rows_ < 1 || cols_ < 1) {
    err = 1;
  } else if (!other.matrix_ || other.rows_ < 1 || other.cols_ < 1) {
    err = 1;
  } else if ((rows_ != other.rows_) || (cols_ != other.cols_)) {
    err = 1;
  }
  if (err != 0) {
    throw std::out_of_range("Error");
  }
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      matrix_[i][j] = matrix_[i][j] - other.matrix_[i][j];
    }
  }
}

void S21Matrix::MulNumber(const double num) {
  if (!matrix_ || rows_ < 1 || cols_ < 1) {
    throw std::out_of_range("Error");
  }
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      matrix_[i][j] = matrix_[i][j] * num;
    }
  }
}

void S21Matrix::MulMatrix(const S21Matrix& other) {
  int err = 0;
  if (!matrix_ || rows_ < 1 || cols_ < 1) {
    err = 1;
  } else if (!other.matrix_ || other.rows_ < 1 || other.cols_ < 1) {
    err = 1;
  } else if (cols_ != other.rows_) {
    err = 1;
  }
  if (err != 0) {
    throw std::out_of_range("Error");
  }
  S21Matrix res(rows_, other.cols_);
  for (int i = 0; i < res.rows_; i++) {
    for (int j = 0; j < res.cols_; j++) {
      res.matrix_[i][j] = 0;
      for (int k = 0; k < cols_; k++) {
        // формула: C(i,j) = A(i,1) × B(1,j) + A(i,2) × B(2,j) + … + A(i,k) ×
        // B(k,j).
        res.matrix_[i][j] =
            res.matrix_[i][j] + matrix_[i][k] * other.matrix_[k][j];
      }
    }
  }
  // *this = res;
  *this = std::move(res);
}

S21Matrix S21Matrix::Transpose() {
  if (!matrix_ || rows_ < 1 || cols_ < 1) {
    throw std::out_of_range("Error");
  }
  S21Matrix res(cols_, rows_);
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      res.matrix_[j][i] = matrix_[i][j];
    }
  }
  return res;
}

void S21Matrix::SetMinor(S21Matrix& a, int i, int j,
                         S21Matrix& minor) noexcept {
  int delete_i = 0;
  int delete_j = 0;
  for (int new_i = 0; new_i < minor.rows_; new_i++) {
    if (new_i == i) {
      delete_i = 1;
    }
    delete_j = 0;
    for (int new_j = 0; new_j < minor.cols_; new_j++) {
      // вычеркиваем столбик
      if (new_j == j) {
        delete_j = 1;
      }
      minor.matrix_[new_i][new_j] =
          a.matrix_[new_i + delete_i][new_j + delete_j];
    }
  }
}

double S21Matrix::Determinant() {
  if (!matrix_ || rows_ < 1 || cols_ < 1 || (rows_ != cols_)) {
    throw std::out_of_range("Error");
  }
  S21Matrix tmp = *this;
  double determinant = tmp.Gauss();
  return determinant;
}

double S21Matrix::Gauss() {
  double determinant = 1;
  double multiplier = 0;
  int size = rows_;
  int iMax = 0;

  for (int i = 0; i < size; i++) {
    iMax = i;
    for (int j = i + 1; j < size; j++) {
      if (std::fabs(matrix_[j][i]) > std::fabs(matrix_[iMax][i])) {
        iMax = j;
      }
    }
    if (std::fabs(matrix_[iMax][i]) < 1e-6) {
      continue;
    }
    std::swap(matrix_[i], matrix_[iMax]);
    if (i != iMax) {
      determinant *= -1;
    }

    for (int j = i + 1; j < size; j++) {
      multiplier = matrix_[j][i] / matrix_[i][i];
      for (int k = i; k < size; k++) {
        matrix_[j][k] -= matrix_[i][k] * multiplier;
      }
    }
  }
  //вычисляем определитель
  for (int i = 0; i < rows_; i++) {
    determinant *= matrix_[i][i];
  }
  return determinant;
}

S21Matrix S21Matrix::CalcComplements() {
  if (!matrix_ || rows_ < 1 || cols_ < 1 || (rows_ != cols_)) {
    throw std::out_of_range("Error");
  }
  S21Matrix res(rows_, cols_);
  int size = rows_;
  double determinant = 0;
  if (size == 1) {
    determinant = 1;
    res.matrix_[0][0] = determinant;
  } else {
    for (int i = 0; i < size; i++) {
      for (int j = 0; j < size; j++) {
        S21Matrix minor(size - 1, size - 1);
        SetMinor(*this, i, j, minor);
        determinant = minor.Determinant();
        // значение минора умножаем на -1^(i+j).
        res.matrix_[i][j] = determinant * pow(-1, (i + j));
      }
    }
  }
  return res;
}

S21Matrix S21Matrix::InverseMatrix() {
  if (!matrix_ || rows_ < 1 || cols_ < 1 || (rows_ != cols_)) {
    throw std::out_of_range("Error");
  }
  S21Matrix res(rows_, cols_);
  double determinant = Determinant();
  // Определитель |A| == 0 -> обратная матрица не существует
  if (fabs(determinant) < 1e-6) {
    throw std::out_of_range("Error");
  } else {
    if (rows_ == 1) {
      res.matrix_[0][0] = 1 / matrix_[0][0];
    } else {
      S21Matrix calc_complements = CalcComplements();
      res = calc_complements.Transpose();
      // A^(-1) =   M^T * 1/|A|
      res.MulNumber(1 / determinant);
    }
  }
  return res;
}

// ========================= SOME OPERATOR ============================

S21Matrix& S21Matrix::operator=(const S21Matrix& other) {
  if (this != &other) {
    // удаляем this, отчистка не будет двойной
    this->~S21Matrix();
    // создаем копию other
    S21Matrix res(other);
    rows_ = res.rows_;
    cols_ = res.cols_;
    matrix_ = res.matrix_;
    // не удаляем, тк используем в this, а просто стираем указатель
    res.rows_ = 0;
    res.cols_ = 0;
    res.matrix_ = nullptr;
  }
  return *this;
}

S21Matrix& S21Matrix::operator=(S21Matrix&& other) noexcept {
  if (this != &other) {
    // удаляем матрицу this отчистка не будет двойной
    this->~S21Matrix();
    rows_ = other.rows_;
    cols_ = other.cols_;
    matrix_ = other.matrix_;
    other.rows_ = 0;
    other.cols_ = 0;
    other.matrix_ = nullptr;
  }
  return *this;
}

bool S21Matrix::operator==(const S21Matrix& other) noexcept {
  return EqMatrix(other);
}

double& S21Matrix::operator()(int row, int col) {
  if (row >= rows_ || col >= cols_ || row < 0 || col < 0) {
    throw std::out_of_range("Error input, index is out of range");
  }
  return matrix_[row][col];
}

S21Matrix S21Matrix::operator+(const S21Matrix& other) {
  S21Matrix res = *this;
  res.SumMatrix(other);
  return res;
}
S21Matrix& S21Matrix::operator+=(const S21Matrix& other) {
  SumMatrix(other);
  return *this;
}

S21Matrix S21Matrix::operator-(const S21Matrix& other) {
  S21Matrix res = *this;
  res.SubMatrix(other);
  return res;
}
S21Matrix& S21Matrix::operator-=(const S21Matrix& other) {
  SubMatrix(other);
  return *this;
}

S21Matrix S21Matrix::operator*(const S21Matrix& other) {
  S21Matrix res = *this;
  res.MulMatrix(other);
  return res;
}
S21Matrix& S21Matrix::operator*=(const S21Matrix& other) {
  MulMatrix(other);
  return *this;
}

S21Matrix S21Matrix::operator*(const double num) {
  S21Matrix res = *this;
  res.MulNumber(num);
  return res;
}
S21Matrix& S21Matrix::operator*=(const double num) {
  MulNumber(num);
  return *this;
}

S21Matrix operator*(const double num, const S21Matrix& matrix) {
  S21Matrix res = matrix;
  res.MulNumber(num);
  return res;
}

// ======================== OTHER ================================
int S21Matrix::GetRows() noexcept { return rows_; }

int S21Matrix::GetCols() noexcept { return cols_; }

void S21Matrix::SetRows(int rows) {
  if (rows < 1) {
    throw std::out_of_range("Error");
  }
  if (rows != rows_) {
    S21Matrix res(rows, cols_);
    for (int i = 0; i < rows; i++) {
      for (int j = 0; j < cols_; j++) {
        if (i < rows_) {
          res.matrix_[i][j] = matrix_[i][j];
        } else {
          res.matrix_[i][j] = 0;
        }
      }
    }
    *this = res;
  }
}

void S21Matrix::SetCols(int cols) {
  if (cols < 1) {
    throw std::out_of_range("Error");
  }
  if (cols != cols_) {
    S21Matrix res(rows_, cols);
    for (int i = 0; i < rows_; i++) {
      for (int j = 0; j < cols; j++) {
        if (j < cols_) {
          res.matrix_[i][j] = matrix_[i][j];
        } else {
          res.matrix_[i][j] = 0;
        }
      }
    }
    *this = res;
  }
}

void S21Matrix::CreateMatrix() {
  if (rows_ > 0 && cols_ > 0) {
    try {
      matrix_ = new double*[rows_];
      int i = 0;
      try {
        for (i = 0; i < rows_; i++) {
          matrix_[i] = new double[cols_];
        }
      } catch (...) {
        for (; i >= 0; i--) {
          delete[] matrix_[i];
        }
        delete[] matrix_;
        throw std::out_of_range("Error");
      }
    } catch (...) {
      throw std::out_of_range("Error");
    }
    for (int i = 0; i < rows_; i++) {
      for (int j = 0; j < cols_; j++) {
        matrix_[i][j] = 0;
      }
    }
  } else {
    matrix_ = nullptr;
  }
}
