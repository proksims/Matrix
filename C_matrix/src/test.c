#include <check.h>

#include "s21_matrix.h"

void s21_fill(matrix_t *A, double x) {
  for (int i = 0; i < A->rows; i++) {
    for (int j = 0; j < A->columns; j++) {
      A->matrix[i][j] = x;
    }
  }
}

void s21_full_matrix(matrix_t *A) {
  double num = 1;
  for (int i = 0; i < A->rows; i++) {
    for (int j = 0; j < A->columns; j++, num++) {
      A->matrix[i][j] = num;
    }
  }
}

void s21_full_matrix_rev(matrix_t *A) {
  double num = 100;
  for (int i = 0; i < A->rows; i++) {
    for (int j = 0; j < A->columns; j++, num--) {
      A->matrix[i][j] = num;
    }
  }
}

START_TEST(create_matrix_1) {
  int code = 0;
  matrix_t A = {0};
  code = s21_create_matrix(1, 1, &A);
  ck_assert_int_eq(code, 0);
  s21_remove_matrix(&A);
}
END_TEST

START_TEST(s21_sum_matrix_test_1) {
  matrix_t result;
  matrix_t result1;
  matrix_t result2;
  matrix_t result3;
  s21_create_matrix(4, 4, &result1);
  s21_create_matrix(4, 4, &result2);
  s21_fill(&result1, 3);
  s21_fill(&result2, 4);
  s21_create_matrix(4, 4, &result);
  s21_fill(&result, 7);
  s21_sum_matrix(&result1, &result2, &result3);
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      ck_assert_double_eq(result.matrix[i][j], result3.matrix[i][j]);
    }
  }
  s21_remove_matrix(&result1);
  s21_remove_matrix(&result2);
  s21_remove_matrix(&result3);
  s21_remove_matrix(&result);
}
END_TEST

START_TEST(s21_sum_matrix_test_2) {
  matrix_t result;
  matrix_t result1;
  matrix_t result2;
  matrix_t result3;
  s21_create_matrix(2, 2, &result1);
  s21_create_matrix(4, 4, &result2);
  int expected_result = s21_create_matrix(2, 2, &result3);
  int actual_result = s21_sum_matrix(&result1, &result2, &result);
  ck_assert_int_ne(expected_result, actual_result);
  s21_remove_matrix(&result1);
  s21_remove_matrix(&result2);
  s21_remove_matrix(&result3);
}
END_TEST

START_TEST(s21_sum_matrix_test_3) {
  matrix_t result;
  matrix_t result1;
  matrix_t result2;
  matrix_t result3;
  s21_create_matrix(4, 4, &result1);
  s21_create_matrix(4, 4, &result2);
  s21_fill(&result1, 0);
  result2.matrix[0][0] = 1;
  result2.matrix[1][1] = 1;
  result2.matrix[2][2] = 1;
  result2.matrix[3][3] = 1;
  int expected_result = s21_create_matrix(4, 4, &result3);
  result3.matrix[0][0] = 1;
  result3.matrix[1][1] = 1;
  result3.matrix[2][2] = 1;
  result3.matrix[3][3] = 1;
  int actual_result = s21_sum_matrix(&result1, &result2, &result);
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      ck_assert_double_eq(result3.matrix[i][j], result.matrix[i][j]);
    }
  }
  ck_assert_uint_eq(expected_result, actual_result);
  s21_remove_matrix(&result1);
  s21_remove_matrix(&result2);
  s21_remove_matrix(&result3);
  s21_remove_matrix(&result);
}
END_TEST

START_TEST(s21_sum_matrix_test_4) {
  matrix_t temp;
  matrix_t temp2;
  matrix_t result;
  matrix_t result_defolt;
  s21_create_matrix(3, 3, &temp);
  s21_create_matrix(3, 3, &temp2);
  s21_create_matrix(3, 3, &result_defolt);
  s21_full_matrix(&temp);
  s21_full_matrix_rev(&temp2);
  for (int i = 0; (i < temp.rows); i++) {
    for (int j = 0; j < temp.columns; j++) {
      result_defolt.matrix[i][j] = temp.matrix[i][j] + temp2.matrix[i][j];
    }
  }
  ck_assert_int_eq(s21_sum_matrix(&temp, &temp2, &result), 0);
  ck_assert_int_eq(s21_eq_matrix(&result_defolt, &result), 1);
  s21_remove_matrix(&temp);
  s21_remove_matrix(&temp2);
  s21_remove_matrix(&result);
  s21_remove_matrix(&result_defolt);
}
END_TEST

START_TEST(s21_sum_matrix_test_5) {
  matrix_t temp;
  matrix_t temp2;
  matrix_t result;
  s21_create_matrix(3, 3, &temp);
  s21_create_matrix(3, 3, &temp2);
  s21_full_matrix(&temp);
  s21_full_matrix(&temp2);
  ck_assert_int_eq(s21_sum_matrix(&temp, &temp2, &result), 0);
  s21_remove_matrix(&temp);
  s21_remove_matrix(&temp2);
  s21_remove_matrix(&result);
}
END_TEST

START_TEST(s21_sub_matrix_test_1) {
  matrix_t result;
  matrix_t result1;
  matrix_t result2;
  matrix_t result3;
  s21_create_matrix(4, 4, &result1);
  s21_create_matrix(4, 4, &result2);
  s21_fill(&result1, 4);
  s21_fill(&result2, 3);
  s21_create_matrix(4, 4, &result);
  s21_fill(&result, 1);
  int sum_m = s21_sub_matrix(&result1, &result2, &result3);
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      ck_assert_double_eq(result.matrix[i][j], result3.matrix[i][j]);
    }
  }
  ck_assert_uint_eq(sum_m, 0);
  s21_remove_matrix(&result1);
  s21_remove_matrix(&result2);
  s21_remove_matrix(&result3);
  s21_remove_matrix(&result);
}
END_TEST

