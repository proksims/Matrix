#include "s21_matrix.h"

// ========================== help ===========================
void s21_create_minor(matrix_t *A, int i, int j, matrix_t *minor) {
  int di = 0;
  int dj = 0;
  for (int ii = 0; ii < minor->rows; ii++) {
    if (ii == i) {
      di = 1;
    }
    dj = 0;

    for (int jj = 0; jj < minor->columns; jj++) {
      // вычеркиваем столбик
      if (jj == j) {
        dj = 1;
      }
      minor->matrix[ii][jj] = A->matrix[ii + di][jj + dj];
      // printf("%f ", minor->matrix[minor_i][minor_j]);
    }
  }
}

double s21_count_det(matrix_t *A, int size) {
  // printf("in count det\n");
  double determinant = 0;
  int k = 1;  //(-1) в степени i
  int n = size - 1;

  if (size == 1) {
    determinant = A->matrix[0][0];
  } else if (size == 2) {
    determinant = (A->matrix[0][0] * A->matrix[1][1]) -
                  (A->matrix[1][0] * A->matrix[0][1]);
  } else {
    matrix_t minor = {0};
    s21_create_matrix(n, n, &minor);

    for (int i = 0; i < size; i++) {
      s21_create_minor(A, i, 0, &minor);
      // s21_printf(&minor);
      determinant =
          determinant + k * A->matrix[i][0] * s21_count_det(&minor, n);
      k = -k;
    }
    s21_remove_matrix(&minor);
  }

  return determinant;
}

void s21_printf(matrix_t *result){
        // размер
        int rows = result->rows;
        int columns = result->columns;

        for(int i = 0; i < rows; i++){
            for (int j = 0; j < columns; j++){
                printf("%f ", result->matrix[i][j] );
            }
            printf("\n");
        }
    printf("\n");
}

// ====================================================================
int s21_create_matrix(int rows, int columns, matrix_t *result) {
  int res = 0;
  result->rows = 0;
  result->columns = 0;

  // проверяем размер
  if ((rows < 1) || (columns < 1)) {
    res = 1;
  } else {
    // записывем размер
    result->rows = rows;
    result->columns = columns;

    // создаем динамический массив
    result->matrix = (double **)calloc(rows, sizeof(double *));
    if (result->matrix == NULL) {
      res = 1;
    } else {
      for (int i = 0; i < rows; i++) {
        result->matrix[i] = (double *)calloc(columns, sizeof(double));
      }
    }
  }
  return res;
}

void s21_remove_matrix(matrix_t *A) {
  if (!(A && A->matrix && A->rows > 0 && A->columns > 0)) {
  } else {
    // освобождаем память
    for (int i = 0; i < A->rows; i++) {
      free(A->matrix[i]);
    }
    free(A->matrix);
  }

  A->matrix = NULL;
  // отчищаем структуру
  A->rows = 0;
  A->columns = 0;
}

int s21_eq_matrix(matrix_t *A, matrix_t *B) {
  int res = 0;

  // некорректная матрица A && B
  if (!(A && A->matrix && A->rows > 0 && A->columns > 0)) {
    res = 0;
  } else if (!(B && B->matrix && B->rows > 0 && B->columns > 0)) {
    res = 0;
  } else if ((A->rows == B->rows) && (A->columns == B->columns)) {
    res = 1;
    // совпадают размерности, проверяем числа
    for (int i = 0; i < A->rows; i++) {
      for (int j = 0; j < A->columns; j++) {
        if (fabs(A->matrix[i][j] - B->matrix[i][j]) > 0.00000001) {
          res = 0;
          break;
        }
      }
    }
  }
  return res;
}

int s21_sum_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  int res = 0;

  // // некорректная матрица A или В
  // if ( A->matrix == NULL || A == NULL || B == NULL || B->matrix == NULL ||
  // A->rows < 1 || A->columns < 1 || B->rows < 1 || B->columns < 1 ){
  //     res = 1;
  // }

  // некорректная матрица A && B
  if (!(A && A->matrix && A->rows > 0 && A->columns > 0)) {
    res = 1;
  } else if (!(B && B->matrix && B->rows > 0 && B->columns > 0)) {
    res = 1;
  } else if ((A->rows != B->rows) || (A->columns != B->columns)) {
    // printf("in size\n");
    res = 2;
  } else if (s21_create_matrix(A->rows, A->columns, result) == 1) {
    res = 1;
  } else {
    for (int i = 0; i < A->rows; i++) {
      for (int j = 0; j < A->columns; j++) {
        result->matrix[i][j] = A->matrix[i][j] + B->matrix[i][j];
      }
    }
  }

  return res;
}

int s21_sub_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  int res = 0;

  // некорректная матрица A && B
  if (!(A && A->matrix && A->rows > 0 && A->columns > 0)) {
    res = 1;
  } else if (!(B && B->matrix && B->rows > 0 && B->columns > 0)) {
    res = 1;
  } else if ((A->rows != B->rows) || (A->columns != B->columns)) {
    res = 2;
  } else if (s21_create_matrix(A->rows, A->columns, result) == 1) {
    res = 1;
  } else {
    for (int i = 0; i < A->rows; i++) {
      for (int j = 0; j < A->columns; j++) {
        result->matrix[i][j] = A->matrix[i][j] - B->matrix[i][j];
      }
    }
  }
  return res;
}

