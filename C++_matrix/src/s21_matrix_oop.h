#ifndef __S21_MATRIX_OOP_H__
#define __S21_MATRIX_OOP_H__

#include <cmath>
#include <iostream>

class S21Matrix {
 public:
  // some methods
  S21Matrix();                            // constructor
  S21Matrix(int rows, int cols);          // parameterized constructor
  S21Matrix(const S21Matrix &other);      // copy cnstructor
  S21Matrix(S21Matrix &&other) noexcept;  // move cnstructor
  // add operator= for google style
  S21Matrix &operator=(const S21Matrix &other);      // copy
  S21Matrix &operator=(S21Matrix &&other) noexcept;  // move
  ~S21Matrix();                                      // destructor

  // some operations
  bool EqMatrix(const S21Matrix &other) noexcept;
  void SumMatrix(const S21Matrix &other);
  void SubMatrix(const S21Matrix &other);
  void MulNumber(const double num);
  void MulMatrix(const S21Matrix &other);
  S21Matrix Transpose();
  S21Matrix CalcComplements();
  double Determinant();
  S21Matrix InverseMatrix();

  // some operators
  bool operator==(const S21Matrix &other) noexcept;
  S21Matrix operator+(const S21Matrix &other);
  S21Matrix operator-(const S21Matrix &other);
  S21Matrix operator*(const S21Matrix &other);
  S21Matrix operator*(const double num);
  S21Matrix &operator+=(const S21Matrix &other);
  S21Matrix &operator-=(const S21Matrix &other);
  S21Matrix &operator*=(const S21Matrix &other);
  S21Matrix &operator*=(const double num);
  double &operator()(int row, int col);
  friend S21Matrix operator*(const double num, const S21Matrix &matrix);

  // Аксессор — функция, используемая для извлечения
  int GetRows() noexcept;
  int GetCols() noexcept;
  // Мутаторы — функция, используемая для редактирования
  void SetRows(int rows);
  void SetCols(int cols);

 private:
  int rows_, cols_;
  double **matrix_;
  void CreateMatrix();
  void SetMinor(S21Matrix &a, int i, int j, S21Matrix &minor) noexcept;
  double Gauss();
};

// cсылки
// https://learn.microsoft.com/ru-ru/cpp/cpp/move-constructors-and-move-assignment-operators-cpp?view=msvc-170
// https://ru.onlinemschool.com/math/assistance/matrix/
// https://qna.habr.com/q/160463
// https://drapegnik.github.io/bsu/numerical-analysis/sem3/lab1/lab1.pdf
// http://hardfire.ru/gauss

#endif  //  S21_MATRIX_OOP_H__