START_TEST(s21_sub_matrix_test_2) {
  matrix_t result;
  matrix_t result1;
  matrix_t result2;
  matrix_t result3;
  s21_create_matrix(2, 2, &result1);
  s21_create_matrix(4, 4, &result2);
  int expected_result = s21_create_matrix(2, 2, &result3);
  int actual_result = s21_sum_matrix(&result1, &result2, &result);
  ck_assert_int_ne(expected_result, actual_result);
  s21_remove_matrix(&result1);
  s21_remove_matrix(&result2);
  s21_remove_matrix(&result3);
}
END_TEST

START_TEST(s21_sub_matrix_test_3) {
  matrix_t result;
  matrix_t result1;
  matrix_t result2;
  matrix_t result3;
  s21_create_matrix(4, 4, &result1);
  s21_create_matrix(4, 4, &result2);
  s21_fill(&result2, 0);
  result1.matrix[0][0] = 1;
  result1.matrix[1][1] = 1;
  result1.matrix[2][2] = 1;
  result1.matrix[3][3] = 1;
  int expected_result = s21_create_matrix(4, 4, &result3);
  result3.matrix[0][0] = 1;
  result3.matrix[1][1] = 1;
  result3.matrix[2][2] = 1;
  result3.matrix[3][3] = 1;
  int actual_result = s21_sub_matrix(&result1, &result2, &result);
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      ck_assert_double_eq(result3.matrix[i][j], result.matrix[i][j]);
    }
  }
  ck_assert_uint_eq(expected_result, actual_result);
  s21_remove_matrix(&result1);
  s21_remove_matrix(&result2);
  s21_remove_matrix(&result3);
  s21_remove_matrix(&result);
}
END_TEST

START_TEST(s21_sub_matrix_test_4) {
  matrix_t temp;
  matrix_t temp2;
  matrix_t result;
  matrix_t result_defolt;
  s21_create_matrix(3, 3, &temp);
  s21_create_matrix(3, 3, &temp2);
  s21_create_matrix(3, 3, &result_defolt);
  s21_full_matrix(&temp);
  s21_full_matrix_rev(&temp2);
  for (int i = 0; (i < temp.rows); i++) {
    for (int j = 0; j < temp.columns; j++) {
      result_defolt.matrix[i][j] = temp.matrix[i][j] - temp2.matrix[i][j];
    }
  }
  ck_assert_int_eq(s21_sub_matrix(&temp, &temp2, &result), 0);
  ck_assert_int_eq(s21_eq_matrix(&result_defolt, &result), 1);
  s21_remove_matrix(&temp);
  s21_remove_matrix(&temp2);
  s21_remove_matrix(&result);
  s21_remove_matrix(&result_defolt);
}
END_TEST

START_TEST(s21_sub_matrix_test_5) {
  matrix_t temp;
  matrix_t temp2;
  matrix_t result;
  s21_create_matrix(3, 3, &temp);
  s21_create_matrix(3, 3, &temp2);
  s21_full_matrix(&temp);
  s21_full_matrix(&temp2);
  ck_assert_int_eq(s21_sub_matrix(&temp, &temp2, &result), 0);
  s21_remove_matrix(&temp);
  s21_remove_matrix(&temp2);
  s21_remove_matrix(&result);
}
END_TEST

START_TEST(s21_sub_matrix_test_6) {
  matrix_t result;
  matrix_t result1;
  matrix_t result2;
  matrix_t result3;
  s21_create_matrix(2, 2, &result1);
  s21_create_matrix(4, 4, &result2);
  int expected_result = s21_create_matrix(2, 2, &result3);
  int actual_result = s21_sub_matrix(&result1, &result2, &result);
  ck_assert_int_ne(expected_result, actual_result);
  s21_remove_matrix(&result1);
  s21_remove_matrix(&result2);
  s21_remove_matrix(&result3);
}
END_TEST

START_TEST(s21_eq_matrix_1) {
  matrix_t temp;
  matrix_t temp2;
  matrix_t temp3;
  s21_create_matrix(3, 3, &temp);
  s21_create_matrix(3, 3, &temp2);
  s21_create_matrix(3, 3, &temp3);
  s21_full_matrix(&temp);
  s21_full_matrix(&temp2);
  ck_assert_int_eq(s21_eq_matrix(&temp, &temp2), 1);
  ck_assert_int_eq(s21_eq_matrix(&temp, &temp3), 0);
  s21_remove_matrix(&temp);
  s21_remove_matrix(&temp2);
  s21_remove_matrix(&temp3);
}
END_TEST

START_TEST(s21_eq_matrix_2) {
  matrix_t temp;
  matrix_t temp2;
  s21_create_matrix(3, 3, &temp);
  s21_create_matrix(3, 3, &temp2);
  s21_full_matrix(&temp);
  s21_full_matrix(&temp2);
  temp2.matrix[1][1] = 0;
  temp2.matrix[1][2] = 77;
  ck_assert_int_eq(s21_eq_matrix(&temp, &temp2), 0);
  s21_remove_matrix(&temp);
  s21_remove_matrix(&temp2);
}
END_TEST

START_TEST(s21_eq_matrix_3) {
  matrix_t temp;
  matrix_t temp2;
  s21_create_matrix(3, 3, &temp);
  s21_create_matrix(2, 3, &temp2);
  s21_full_matrix(&temp);
  s21_full_matrix(&temp2);
  ck_assert_int_eq(s21_eq_matrix(&temp, &temp2), 0);
  s21_remove_matrix(&temp);
  s21_remove_matrix(&temp2);
}
END_TEST

START_TEST(s21_eq_matrix_4) {
  matrix_t temp;
  matrix_t temp2;
  s21_create_matrix(3, 3, &temp);
  s21_create_matrix(3, 21, &temp2);
  s21_full_matrix(&temp);
  s21_full_matrix(&temp2);
  ck_assert_int_eq(s21_eq_matrix(&temp, &temp2), 0);
  s21_remove_matrix(&temp);
  s21_remove_matrix(&temp2);
}
END_TEST