int s21_mult_number(matrix_t *A, double number, matrix_t *result) {
  int res = 0;

  // некорректная матрица A
  if (!(A && A->matrix && A->rows > 0 && A->columns > 0)) {
    res = 1;
  } else if (s21_create_matrix(A->rows, A->columns, result) == 1) {
    res = 1;
  } else {
    for (int i = 0; i < A->rows; i++) {
      for (int j = 0; j < A->columns; j++) {
        result->matrix[i][j] = A->matrix[i][j] * number;
      }
    }
  }
  return res;
}

int s21_mult_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  int res = 0;

  // некорректная матрица A && B
  if (!(A && A->matrix && A->rows > 0 && A->columns > 0)) {
    res = 1;
  } else if (!(B && B->matrix && B->rows > 0 && B->columns > 0)) {
    res = 1;
  } else if ((A->columns != B->rows)) {
    res = 2;
  } else if (s21_create_matrix(A->rows, B->columns, result) == 1) {
    res = 1;
  } else {
    for (int i = 0; i < A->rows; i++) {
      for (int j = 0; j < B->columns; j++) {
        for (int k = 0; k < A->columns; k++) {
          // формула: C(i,j) = A(i,1) × B(1,j) + A(i,2) × B(2,j) + … + A(i,k) ×
          // B(k,j).
          result->matrix[i][j] =
              result->matrix[i][j] + A->matrix[i][k] * B->matrix[k][j];
          // printf("i = %d, j = %d, k = %d\n", i, j, k);
          // printf("A = %f, B = %f, res = %f\n", A->matrix[i][k],
          // B->matrix[k][j], result->matrix[i][j]);
        }
      }
    }
  }
  return res;
}

int s21_transpose(matrix_t *A, matrix_t *result) {
  int res = 0;

  // некорректная матрица A
  if (!(A && A->matrix && A->rows > 0 && A->columns > 0)) {
    res = 1;
  } else if (s21_create_matrix(A->columns, A->rows, result) == 1) {
    res = 1;
  } else {
    for (int i = 0; i < A->rows; i++) {
      for (int j = 0; j < A->columns; j++) {
        result->matrix[j][i] = A->matrix[i][j];
      }
    }
  }
  return res;
}

int s21_determinant(matrix_t *A, double *result) {
  int res = 0;

  // некорректная матрица A
  if (!(A && A->matrix && A->rows > 0 && A->columns > 0)) {
    res = 1;
  } else if (A->rows != A->columns) {
    res = 2;
  } else {
    // printf("in det\n");
    *result = s21_count_det(A, A->rows);
  }
  return res;
}

int s21_calc_complements(matrix_t *A, matrix_t *result) {
  int res = 0;

  // некорректная матрица A
  if (!(A && A->matrix && A->rows > 0 && A->columns > 0)) {
    res = 1;
  } else if (A->rows != A->columns) {
    res = 2;
  } else if (s21_create_matrix(A->rows, A->columns, result) == 1) {
    res = 1;
  } else {
    int size = A->rows;
    double determinant = 0;
    if (size == 1) {
      determinant = A->matrix[0][0];
      result->matrix[0][0] = determinant;
    } else {
      for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
          matrix_t minor = {0};
          res = s21_create_matrix(size - 1, size - 1, &minor);
          if (res != 0) {
            break;
          }
          s21_create_minor(A, i, j, &minor);
          res = s21_determinant(&minor, &determinant);
          if (res != 0) {
            break;
          }
          // значение минора умножаем на -1^(i+j).
          result->matrix[i][j] = determinant * pow(-1, (i + j));
          s21_remove_matrix(&minor);
        }
      }
    }
  }
  return res;
}

int s21_inverse_matrix(matrix_t *A, matrix_t *result) {
  int res = 0;

  // некорректная матрица A
  if (!(A && A->matrix && A->rows > 0 && A->columns > 0)) {
    res = 1;
  } else if (A->rows != A->columns) {
    res = 2;
  } else if (s21_create_matrix(A->rows, A->columns, result) == 1) {
    res = 1;
  } else {
    double determinant = 0;
    s21_determinant(A, &determinant);

    // Определитель |A| == 0 -> обратная матрица не существует
    if (determinant == 0) {
      res = 2;
    } else {
      matrix_t calc_complements = {0};
      matrix_t trans = {0};
      res = s21_calc_complements(A, &calc_complements);
      res = res + s21_transpose(&calc_complements, &trans);
      // A^(-1) =   M^T * 1/|A|
      res = res + s21_mult_number(&trans, 1 / determinant, result);
      s21_remove_matrix(&calc_complements);
      s21_remove_matrix(&trans);

      // проверка на размер матрицы уже была, поэтому ошибка мемори
      if (res > 1) {
        res = 1;
      }
    }
  }
  return res;
}
