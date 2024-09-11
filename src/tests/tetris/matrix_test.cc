#include "tetris_suites.h"

START_TEST(matrix_rotate_test_1) {
  int **matrix_to_rotate = get_tetramino(1);
  int **correct = create_matrix(4, 4);
  correct[0][2] = 1;
  correct[1][2] = 1;
  correct[2][2] = 1;
  correct[3][2] = 1;
  rotate_matrix_90_clockwise(matrix_to_rotate, 4, 4);
  int is_equal = eq_matrix(matrix_to_rotate, correct, 4, 4);
  ck_assert_int_eq(1, is_equal);
  remove_matrix(matrix_to_rotate);
  remove_matrix(correct);
}
END_TEST

START_TEST(matrix_rotate_test_2) {
  int **matrix_to_rotate = get_tetramino(1);
  int **correct = create_matrix(4, 4);
  correct[2][0] = 1;
  correct[2][1] = 1;
  correct[2][2] = 1;
  correct[2][3] = 1;
  rotate_matrix_90_clockwise(matrix_to_rotate, 4, 4);
  rotate_matrix_90_clockwise(matrix_to_rotate, 4, 4);
  int is_equal = eq_matrix(matrix_to_rotate, correct, 4, 4);
  ck_assert_int_eq(1, is_equal);
  remove_matrix(matrix_to_rotate);
  remove_matrix(correct);
}
END_TEST

START_TEST(matrix_rotate_test_3) {
  int **matrix_to_rotate = get_tetramino(2);
  int **correct = create_matrix(3, 3);
  correct[0][1] = 2;
  correct[0][2] = 2;
  correct[1][1] = 2;
  correct[2][1] = 2;
  rotate_matrix_90_clockwise(matrix_to_rotate, 3, 3);
  int is_equal = eq_matrix(matrix_to_rotate, correct, 3, 3);
  ck_assert_int_eq(1, is_equal);
  remove_matrix(matrix_to_rotate);
  remove_matrix(correct);
}
END_TEST

START_TEST(matrix_rotate_test_4) {
  int **matrix_to_rotate = get_tetramino(2);
  int **correct = create_matrix(3, 3);
  correct[1][0] = 2;
  correct[1][1] = 2;
  correct[1][2] = 2;
  correct[2][2] = 2;
  rotate_matrix_90_clockwise(matrix_to_rotate, 3, 3);
  rotate_matrix_90_clockwise(matrix_to_rotate, 3, 3);
  int is_equal = eq_matrix(matrix_to_rotate, correct, 3, 3);
  ck_assert_int_eq(1, is_equal);
  remove_matrix(matrix_to_rotate);
  remove_matrix(correct);
}
END_TEST

START_TEST(matrix_rotate_test_5) {
  int **matrix_to_rotate = get_tetramino(3);
  int **correct = create_matrix(3, 3);
  correct[0][1] = 3;
  correct[1][1] = 3;
  correct[2][1] = 3;
  correct[2][2] = 3;
  rotate_matrix_90_clockwise(matrix_to_rotate, 3, 3);
  int is_equal = eq_matrix(matrix_to_rotate, correct, 3, 3);
  ck_assert_int_eq(1, is_equal);
  remove_matrix(matrix_to_rotate);
  remove_matrix(correct);
}
END_TEST

START_TEST(matrix_rotate_test_6) {
  int **matrix_to_rotate = get_tetramino(3);
  int **correct = create_matrix(3, 3);
  correct[1][0] = 3;
  correct[1][1] = 3;
  correct[1][2] = 3;
  correct[2][0] = 3;
  rotate_matrix_90_clockwise(matrix_to_rotate, 3, 3);
  rotate_matrix_90_clockwise(matrix_to_rotate, 3, 3);
  int is_equal = eq_matrix(matrix_to_rotate, correct, 3, 3);
  ck_assert_int_eq(1, is_equal);
  remove_matrix(matrix_to_rotate);
  remove_matrix(correct);
}
END_TEST