START_TEST(s21_eq_matrix_5) {
  matrix_t temp;
  matrix_t temp2;
  s21_create_matrix(3, 3, &temp);
  s21_create_matrix(3, 3, &temp2);
  s21_full_matrix(&temp);
  s21_full_matrix(&temp2);
  temp.matrix[0][1] = 4.67773;
  temp2.matrix[0][1] = 4.67774;
  ck_assert_int_eq(s21_eq_matrix(&temp, &temp2), 0);
  s21_remove_matrix(&temp);
  s21_remove_matrix(&temp2);
}
END_TEST

START_TEST(s21_eq_matrix_6) {
  matrix_t result1;
  matrix_t result2;
  s21_create_matrix(41, 41, &result1);
  s21_create_matrix(41, 41, &result2);
  s21_fill(&result1, 1);
  s21_fill(&result2, 1);
  int expected_result = 1;
  int actual_result = s21_eq_matrix(&result1, &result2);
  ck_assert_uint_eq(expected_result, actual_result);
  s21_remove_matrix(&result1);
  s21_remove_matrix(&result2);
}
END_TEST

START_TEST(s21_eq_matrix_7) {
  matrix_t result1;
  matrix_t result2;
  s21_create_matrix(83, 83, &result1);
  s21_create_matrix(83, 83, &result2);
  s21_fill(&result1, 7);
  s21_fill(&result2, 9);
  int expected_result = 0;
  int actual_result = s21_eq_matrix(&result1, &result2);
  ck_assert_uint_eq(expected_result, actual_result);
  s21_remove_matrix(&result1);
  s21_remove_matrix(&result2);
}
END_TEST

START_TEST(s21_eq_matrix_8) {
  matrix_t result1;
  matrix_t result2;
  s21_create_matrix(32, 32, &result1);
  s21_create_matrix(27, 27, &result2);
  s21_fill(&result1, 42);
  s21_fill(&result2, 42);
  int expected_result = 0;
  int actual_result = s21_eq_matrix(&result1, &result2);
  ck_assert_uint_eq(expected_result, actual_result);
  s21_remove_matrix(&result1);
  s21_remove_matrix(&result2);
}
END_TEST

START_TEST(s21_eq_matrix_9) {
  matrix_t result1;
  matrix_t result2;
  s21_create_matrix(22, 22, &result1);
  s21_create_matrix(22, 22, &result2);
  s21_fill(&result1, 13);
  s21_fill(&result2, 12);
  int expected_result = 0;
  int actual_result = s21_eq_matrix(&result1, &result2);
  ck_assert_uint_eq(expected_result, actual_result);
  s21_remove_matrix(&result1);
  s21_remove_matrix(&result2);
}
END_TEST

START_TEST(s21_mult_matrix_1) {
  matrix_t temp;
  matrix_t temp2;
  matrix_t result;
  matrix_t result_defolt;
  s21_create_matrix(3, 2, &temp);
  s21_create_matrix(2, 3, &temp2);
  s21_create_matrix(3, 3, &result_defolt);
  s21_full_matrix(&temp);
  s21_full_matrix(&temp2);
  result_defolt.matrix[0][0] = 9;
  result_defolt.matrix[0][1] = 12;
  result_defolt.matrix[0][2] = 15;
  result_defolt.matrix[1][0] = 19;
  result_defolt.matrix[1][1] = 26;
  result_defolt.matrix[1][2] = 33;
  result_defolt.matrix[2][0] = 29;
  result_defolt.matrix[2][1] = 40;
  result_defolt.matrix[2][2] = 51;
  ck_assert_int_eq(s21_mult_matrix(&temp, &temp2, &result), 0);
  ck_assert_int_eq(s21_eq_matrix(&result_defolt, &result), 1);
  s21_remove_matrix(&temp);
  s21_remove_matrix(&temp2);
  s21_remove_matrix(&result);
  s21_remove_matrix(&result_defolt);
}
END_TEST

START_TEST(s21_mult_matrix_2) {
  matrix_t temp;
  matrix_t temp2;
  matrix_t result;
  matrix_t result_defolt;
  s21_create_matrix(2, 3, &temp);
  s21_create_matrix(3, 2, &temp2);
  s21_create_matrix(2, 2, &result_defolt);
  s21_full_matrix(&temp);
  s21_full_matrix(&temp2);
  result_defolt.matrix[0][0] = 22;
  result_defolt.matrix[0][1] = 28;
  result_defolt.matrix[1][0] = 49;
  result_defolt.matrix[1][1] = 64;
  ck_assert_int_eq(s21_mult_matrix(&temp, &temp2, &result), 0);
  ck_assert_int_eq(s21_eq_matrix(&result_defolt, &result), 1);
  s21_remove_matrix(&temp);
  s21_remove_matrix(&temp2);
  s21_remove_matrix(&result);
  s21_remove_matrix(&result_defolt);
}
END_TEST

START_TEST(s21_mult_matrix_3) {
  matrix_t temp;
  matrix_t temp2;
  matrix_t result;
  s21_create_matrix(3, 3, &temp);
  s21_create_matrix(3, 3, &temp2);
  s21_full_matrix(&temp);
  s21_full_matrix(&temp2);
  ck_assert_int_eq(s21_mult_matrix(&temp, &temp2, &result), 0);
  s21_remove_matrix(&temp);
  s21_remove_matrix(&temp2);
  s21_remove_matrix(&result);
}
END_TEST

START_TEST(s21_mult_matrix_4) {
  matrix_t result1;
  matrix_t result2;
  matrix_t result3;
  matrix_t result4;
  s21_create_matrix(4, 4, &result1);
  s21_create_matrix(3, 3, &result2);
  s21_fill(&result1, 3);
  s21_fill(&result2, 3);
  int expected_result = s21_create_matrix(4, 4, &result3);
  expected_result = 1;
  int actual_result = s21_mult_matrix(&result1, &result2, &result4);
  ck_assert_uint_ne(expected_result, actual_result);
  s21_remove_matrix(&result3);
  s21_remove_matrix(&result2);
  s21_remove_matrix(&result1);
}
END_TEST

