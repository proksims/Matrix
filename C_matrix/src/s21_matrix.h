#ifndef SRC_s21_MATRIX_H
#define SRC_s21_MATRIX_H

#include <math.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct matrix_struct {
  double **matrix;
  int rows;
  int columns;
} matrix_t;

// SUCCESS 1
// FAILURE 0
int s21_eq_matrix(matrix_t *A, matrix_t *B);

// 0 - OK
// 1 - Ошибка, некорректная матрица
// 2 - Ошибка вычисления
int s21_create_matrix(int rows, int columns, matrix_t *result);
void s21_remove_matrix(matrix_t *A);
int s21_sum_matrix(matrix_t *A, matrix_t *B, matrix_t *result);
int s21_sub_matrix(matrix_t *A, matrix_t *B, matrix_t *result);
int s21_mult_number(matrix_t *A, double number, matrix_t *result);
int s21_mult_matrix(matrix_t *A, matrix_t *B, matrix_t *result);
int s21_transpose(matrix_t *A, matrix_t *result);
int s21_calc_complements(matrix_t *A, matrix_t *result);
int s21_determinant(matrix_t *A, double *result);
int s21_inverse_matrix(matrix_t *A, matrix_t *result);

// ======================== help ===================================
void s21_create_minor(matrix_t *A, int i, int j, matrix_t *minor);
double s21_count_det(matrix_t *A, int size);
void s21_printf(matrix_t *result);

// полезные ссылки
// https://www.youtube.com/watch?v=MQBV3PMx5sg
// https://prog-cpp.ru/matrix-determinant/
// https://ru.onlinemschool.com/math/assistance/matrix/

#endif  // SRC_s21_MATRIX_H_