START_TEST(matrix_rotate_test_7) {
  int **matrix_to_rotate = get_tetramino(4);
  int **correct = create_matrix(2, 2);
  correct[0][0] = 4;
  correct[0][1] = 4;
  correct[1][0] = 4;
  correct[1][1] = 4;
  rotate_matrix_90_clockwise(matrix_to_rotate, 2, 2);
  rotate_matrix_90_clockwise(matrix_to_rotate, 2, 2);
  int is_equal = eq_matrix(matrix_to_rotate, correct, 2, 2);
  ck_assert_int_eq(1, is_equal);
  remove_matrix(matrix_to_rotate);
  remove_matrix(correct);
}
END_TEST

START_TEST(matrix_rotate_test_8) {
  int **matrix_to_rotate = get_tetramino(5);
  int **correct = create_matrix(3, 3);
  correct[0][1] = 5;
  correct[1][1] = 5;
  correct[1][2] = 5;
  correct[2][2] = 5;
  rotate_matrix_90_clockwise(matrix_to_rotate, 3, 3);
  int is_equal = eq_matrix(matrix_to_rotate, correct, 3, 3);
  ck_assert_int_eq(1, is_equal);
  remove_matrix(matrix_to_rotate);
  remove_matrix(correct);
}
END_TEST

START_TEST(matrix_rotate_test_9) {
  int **matrix_to_rotate = get_tetramino(5);
  int **correct = create_matrix(3, 3);
  correct[1][1] = 5;
  correct[1][2] = 5;
  correct[2][0] = 5;
  correct[2][1] = 5;
  rotate_matrix_90_clockwise(matrix_to_rotate, 3, 3);
  rotate_matrix_90_clockwise(matrix_to_rotate, 3, 3);
  int is_equal = eq_matrix(matrix_to_rotate, correct, 3, 3);
  ck_assert_int_eq(1, is_equal);
  remove_matrix(matrix_to_rotate);
  remove_matrix(correct);
}
END_TEST

START_TEST(matrix_rotate_test_10) {
  int **matrix_to_rotate = get_tetramino(6);
  int **correct = create_matrix(3, 3);
  correct[1][0] = 6;
  correct[1][1] = 6;
  correct[1][2] = 6;
  correct[2][1] = 6;
  rotate_matrix_90_clockwise(matrix_to_rotate, 3, 3);
  rotate_matrix_90_clockwise(matrix_to_rotate, 3, 3);
  int is_equal = eq_matrix(matrix_to_rotate, correct, 3, 3);
  ck_assert_int_eq(1, is_equal);
  remove_matrix(matrix_to_rotate);
  remove_matrix(correct);
}
END_TEST

START_TEST(matrix_rotate_test_11) {
  int **matrix_to_rotate = get_tetramino(7);
  int **correct = create_matrix(3, 3);
  int **correct_copy = create_matrix(3, 3);
  copy_matrix(correct_copy, correct, 3, 3);
  clear_matrix(correct, 3, 3);
  correct_copy[1][0] = 7;
  correct_copy[1][1] = 7;
  correct_copy[2][1] = 7;
  correct_copy[2][2] = 7;
  rotate_matrix_90_clockwise(matrix_to_rotate, 3, 3);
  rotate_matrix_90_clockwise(matrix_to_rotate, 3, 3);
  int is_equal = eq_matrix(matrix_to_rotate, correct_copy, 3, 3);
  ck_assert_int_eq(1, is_equal);
  remove_matrix(matrix_to_rotate);
  remove_matrix(correct_copy);
  remove_matrix(correct);
}
END_TEST

Suite *matrix_test_suite() {
  Suite *s;
  TCase *tc;

  s = suite_create("matrix_test_suite");
  tc = tcase_create("matrix_test_case");

  tcase_add_test(tc, matrix_rotate_test_1);
  tcase_add_test(tc, matrix_rotate_test_2);
  tcase_add_test(tc, matrix_rotate_test_3);
  tcase_add_test(tc, matrix_rotate_test_4);
  tcase_add_test(tc, matrix_rotate_test_5);
  tcase_add_test(tc, matrix_rotate_test_6);
  tcase_add_test(tc, matrix_rotate_test_7);
  tcase_add_test(tc, matrix_rotate_test_8);
  tcase_add_test(tc, matrix_rotate_test_9);
  tcase_add_test(tc, matrix_rotate_test_10);
  tcase_add_test(tc, matrix_rotate_test_11);

  suite_add_tcase(s, tc);

  return s;
}