START_TEST(s21_mult_number_1) {
  const int rows = 2;
  const int cols = 2;
  matrix_t m = {0};
  s21_create_matrix(rows, cols, &m);
  matrix_t check = {0};
  s21_create_matrix(rows, cols, &check);
  m.matrix[0][0] = 1;
  m.matrix[0][1] = 1;
  m.matrix[1][0] = 1;
  m.matrix[1][1] = 1;
  check.matrix[0][0] = 2;
  check.matrix[0][1] = 2;
  check.matrix[1][0] = 2;
  check.matrix[1][1] = 2;
  int num = 2;
  matrix_t res = {0};
  ck_assert_int_eq(s21_mult_number(&m, num, &res), 0);
  ck_assert_int_eq(s21_eq_matrix(&check, &res), 1);
  s21_remove_matrix(&m);
  s21_remove_matrix(&res);
  s21_remove_matrix(&check);
}
END_TEST

START_TEST(s21_mult_number_2) {
  matrix_t result1;
  matrix_t result2;
  matrix_t result3;
  s21_create_matrix(4, 4, &result1);
  s21_fill(&result1, 3);
  int expected_result = s21_create_matrix(4, 4, &result2);
  s21_fill(&result2, 30);
  int actual_result = s21_mult_number(&result1, 10, &result3);
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      ck_assert_double_eq(result3.matrix[i][j], result2.matrix[i][j]);
    }
  }
  ck_assert_int_eq(expected_result, actual_result);
  s21_remove_matrix(&result1);
  s21_remove_matrix(&result2);
  s21_remove_matrix(&result3);
}
END_TEST

START_TEST(s21_mult_number_3) {
  matrix_t result1;
  matrix_t result3;
  s21_create_matrix(2, 2, &result1);
  int expected_result = 0;
  int actual_result = s21_mult_number(&result1, 3, &result3);
  ck_assert_uint_eq(expected_result, actual_result);
  s21_remove_matrix(&result3);
  s21_remove_matrix(&result1);
}
END_TEST

START_TEST(s21_mult_number_4) {
  matrix_t result1;
  matrix_t result2;
  matrix_t result3;
  matrix_t result4;
  s21_create_matrix(4, 4, &result1);
  s21_create_matrix(4, 4, &result2);
  s21_fill(&result1, 3);
  s21_fill(&result2, 3);
  int expected_result = s21_create_matrix(4, 4, &result3);
  s21_fill(&result3, 36);
  int actual_result = s21_mult_matrix(&result1, &result2, &result4);
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      ck_assert_double_eq(result3.matrix[i][j], result4.matrix[i][j]);
    }
  }
  ck_assert_uint_eq(expected_result, actual_result);
  s21_remove_matrix(&result4);
  s21_remove_matrix(&result3);
  s21_remove_matrix(&result2);
  s21_remove_matrix(&result1);
}
END_TEST

START_TEST(s21_mult_number_5) {
  matrix_t temp;
  matrix_t temp2;
  matrix_t result;
  matrix_t result_defolt;
  double num = 777.777;
  s21_create_matrix(3, 3, &temp);
  s21_create_matrix(3, 3, &temp2);
  s21_create_matrix(3, 3, &result_defolt);
  s21_full_matrix(&temp);
  s21_full_matrix(&temp2);
  for (int i = 0; (i < temp.rows); i++) {
    for (int j = 0; j < temp.columns; j++) {
      result_defolt.matrix[i][j] = temp.matrix[i][j] * 777.777;
    }
  }
  ck_assert_int_eq(s21_mult_number(&temp, num, &result), 0);
  ck_assert_int_eq(s21_eq_matrix(&result_defolt, &result), 1);
  s21_remove_matrix(&temp);
  s21_remove_matrix(&temp2);
  s21_remove_matrix(&result);
  s21_remove_matrix(&result_defolt);
}
END_TEST

START_TEST(s21_mult_number_6) {
  matrix_t temp;
  matrix_t temp2;
  matrix_t result;
  matrix_t result_defolt;
  double num = 777.777;
  s21_create_matrix(3, 3, &temp);
  s21_create_matrix(3, 3, &temp2);
  s21_create_matrix(3, 3, &result_defolt);
  s21_full_matrix(&temp);
  s21_full_matrix(&temp2);
  for (int i = 0; i < temp.rows; i++) {
    for (int j = 0; j < temp.columns; j++) {
      result_defolt.matrix[i][j] = temp.matrix[i][j] * 777.777;
    }
  }
  ck_assert_int_eq(s21_mult_number(&temp, num, &result), 0);
  ck_assert_int_eq(s21_eq_matrix(&result_defolt, &result), 1);
  s21_remove_matrix(&temp);
  s21_remove_matrix(&temp2);
  s21_remove_matrix(&result);
  s21_remove_matrix(&result_defolt);
}
END_TEST

START_TEST(s21_transpose_1) {
  const int rows = 2;
  const int cols = 2;
  matrix_t m = {0};
  s21_create_matrix(rows, cols, &m);
  matrix_t check = {0};
  s21_create_matrix(cols, rows, &check);
  m.matrix[0][0] = 1;
  m.matrix[0][1] = 2;
  m.matrix[1][0] = 3;
  m.matrix[1][1] = 4;
  check.matrix[0][0] = 1;
  check.matrix[0][1] = 3;
  check.matrix[1][0] = 2;
  check.matrix[1][1] = 4;
  matrix_t res = {0};
  ck_assert_int_eq(s21_transpose(&m, &res), 0);
  ck_assert_int_eq(s21_eq_matrix(&check, &res), 1);
  s21_remove_matrix(&m);
  s21_remove_matrix(&res);
  s21_remove_matrix(&check);
}
END_TEST

START_TEST(s21_transpose_2) {
  matrix_t temp;
  matrix_t result;
  matrix_t result_defolt;
  s21_create_matrix(3, 2, &temp);
  s21_create_matrix(2, 3, &result_defolt);
  s21_full_matrix(&temp);
  result_defolt.matrix[0][0] = 1;
  result_defolt.matrix[0][1] = 3;
  result_defolt.matrix[0][2] = 5;
  result_defolt.matrix[1][0] = 2;
  result_defolt.matrix[1][1] = 4;
  result_defolt.matrix[1][2] = 6;
  ck_assert_int_eq(s21_transpose(&temp, &result), 0);
  ck_assert_int_eq(s21_eq_matrix(&result_defolt, &result), 1);
  s21_remove_matrix(&temp);
  s21_remove_matrix(&result);
  s21_remove_matrix(&result_defolt);
}
END_TEST

START_TEST(s21_transpose_3) {
  matrix_t A, B, R;
  s21_create_matrix(1, 1, &A);
  s21_create_matrix(1, 1, &B);
  A.matrix[0][0] = 1.25;
  B.matrix[0][0] = 1.25;
  s21_transpose(&A, &R);
  ck_assert_int_eq(s21_eq_matrix(&R, &B), 1);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&R);
}
END_TEST

START_TEST(s21_transpose_4) {
  matrix_t A, B, R;
  s21_create_matrix(3, 3, &A);
  s21_create_matrix(3, 3, &B);
  A.matrix[0][0] = 0.25;
  A.matrix[0][1] = 1.25;
  A.matrix[0][2] = 2.25;
  A.matrix[1][0] = 3.25;
  A.matrix[1][1] = 4.25;
  A.matrix[1][2] = 5.25;
  A.matrix[2][0] = 6.25;
  A.matrix[2][1] = 7.25;
  A.matrix[2][2] = 8.25;
  s21_transpose(&A, &R);
  B.matrix[0][0] = 0.25;
  B.matrix[1][0] = 1.25;
  B.matrix[2][0] = 2.25;
  B.matrix[0][1] = 3.25;
  B.matrix[1][1] = 4.25;
  B.matrix[2][1] = 5.25;
  B.matrix[0][2] = 6.25;
  B.matrix[1][2] = 7.25;
  B.matrix[2][2] = 8.25;
  ck_assert_int_eq(s21_eq_matrix(&R, &B), 1);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&R);
}
END_TEST

START_TEST(s21_determinant_1) {
  matrix_t temp;
  double result;
  int result_defolt;
  s21_create_matrix(3, 2, &temp);
  s21_full_matrix(&temp);
  result_defolt = s21_determinant(&temp, &result);
  ck_assert_int_eq(result_defolt, 2);
  s21_remove_matrix(&temp);
}
END_TEST
START_TEST(s21_determinant_2) {
  matrix_t temp;
  double result;
  int result_defolt;
  s21_create_matrix(3, 3, &temp);
  s21_full_matrix(&temp);
  result_defolt = s21_determinant(&temp, &result);
  ck_assert_int_eq(result_defolt, 0);
  ck_assert_uint_eq(result, 0);
  s21_remove_matrix(&temp);
}
END_TEST
START_TEST(s21_determinant_3) {
  matrix_t temp;
  double result;
  int result_defolt;
  s21_create_matrix(3, 3, &temp);
  temp.matrix[0][0] = 0;
  temp.matrix[0][1] = 9;
  temp.matrix[0][2] = 5;

  temp.matrix[1][0] = 4;
  temp.matrix[1][1] = 3;
  temp.matrix[1][2] = -5;

  temp.matrix[2][0] = -1;
  temp.matrix[2][1] = 6;
  temp.matrix[2][2] = -4;
  result_defolt = s21_determinant(&temp, &result);
  ck_assert_int_eq(result_defolt, 0);
  ck_assert_uint_eq(result, 324);
  s21_remove_matrix(&temp);
}
END_TEST
START_TEST(s21_determinant_4) {
  matrix_t temp;
  double result;
  int result_defolt;
  s21_create_matrix(3, 3, &temp);
  temp.matrix[0][0] = 1;
  temp.matrix[1][1] = 1;
  temp.matrix[2][2] = 1;

  result_defolt = s21_determinant(&temp, &result);
  ck_assert_int_eq(result_defolt, 0);
  ck_assert_uint_eq(result, 1);
  s21_remove_matrix(&temp);
}
END_TEST
START_TEST(s21_determinant_5) {
  matrix_t result1;
  double result2;
  s21_create_matrix(3, 3, &result1);
  result1.matrix[0][0] = 1;
  result1.matrix[0][1] = 2;
  result1.matrix[0][2] = 3;

  result1.matrix[1][0] = 4;
  result1.matrix[1][1] = 5;
  result1.matrix[1][2] = 6;

  result1.matrix[2][0] = 7;
  result1.matrix[2][1] = 8;
  result1.matrix[2][2] = 9;
  double expected_result = 0;
  s21_determinant(&result1, &result2);
  ck_assert_ldouble_eq(expected_result, result2);
  s21_remove_matrix(&result1);
}
END_TEST

START_TEST(s21_determinant_6) {
  matrix_t result1;
  double result3;
  s21_create_matrix(3, 4, &result1);
  int actual_result = 2;
  int expected_result = s21_determinant(&result1, &result3);
  ck_assert_uint_eq(expected_result, actual_result);
  s21_remove_matrix(&result1);
}
END_TEST

START_TEST(s21_determinant_7) {
  const int rows = 3;
  const int cols = 3;
  matrix_t m1 = {0};

  s21_create_matrix(rows, cols, &m1);
  int m = 1;
  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < cols; j++) {
      m1.matrix[i][j] = m++;
    }
  }
  m1.matrix[2][2] = 0;
  double result = 0;
  int got = s21_determinant(&m1, &result);
  ck_assert_double_eq_tol(result, 27, 1e-6);
  ck_assert_int_eq(got, 0);
  s21_remove_matrix(&m1);
}
END_TEST

START_TEST(s21_determinant_8) {
  matrix_t result1;
  double result2;
  s21_create_matrix(1, 1, &result1);
  result1.matrix[0][0] = 5;
  double expected_result = 5;
  s21_determinant(&result1, &result2);
  ck_assert_ldouble_eq(expected_result, result2);
  s21_remove_matrix(&result1);
}
END_TEST

START_TEST(s21_calc_complements_1) {
  matrix_t result1;
  matrix_t result2;
  matrix_t result3;

  s21_create_matrix(3, 3, &result1);
  result1.matrix[0][0] = 1;
  result1.matrix[0][1] = 2;
  result1.matrix[0][2] = 3;

  result1.matrix[1][0] = 0;
  result1.matrix[1][1] = 4;
  result1.matrix[1][2] = 2;

  result1.matrix[2][0] = 5;
  result1.matrix[2][1] = 2;
  result1.matrix[2][2] = 1;
  int expected_result = s21_create_matrix(3, 3, &result2);
  result2.matrix[0][0] = 0;
  result2.matrix[0][1] = 10;
  result2.matrix[0][2] = -20;

  result2.matrix[1][0] = 4;
  result2.matrix[1][1] = -14;
  result2.matrix[1][2] = 8;

  result2.matrix[2][0] = -8;
  result2.matrix[2][1] = -2;
  result2.matrix[2][2] = 4;
  int actual_result = s21_calc_complements(&result1, &result3);

  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      ck_assert_double_eq_tol(result2.matrix[i][j], result3.matrix[i][j], 1e-6);
    }
  }
  ck_assert_uint_eq(expected_result, actual_result);
  s21_remove_matrix(&result3);
  s21_remove_matrix(&result2);
  s21_remove_matrix(&result1);
}

START_TEST(s21_calc_complements_2) {
  matrix_t result1;
  matrix_t result3;
  s21_create_matrix(3, -1, &result1);
  int expected_result = 1;
  int actual_result = s21_calc_complements(&result1, &result3);
  ck_assert_int_eq(expected_result, actual_result);
}
END_TEST

START_TEST(s21_calc_complements_3) {
  const int size = 3;
  matrix_t m = {0};
  s21_create_matrix(size, size, &m);
  m.matrix[0][0] = 1;
  m.matrix[0][1] = 2;
  m.matrix[0][2] = 3;
  m.matrix[1][1] = 4;
  m.matrix[1][2] = 2;
  m.matrix[2][0] = 5;
  m.matrix[2][1] = 2;
  m.matrix[2][2] = 1;

  matrix_t expected = {0};
  s21_create_matrix(size, size, &expected);
  expected.matrix[0][1] = 10;
  expected.matrix[0][2] = -20;
  expected.matrix[1][0] = 4;
  expected.matrix[1][1] = -14;
  expected.matrix[1][2] = 8;
  expected.matrix[2][0] = -8;
  expected.matrix[2][1] = -2;
  expected.matrix[2][2] = 4;

  matrix_t res = {0};
  s21_calc_complements(&m, &res);

  ck_assert_int_eq(s21_eq_matrix(&expected, &res), 1);
  s21_remove_matrix(&m);
  s21_remove_matrix(&res);
  s21_remove_matrix(&expected);
}
END_TEST

START_TEST(s21_calc_complements_4) {
  matrix_t test, result;
  s21_create_matrix(3, 2, &test);
  int result_status;
  s21_full_matrix(&test);
  result_status = s21_calc_complements(&test, &result);
  ck_assert_int_eq(result_status, 2);
  s21_remove_matrix(&test);
  // s21_remove_matrix(&result);
}
END_TEST

START_TEST(s21_calc_complements_5) {
  matrix_t test, result;
  s21_create_matrix(3, 3, &test);
  s21_full_matrix(&test);
  int result_status = s21_calc_complements(&test, &result);
  ck_assert_int_eq(result_status, 0);
  s21_remove_matrix(&test);
  s21_remove_matrix(&result);
}
END_TEST

START_TEST(s21_calc_complements_6) {
  matrix_t test, test_2, result;
  s21_create_matrix(3, 3, &test);
  test.matrix[0][0] = 1;
  test.matrix[0][1] = 2;
  test.matrix[0][2] = 3;
  test.matrix[1][0] = 0;
  test.matrix[1][1] = 4;
  test.matrix[1][2] = 2;
  test.matrix[2][0] = 5;
  test.matrix[2][1] = 2;
  test.matrix[2][2] = 1;
  s21_calc_complements(&test, &result);
  s21_create_matrix(3, 3, &test_2);
  test_2.matrix[0][0] = 0;
  test_2.matrix[0][1] = 10;
  test_2.matrix[0][2] = -20;
  test_2.matrix[1][0] = 4;
  test_2.matrix[1][1] = -14;
  test_2.matrix[1][2] = 8;
  test_2.matrix[2][0] = -8;
  test_2.matrix[2][1] = -2;
  test_2.matrix[2][2] = 4;
  for (int i = 0; i < result.rows; i++) {
    for (int j = 0; j < result.columns; j++) {
      ck_assert_uint_eq(result.matrix[i][j], test_2.matrix[i][j]);
    }
  }
  s21_remove_matrix(&test);
  s21_remove_matrix(&test_2);
  s21_remove_matrix(&result);
}
END_TEST

START_TEST(s21_calc_complements_7) {
  matrix_t test, test_2, result;
  s21_create_matrix(1, 1, &test);
  test.matrix[0][0] = 1;
  s21_calc_complements(&test, &result);
  s21_create_matrix(1, 1, &test_2);
  test_2.matrix[0][0] = 1;
  for (int i = 0; i < result.rows; i++) {
    for (int j = 0; j < result.columns; j++) {
      ck_assert_uint_eq(result.matrix[i][j], test_2.matrix[i][j]);
    }
  }
  s21_remove_matrix(&test);
  s21_remove_matrix(&test_2);
  s21_remove_matrix(&result);
}
END_TEST

START_TEST(s21_inverse_matrix_1) {
  matrix_t temp, result_defolt, result_defolt_2;
  s21_create_matrix(3, 3, &temp);
  s21_create_matrix(3, 3, &result_defolt);
  temp.matrix[0][0] = 2;
  temp.matrix[0][1] = 5;
  temp.matrix[0][2] = 7;
  temp.matrix[1][0] = 6;
  temp.matrix[1][1] = 3;
  temp.matrix[1][2] = 4;
  temp.matrix[2][0] = 5;
  temp.matrix[2][1] = -2;
  temp.matrix[2][2] = -3;
  result_defolt.matrix[0][0] = 1;
  result_defolt.matrix[0][1] = -1;
  result_defolt.matrix[0][2] = 1;
  result_defolt.matrix[1][0] = -38;
  result_defolt.matrix[1][1] = 41;
  result_defolt.matrix[1][2] = -34;
  result_defolt.matrix[2][0] = 27;
  result_defolt.matrix[2][1] = -29;
  result_defolt.matrix[2][2] = 24;

  s21_inverse_matrix(&temp, &result_defolt_2);

  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      ck_assert_uint_eq(result_defolt.matrix[i][j],
                        result_defolt_2.matrix[i][j]);
    }
  }
  s21_remove_matrix(&temp);
  s21_remove_matrix(&result_defolt);
  s21_remove_matrix(&result_defolt_2);
}
END_TEST

START_TEST(s21_inverse_matrix_3) {
  matrix_t temp, result;
  s21_create_matrix(3, 4, &temp);
  s21_full_matrix(&temp);
  int result_status = s21_inverse_matrix(&temp, &result);
  ck_assert_int_eq(result_status, 2);
  s21_remove_matrix(&temp);
}
END_TEST

START_TEST(s21_inverse_matrix_4) {
  matrix_t temp, result;
  s21_create_matrix(3, 3, &temp);
  temp.matrix[0][0] = 1;
  temp.matrix[1][1] = 1;
  temp.matrix[2][2] = 1;
  s21_inverse_matrix(&temp, &result);
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      ck_assert_uint_eq(temp.matrix[i][j], result.matrix[i][j]);
    }
  }
  s21_remove_matrix(&temp);
  s21_remove_matrix(&result);
}
END_TEST

START_TEST(s21_inverse_matrix_5) {
  matrix_t result1;
  matrix_t result2;
  matrix_t result3;
  s21_create_matrix(3, 3, &result1);
  result1.matrix[0][0] = 2;
  result1.matrix[0][1] = 5;
  result1.matrix[0][2] = 7;
  result1.matrix[1][0] = 6;
  result1.matrix[1][1] = 3;
  result1.matrix[1][2] = 4;
  result1.matrix[2][0] = 5;
  result1.matrix[2][1] = -2;
  result1.matrix[2][2] = -3;
  int expected_result = s21_create_matrix(3, 3, &result2);
  result2.matrix[0][0] = 1;
  result2.matrix[0][1] = -1;
  result2.matrix[0][2] = 1;
  result2.matrix[1][0] = -38;
  result2.matrix[1][1] = 41;
  result2.matrix[1][2] = -34;
  result2.matrix[2][0] = 27;
  result2.matrix[2][1] = -29;
  result2.matrix[2][2] = 24;
  int actual_result = s21_inverse_matrix(&result1, &result3);
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      ck_assert_double_eq_tol(result2.matrix[i][j], result3.matrix[i][j], 1e-6);
    }
  }
  ck_assert_uint_eq(expected_result, actual_result);
  s21_remove_matrix(&result3);
  s21_remove_matrix(&result2);
  s21_remove_matrix(&result1);
}
END_TEST

START_TEST(s21_inverse_matrix_6) {
  matrix_t result1;
  matrix_t result3;
  s21_create_matrix(3, 3, &result1);
  result1.matrix[0][0] = 1;
  result1.matrix[0][1] = 2;
  result1.matrix[0][2] = 3;

  result1.matrix[1][0] = 4;
  result1.matrix[1][1] = 5;
  result1.matrix[1][2] = 6;

  result1.matrix[2][0] = 7;
  result1.matrix[2][1] = 8;
  result1.matrix[2][2] = 9;
  int expected_result = 2;
  int actual_result = s21_inverse_matrix(&result1, &result3);
  ck_assert_uint_eq(expected_result, actual_result);

  s21_remove_matrix(&result1);
}
END_TEST
START_TEST(s21_inverse_matrix_7) {
  const int size = 3;
  matrix_t m = {0};
  s21_create_matrix(size, size, &m);
  m.matrix[0][0] = 2;
  m.matrix[0][1] = 5;
  m.matrix[0][2] = 7;
  m.matrix[1][0] = 6;
  m.matrix[1][1] = 3;
  m.matrix[1][2] = 4;
  m.matrix[2][0] = 5;
  m.matrix[2][1] = -2;
  m.matrix[2][2] = -3;
  matrix_t res = {0};
  s21_inverse_matrix(&m, &res);
  matrix_t expected = {0};
  s21_create_matrix(size, size, &expected);
  expected.matrix[0][0] = 1;
  expected.matrix[0][1] = -1;
  expected.matrix[0][2] = 1;
  expected.matrix[1][0] = -38;
  expected.matrix[1][1] = 41;
  expected.matrix[1][2] = -34;
  expected.matrix[2][0] = 27;
  expected.matrix[2][1] = -29;
  expected.matrix[2][2] = 24;
  ck_assert_int_eq(s21_eq_matrix(&expected, &res), 1);
  s21_remove_matrix(&expected);
  s21_remove_matrix(&res);
  s21_remove_matrix(&m);
}
END_TEST

START_TEST(null_1) {
  matrix_t *B = NULL;
  matrix_t *R = NULL;
  int res = s21_calc_complements(B, R);
  ck_assert_int_eq(res, 1);
}

START_TEST(null_2) {
  matrix_t *B = NULL;
  double re = 0;
  int res = s21_determinant(B, &re);
  ck_assert_int_eq(res, 1);
}
START_TEST(null_3) {
  matrix_t *B = NULL;
  matrix_t *R = NULL;
  int res = s21_inverse_matrix(B, R);
  ck_assert_int_eq(res, 1);
}
START_TEST(null_4) {
  matrix_t *A = NULL;
  matrix_t *B = NULL;
  matrix_t *R = NULL;
  int res = s21_mult_matrix(A, B, R);
  ck_assert_int_eq(res, 1);
}
START_TEST(null_5) {
  matrix_t *B = NULL;
  double num = 0;
  matrix_t *R = NULL;
  int res = s21_mult_number(B, num, R);
  ck_assert_int_eq(res, 1);
}
START_TEST(null_6) {
  matrix_t *A = NULL;
  matrix_t *B = NULL;
  matrix_t *R = NULL;
  int res = s21_sub_matrix(A, B, R);
  ck_assert_int_eq(res, 1);
}
START_TEST(null_7) {
  matrix_t *A = NULL;
  matrix_t *B = NULL;
  matrix_t *R = NULL;
  int res = s21_sum_matrix(A, B, R);
  ck_assert_int_eq(res, 1);
}
START_TEST(null_8) {
  matrix_t *B = NULL;
  matrix_t *R = NULL;
  int res = s21_transpose(B, R);
  ck_assert_int_eq(res, 1);
}

int main() {
  Suite *s1 = suite_create("Core");
  TCase *tc_1 = tcase_create("Core");
  SRunner *sr = srunner_create(s1);
  int a;
  suite_add_tcase(s1, tc_1);

  tcase_add_test(tc_1, create_matrix_1);

  tcase_add_test(tc_1, s21_sum_matrix_test_1);
  tcase_add_test(tc_1, s21_sum_matrix_test_2);
  tcase_add_test(tc_1, s21_sum_matrix_test_3);
  tcase_add_test(tc_1, s21_sum_matrix_test_4);
  tcase_add_test(tc_1, s21_sum_matrix_test_5);

  tcase_add_test(tc_1, s21_sub_matrix_test_1);
  tcase_add_test(tc_1, s21_sub_matrix_test_2);
  tcase_add_test(tc_1, s21_sub_matrix_test_3);
  tcase_add_test(tc_1, s21_sub_matrix_test_4);
  tcase_add_test(tc_1, s21_sub_matrix_test_5);
  tcase_add_test(tc_1, s21_sub_matrix_test_6);

  tcase_add_test(tc_1, s21_eq_matrix_1);
  tcase_add_test(tc_1, s21_eq_matrix_2);
  tcase_add_test(tc_1, s21_eq_matrix_3);
  tcase_add_test(tc_1, s21_eq_matrix_3);
  tcase_add_test(tc_1, s21_eq_matrix_4);
  tcase_add_test(tc_1, s21_eq_matrix_5);
  tcase_add_test(tc_1, s21_eq_matrix_6);
  tcase_add_test(tc_1, s21_eq_matrix_7);
  tcase_add_test(tc_1, s21_eq_matrix_8);
  tcase_add_test(tc_1, s21_eq_matrix_9);

  tcase_add_test(tc_1, s21_mult_number_1);
  tcase_add_test(tc_1, s21_mult_number_2);
  tcase_add_test(tc_1, s21_mult_number_3);
  tcase_add_test(tc_1, s21_mult_number_4);
  tcase_add_test(tc_1, s21_mult_number_5);
  tcase_add_test(tc_1, s21_mult_number_6);

  tcase_add_test(tc_1, s21_mult_matrix_1);
  tcase_add_test(tc_1, s21_mult_matrix_2);
  tcase_add_test(tc_1, s21_mult_matrix_3);
  tcase_add_test(tc_1, s21_mult_matrix_4);

  tcase_add_test(tc_1, s21_transpose_1);
  tcase_add_test(tc_1, s21_transpose_2);
  tcase_add_test(tc_1, s21_transpose_3);
  tcase_add_test(tc_1, s21_transpose_4);

  tcase_add_test(tc_1, s21_determinant_1);
  tcase_add_test(tc_1, s21_determinant_2);
  tcase_add_test(tc_1, s21_determinant_3);
  tcase_add_test(tc_1, s21_determinant_4);
  tcase_add_test(tc_1, s21_determinant_5);
  tcase_add_test(tc_1, s21_determinant_6);
  tcase_add_test(tc_1, s21_determinant_7);
  tcase_add_test(tc_1, s21_determinant_8);

  tcase_add_test(tc_1, s21_calc_complements_1);
  tcase_add_test(tc_1, s21_calc_complements_2);
  tcase_add_test(tc_1, s21_calc_complements_3);
  tcase_add_test(tc_1, s21_calc_complements_4);
  tcase_add_test(tc_1, s21_calc_complements_5);
  tcase_add_test(tc_1, s21_calc_complements_6);
  tcase_add_test(tc_1, s21_calc_complements_7);

  tcase_add_test(tc_1, s21_inverse_matrix_1);
  tcase_add_test(tc_1, s21_inverse_matrix_3);
  tcase_add_test(tc_1, s21_inverse_matrix_4);
  tcase_add_test(tc_1, s21_inverse_matrix_5);
  tcase_add_test(tc_1, s21_inverse_matrix_6);
  tcase_add_test(tc_1, s21_inverse_matrix_7);

  tcase_add_test(tc_1, null_1);
  tcase_add_test(tc_1, null_2);
  tcase_add_test(tc_1, null_3);
  tcase_add_test(tc_1, null_3);
  tcase_add_test(tc_1, null_4);
  tcase_add_test(tc_1, null_5);
  tcase_add_test(tc_1, null_6);
  tcase_add_test(tc_1, null_7);
  tcase_add_test(tc_1, null_8);

  srunner_run_all(sr, CK_VERBOSE);
  srunner_run_all(sr, CK_ENV);
  a = srunner_ntests_failed(sr);
  srunner_free(sr);

  return a == 0 ? 0 : 1;
}