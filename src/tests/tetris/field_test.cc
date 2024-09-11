#include "tetris_suites.h"

START_TEST(shift_down_test_1) {
  char *user_name = (char *)malloc(sizeof(char) * 5);
  strcpy(user_name, "igor");
  GameInfo_t *info = init_game_info_tetris(user_name);
  info = current_game_info(info);
  drop_new_tetramino();
  get_next_test(info, 2);
  drop_new_tetramino();
  get_next_test(info, 2);
  info->field[1][5] = 1;
  shift_down(info);
  shift_down(info);
  shift_down(info);
  attach(info);
  ck_assert_int_eq(info->moving->row, -1);
  ck_assert_int_eq(info->field[0][4], info->moving->figure[1][1]);
  ck_assert_int_eq(info->field[0][5], info->moving->figure[1][1]);
  ck_assert_int_eq(info->field[0][6], info->moving->figure[1][1]);
  ck_assert_int_ne(info->field[0][7], info->moving->figure[1][1]);

  destroy_game_info();
}
END_TEST

START_TEST(shift_down_test_2) {
  char *user_name = (char *)malloc(sizeof(char) * 5);
  strcpy(user_name, "igor");
  GameInfo_t *info = init_game_info_tetris(user_name);
  info = current_game_info(info);
  drop_new_tetramino();
  get_next_test(info, 2);
  drop_new_tetramino();
  get_next_test(info, 2);
  info->field[2][7] = 1;
  shift_down(info);
  shift_down(info);
  shift_down(info);
  shift_down(info);
  attach(info);
  ck_assert_int_eq(info->moving->row, 1);
  ck_assert_int_eq(info->field[1][4], info->moving->figure[1][1]);
  ck_assert_int_eq(info->field[2][4], info->moving->figure[1][1]);
  ck_assert_int_eq(info->field[2][5], info->moving->figure[1][1]);
  ck_assert_int_eq(info->field[2][6], info->moving->figure[1][1]);
  ck_assert_int_ne(info->field[0][5], info->moving->figure[1][1]);

  destroy_game_info();
}
END_TEST

START_TEST(shift_right_test_1) {
  char *user_name = (char *)malloc(sizeof(char) * 5);
  strcpy(user_name, "igor");
  GameInfo_t *info = init_game_info_tetris(user_name);
  info = current_game_info(info);
  drop_new_tetramino();
  get_next_test(info, 2);
  drop_new_tetramino();
  get_next_test(info, 2);
  shift_down(info);
  shift_down(info);
  shift_down(info);
  info->field[0][7] = 1;
  shift_right(info);
  shift_right(info);
  shift_right(info);
  attach(info);
  ck_assert_int_eq(info->moving->col, 6);
  ck_assert_int_eq(info->field[0][6], info->moving->figure[1][1]);
  ck_assert_int_eq(info->field[1][6], info->moving->figure[1][1]);
  ck_assert_int_eq(info->field[1][7], info->moving->figure[1][1]);
  ck_assert_int_eq(info->field[1][8], info->moving->figure[1][1]);
  ck_assert_int_ne(info->field[1][5], info->moving->figure[1][1]);

  destroy_game_info();
}
END_TEST

START_TEST(shift_right_test_2) {
  char *user_name = (char *)malloc(sizeof(char) * 5);
  strcpy(user_name, "igor");
  GameInfo_t *info = init_game_info_tetris(user_name);
  info = current_game_info(info);
  drop_new_tetramino();
  get_next_test(info, 2);
  drop_new_tetramino();
  get_next_test(info, 2);
  shift_down(info);
  shift_down(info);
  shift_down(info);
  info->field[1][7] = 1;
  shift_right(info);
  shift_right(info);
  shift_right(info);
  attach(info);
  ck_assert_int_eq(info->moving->col, MOVING_INIT_COL);
  ck_assert_int_eq(info->field[0][4], info->moving->figure[1][1]);
  ck_assert_int_eq(info->field[1][4], info->moving->figure[1][1]);
  ck_assert_int_eq(info->field[1][5], info->moving->figure[1][1]);
  ck_assert_int_eq(info->field[1][6], info->moving->figure[1][1]);
  ck_assert_int_ne(info->field[1][8], info->moving->figure[1][1]);

  destroy_game_info();
}
END_TEST

START_TEST(shift_right_test_3) {
  char *user_name = (char *)malloc(sizeof(char) * 5);
  strcpy(user_name, "igor");
  GameInfo_t *info = init_game_info_tetris(user_name);
  info = current_game_info(info);
  drop_new_tetramino();
  get_next_test(info, 2);
  drop_new_tetramino();
  get_next_test(info, 2);
  shift_down(info);
  shift_down(info);
  shift_down(info);
  info->field[2][7] = 1;
  shift_right(info);
  shift_right(info);
  shift_right(info);
  attach(info);
  ck_assert_int_eq(info->moving->col, 7);
  ck_assert_int_eq(info->field[0][7], info->moving->figure[1][1]);
  ck_assert_int_eq(info->field[1][7], info->moving->figure[1][1]);
  ck_assert_int_eq(info->field[1][8], info->moving->figure[1][1]);
  ck_assert_int_eq(info->field[1][9], info->moving->figure[1][1]);
  ck_assert_int_ne(info->field[0][6], info->moving->figure[1][1]);

  destroy_game_info();
}
END_TEST

START_TEST(shift_right_test_4) {
  char *user_name = (char *)malloc(sizeof(char) * 5);
  strcpy(user_name, "igor");
  GameInfo_t *info = init_game_info_tetris(user_name);
  info = current_game_info(info);
  drop_new_tetramino();
  get_next_test(info, 2);
  drop_new_tetramino();
  get_next_test(info, 2);
  shift_down(info);
  shift_down(info);
  shift_down(info);
  info->field[2][6] = 1;
  shift_right(info);
  shift_right(info);
  shift_right(info);
  shift_right(info);
  shift_right(info);
  attach(info);
  ck_assert_int_eq(info->moving->col, 7);
  ck_assert_int_eq(info->field[0][7], info->moving->figure[1][1]);
  ck_assert_int_eq(info->field[1][7], info->moving->figure[1][1]);
  ck_assert_int_eq(info->field[1][8], info->moving->figure[1][1]);
  ck_assert_int_eq(info->field[1][9], info->moving->figure[1][1]);
  ck_assert_int_ne(info->field[0][6], info->moving->figure[1][1]);

  destroy_game_info();
}
END_TEST

START_TEST(shift_right_test_5) {
  char *user_name = (char *)malloc(sizeof(char) * 5);
  strcpy(user_name, "igor");
  GameInfo_t *info = init_game_info_tetris(user_name);
  info = current_game_info(info);
  drop_new_tetramino();
  get_next_test(info, 1);
  drop_new_tetramino();
  get_next_test(info, 1);
  rotate_tetramino();
  rotate_tetramino();
  rotate_tetramino();
  shift_down(info);
  shift_down(info);
  shift_down(info);
  shift_right(info);
  shift_right(info);
  shift_right(info);
  shift_right(info);
  shift_right(info);

  attach(info);
  ck_assert_int_eq(info->moving->col, 8);
  ck_assert_int_eq(info->field[0][9], info->moving->figure[1][1]);
  ck_assert_int_eq(info->field[1][9], info->moving->figure[1][1]);
  ck_assert_int_eq(info->field[2][9], info->moving->figure[1][1]);
  ck_assert_int_eq(info->field[3][9], info->moving->figure[1][1]);
  ck_assert_int_ne(info->field[0][8], info->moving->figure[1][1]);

  destroy_game_info();
}
END_TEST

START_TEST(shift_left_test_1) {
  char *user_name = (char *)malloc(sizeof(char) * 5);
  strcpy(user_name, "igor");
  GameInfo_t *info = init_game_info_tetris(user_name);
  info = current_game_info(info);
  drop_new_tetramino();
  get_next_test(info, 2);
  drop_new_tetramino();
  get_next_test(info, 2);
  shift_down(info);
  shift_down(info);
  shift_down(info);
  info->field[0][2] = 1;
  shift_left(info);
  shift_left(info);
  shift_left(info);
  attach(info);
  ck_assert_int_eq(info->moving->col, 3);
  ck_assert_int_eq(info->field[0][3], info->moving->figure[1][1]);
  ck_assert_int_eq(info->field[1][3], info->moving->figure[1][1]);
  ck_assert_int_eq(info->field[1][4], info->moving->figure[1][1]);
  ck_assert_int_eq(info->field[1][5], info->moving->figure[1][1]);
  ck_assert_int_ne(info->field[0][4], info->moving->figure[1][1]);

  destroy_game_info();
}
END_TEST

START_TEST(shift_left_test_2) {
  char *user_name = (char *)malloc(sizeof(char) * 5);
  strcpy(user_name, "igor");
  GameInfo_t *info = init_game_info_tetris(user_name);
  info = current_game_info(info);
  drop_new_tetramino();
  get_next_test(info, 2);
  drop_new_tetramino();
  get_next_test(info, 2);
  shift_down(info);
  shift_down(info);
  shift_down(info);
  info->field[1][1] = 1;
  shift_left(info);
  shift_left(info);
  shift_left(info);
  attach(info);
  ck_assert_int_eq(info->moving->col, 2);
  ck_assert_int_eq(info->field[0][2], info->moving->figure[1][1]);
  ck_assert_int_eq(info->field[1][2], info->moving->figure[1][1]);
  ck_assert_int_eq(info->field[1][3], info->moving->figure[1][1]);
  ck_assert_int_eq(info->field[1][4], info->moving->figure[1][1]);
  ck_assert_int_ne(info->field[1][5], info->moving->figure[1][1]);

  destroy_game_info();
}
END_TEST

START_TEST(shift_left_test_3) {
  char *user_name = (char *)malloc(sizeof(char) * 5);
  strcpy(user_name, "igor");
  GameInfo_t *info = init_game_info_tetris(user_name);
  info = current_game_info(info);
  drop_new_tetramino();
  get_next_test(info, 2);
  drop_new_tetramino();
  get_next_test(info, 2);
  shift_down(info);
  shift_down(info);
  shift_down(info);
  info->field[2][1] = 1;
  shift_left(info);
  shift_left(info);
  shift_left(info);
  attach(info);
  ck_assert_int_eq(info->moving->col, 1);
  ck_assert_int_eq(info->field[0][1], info->moving->figure[1][1]);
  ck_assert_int_eq(info->field[1][1], info->moving->figure[1][1]);
  ck_assert_int_eq(info->field[1][2], info->moving->figure[1][1]);
  ck_assert_int_eq(info->field[1][3], info->moving->figure[1][1]);
  ck_assert_int_ne(info->field[1][4], info->moving->figure[1][1]);

  destroy_game_info();
}
END_TEST

START_TEST(shift_left_test_4) {
  char *user_name = (char *)malloc(sizeof(char) * 5);
  strcpy(user_name, "igor");
  GameInfo_t *info = init_game_info_tetris(user_name);
  info = current_game_info(info);
  drop_new_tetramino();
  get_next_test(info, 2);
  drop_new_tetramino();
  get_next_test(info, 2);
  shift_down(info);
  shift_down(info);
  shift_down(info);
  info->field[2][1] = 1;
  shift_left(info);
  shift_left(info);
  shift_left(info);
  shift_left(info);
  shift_left(info);
  shift_left(info);
  shift_left(info);
  attach(info);
  ck_assert_int_eq(info->moving->col, 0);
  ck_assert_int_eq(info->field[0][0], info->moving->figure[1][1]);
  ck_assert_int_eq(info->field[1][0], info->moving->figure[1][1]);
  ck_assert_int_eq(info->field[1][1], info->moving->figure[1][1]);
  ck_assert_int_eq(info->field[1][2], info->moving->figure[1][1]);
  ck_assert_int_ne(info->field[0][1], info->moving->figure[1][1]);

  destroy_game_info();
}
END_TEST

START_TEST(shift_left_test_5) {
  char *user_name = (char *)malloc(sizeof(char) * 5);
  strcpy(user_name, "igor");
  GameInfo_t *info = init_game_info_tetris(user_name);
  info = current_game_info(info);
  drop_new_tetramino();
  get_next_test(info, 1);
  drop_new_tetramino();
  get_next_test(info, 1);
  rotate_tetramino();
  shift_down(info);
  shift_down(info);
  shift_down(info);
  shift_left(info);
  shift_left(info);
  shift_left(info);
  shift_left(info);
  shift_left(info);
  shift_left(info);
  shift_left(info);
  attach(info);
  ck_assert_int_eq(info->moving->col, -2);
  ck_assert_int_eq(info->field[0][0], info->moving->figure[1][2]);
  ck_assert_int_eq(info->field[1][0], info->moving->figure[1][2]);
  ck_assert_int_eq(info->field[2][0], info->moving->figure[1][2]);
  ck_assert_int_eq(info->field[3][0], info->moving->figure[1][2]);
  ck_assert_int_ne(info->field[1][1], info->moving->figure[1][2]);

  destroy_game_info();
}
END_TEST

START_TEST(drop_down_test_1) {
  char *user_name = (char *)malloc(sizeof(char) * 5);
  strcpy(user_name, "igor");
  GameInfo_t *info = init_game_info_tetris(user_name);
  info = current_game_info(info);
  drop_new_tetramino();
  get_next_test(info, 6);
  drop_new_tetramino();
  get_next_test(info, 6);
  drop_down(info);

  attach(info);
  ck_assert_int_eq(info->moving->row, 18);
  ck_assert_int_eq(info->moving->col, MOVING_INIT_COL);
  ck_assert_int_eq(info->field[18][5], info->moving->figure[1][2]);
  ck_assert_int_eq(info->field[19][4], info->moving->figure[1][2]);
  ck_assert_int_eq(info->field[19][5], info->moving->figure[1][2]);
  ck_assert_int_eq(info->field[19][6], info->moving->figure[1][2]);
  ck_assert_int_ne(info->field[17][4], info->moving->figure[1][2]);

  destroy_game_info();
}
END_TEST

START_TEST(drop_down_test_2) {
  char *user_name = (char *)malloc(sizeof(char) * 5);
  strcpy(user_name, "igor");
  GameInfo_t *info = init_game_info_tetris(user_name);
  info = current_game_info(info);
  drop_new_tetramino();
  get_next_test(info, 6);
  drop_new_tetramino();
  get_next_test(info, 6);
  drop_down(info);
  attach(info);

  drop_new_tetramino();
  get_next_test(info, 6);
  shift_left(info);
  shift_left(info);
  shift_left(info);
  drop_down(info);

  attach(info);
  ck_assert_int_eq(info->moving->row, 18);
  ck_assert_int_eq(info->moving->col, 1);
  ck_assert_int_eq(info->field[18][5], info->moving->figure[1][2]);
  ck_assert_int_eq(info->field[19][4], info->moving->figure[1][2]);
  ck_assert_int_eq(info->field[19][5], info->moving->figure[1][2]);
  ck_assert_int_eq(info->field[19][6], info->moving->figure[1][2]);
  ck_assert_int_ne(info->field[17][4], info->moving->figure[1][2]);

  ck_assert_int_eq(info->field[18][2], info->moving->figure[1][2]);
  ck_assert_int_eq(info->field[19][1], info->moving->figure[1][2]);
  ck_assert_int_eq(info->field[19][2], info->moving->figure[1][2]);
  ck_assert_int_eq(info->field[19][3], info->moving->figure[1][2]);
  ck_assert_int_ne(info->field[19][0], info->moving->figure[1][2]);

  destroy_game_info();
}
END_TEST

START_TEST(drop_down_test_3) {
  char *user_name = (char *)malloc(sizeof(char) * 5);
  strcpy(user_name, "igor");
  GameInfo_t *info = init_game_info_tetris(user_name);
  info = current_game_info(info);
  drop_new_tetramino();
  get_next_test(info, 6);
  drop_new_tetramino();
  get_next_test(info, 6);
  shift_left(info);
  shift_left(info);
  shift_left(info);
  shift_left(info);
  drop_down(info);
  attach(info);

  drop_new_tetramino();
  get_next_test(info, 6);
  shift_left(info);
  drop_down(info);
  attach(info);

  drop_new_tetramino();
  get_next_test(info, 6);
  shift_right(info);
  shift_right(info);
  drop_down(info);
  attach(info);

  ck_assert_int_eq(info->moving->row, 18);
  ck_assert_int_eq(info->moving->col, 6);
  for (int i = 0; i < 9; i++) {
    ck_assert_int_eq(info->field[19][i], info->moving->figure[1][1]);
  }
  ck_assert_int_eq(info->field[18][1], info->moving->figure[1][1]);
  ck_assert_int_eq(info->field[18][4], info->moving->figure[1][1]);
  ck_assert_int_ne(info->field[18][0], info->moving->figure[1][1]);

  ck_assert_int_eq(info->field[18][7], info->moving->figure[1][1]);
  ck_assert_int_ne(info->field[18][3], info->moving->figure[1][1]);

  destroy_game_info();
}
END_TEST

START_TEST(drop_down_test_4) {
  char *user_name = (char *)malloc(sizeof(char) * 5);
  strcpy(user_name, "igor");
  GameInfo_t *info = init_game_info_tetris(user_name);
  info = current_game_info(info);
  drop_new_tetramino();
  get_next_test(info, 2);
  drop_new_tetramino();
  get_next_test(info, 2);
  shift_left(info);
  shift_left(info);
  shift_left(info);
  drop_down(info);
  attach(info);

  ck_assert_int_eq(info->moving->row, 18);
  ck_assert_int_eq(info->moving->col, 1);

  drop_new_tetramino();
  get_next_test(info, 2);
  rotate_tetramino();
  shift_left(info);
  shift_left(info);
  shift_left(info);
  shift_left(info);
  shift_left(info);
  shift_left(info);
  drop_down(info);
  attach(info);

  ck_assert_int_eq(info->moving->row, 17);
  ck_assert_int_eq(info->moving->col, -1);

  ck_assert_int_eq(info->field[17][0], info->moving->figure[1][1]);
  ck_assert_int_eq(info->field[17][1], info->moving->figure[1][1]);
  ck_assert_int_eq(info->field[18][0], info->moving->figure[1][1]);
  ck_assert_int_eq(info->field[18][1], info->moving->figure[1][1]);
  ck_assert_int_eq(info->field[19][0], info->moving->figure[1][1]);
  ck_assert_int_eq(info->field[19][1], info->moving->figure[1][1]);
  ck_assert_int_eq(info->field[19][2], info->moving->figure[1][1]);
  ck_assert_int_eq(info->field[19][3], info->moving->figure[1][1]);
  ck_assert_int_ne(info->field[17][2], info->moving->figure[1][1]);
  ck_assert_int_ne(info->field[17][3], info->moving->figure[1][1]);
  ck_assert_int_ne(info->field[18][2], info->moving->figure[1][1]);
  ck_assert_int_ne(info->field[18][3], info->moving->figure[1][1]);

  destroy_game_info();
}
END_TEST

START_TEST(drop_down_test_5) {
  char *user_name = (char *)malloc(sizeof(char) * 5);
  strcpy(user_name, "igor");
  GameInfo_t *info = init_game_info_tetris(user_name);
  info = current_game_info(info);
  drop_new_tetramino();
  get_next_test(info, 2);
  drop_new_tetramino();
  get_next_test(info, 2);
  drop_down(info);
  attach(info);

  drop_new_tetramino();
  get_next_test(info, 2);
  shift_right(info);
  drop_down(info);
  attach(info);

  ck_assert_int_eq(info->moving->row, 17);
  ck_assert_int_eq(info->moving->col, 5);

  ck_assert_int_eq(info->field[18][4], info->moving->figure[1][1]);
  ck_assert_int_eq(info->field[19][4], info->moving->figure[1][1]);
  ck_assert_int_eq(info->field[19][5], info->moving->figure[1][1]);
  ck_assert_int_eq(info->field[19][6], info->moving->figure[1][1]);
  ck_assert_int_eq(info->field[18][5], info->moving->figure[1][1]);
  ck_assert_int_eq(info->field[18][6], info->moving->figure[1][1]);
  ck_assert_int_eq(info->field[18][7], info->moving->figure[1][1]);
  ck_assert_int_eq(info->field[17][5], info->moving->figure[1][1]);
  ck_assert_int_ne(info->field[17][4], info->moving->figure[1][1]);
  ck_assert_int_ne(info->field[19][7], info->moving->figure[1][1]);
  ck_assert_int_ne(info->field[18][8], info->moving->figure[1][1]);
  ck_assert_int_ne(info->field[17][6], info->moving->figure[1][1]);

  destroy_game_info();
}
END_TEST

START_TEST(drop_down_test_6) {
  char *user_name = (char *)malloc(sizeof(char) * 5);
  strcpy(user_name, "igor");
  GameInfo_t *info = init_game_info_tetris(user_name);
  info = current_game_info(info);
  drop_new_tetramino();
  get_next_test(info, 5);
  drop_new_tetramino();
  get_next_test(info, 1);
  shift_left(info);
  shift_left(info);
  shift_left(info);
  shift_left(info);
  drop_down(info);
  attach(info);

  drop_new_tetramino();
  get_next_test(info, 2);
  shift_left(info);
  drop_down(info);
  attach(info);

  ck_assert_int_eq(info->field[19][0], 5);
  ck_assert_int_eq(info->field[19][1], 5);
  ck_assert_int_ne(info->field[19][2], 5);
  ck_assert_int_ne(info->field[18][0], 5);
  ck_assert_int_eq(info->field[18][1], 5);
  ck_assert_int_eq(info->field[18][2], 5);
  ck_assert_int_eq(info->field[19][3], info->moving->figure[1][1]);
  ck_assert_int_eq(info->field[19][4], info->moving->figure[1][1]);
  ck_assert_int_eq(info->field[19][5], info->moving->figure[1][1]);
  ck_assert_int_eq(info->field[19][6], info->moving->figure[1][1]);

  destroy_game_info();
}
END_TEST

START_TEST(game_over_test_1) {
  char *user_name = (char *)malloc(sizeof(char) * 5);
  strcpy(user_name, "igor");
  GameInfo_t *info = init_game_info_tetris(user_name);
  info = current_game_info(info);
  drop_new_tetramino();
  get_next_test(info, 2);
  drop_new_tetramino();
  get_next_test(info, 2);
  rotate_tetramino();
  drop_down(info);
  attach(info);

  drop_new_tetramino();
  get_next_test(info, 2);
  rotate_tetramino();
  drop_down(info);
  attach(info);

  drop_new_tetramino();
  get_next_test(info, 2);
  rotate_tetramino();
  drop_down(info);
  attach(info);

  drop_new_tetramino();
  get_next_test(info, 2);
  rotate_tetramino();
  drop_down(info);
  attach(info);

  drop_new_tetramino();
  get_next_test(info, 2);
  rotate_tetramino();
  drop_down(info);
  attach(info);

  drop_new_tetramino();
  get_next_test(info, 2);
  rotate_tetramino();
  drop_down(info);
  attach(info);

  ck_assert_int_eq(info->moving->row, 2);
  ck_assert_int_eq(info->moving->col, MOVING_INIT_COL);

  drop_new_tetramino();
  get_next_test(info, 2);
  drop_down(info);
  attach(info);

  ck_assert_int_eq(info->moving->row, 0);
  ck_assert_int_eq(info->moving->col, MOVING_INIT_COL);

  ck_assert_int_eq(info->field[0][4], info->moving->figure[1][1]);
  ck_assert_int_eq(info->field[2][5], info->moving->figure[1][1]);
  ck_assert_int_eq(info->field[2][6], info->moving->figure[1][1]);
  ck_assert_int_eq(info->field[3][5], info->moving->figure[1][1]);
  ck_assert_int_eq(info->field[5][5], info->moving->figure[1][1]);
  ck_assert_int_eq(info->field[5][6], info->moving->figure[1][1]);
  ck_assert_int_eq(info->field[6][5], info->moving->figure[1][1]);
  ck_assert_int_ne(info->field[6][6], info->moving->figure[1][1]);
  ck_assert_int_ne(info->field[7][6], info->moving->figure[1][1]);
  ck_assert_int_ne(info->field[2][4], info->moving->figure[1][1]);

  ck_assert_int_eq(check_ceiling(info), 1);

  destroy_game_info();
}
END_TEST

START_TEST(bottom_filling_test_1) {
  char *user_name = (char *)malloc(sizeof(char) * 5);
  strcpy(user_name, "igor");
  GameInfo_t *info = init_game_info_tetris(user_name);
  info = current_game_info(info);
  drop_new_tetramino();
  get_next_test(info, 2);
  drop_new_tetramino();
  get_next_test(info, 2);
  shift_left(info);
  shift_left(info);
  shift_left(info);
  drop_down(info);
  attach(info);

  drop_new_tetramino();
  get_next_test(info, 2);
  rotate_tetramino();
  shift_left(info);
  shift_left(info);
  shift_left(info);
  shift_left(info);
  shift_left(info);
  shift_left(info);
  drop_down(info);
  attach(info);

  drop_new_tetramino();
  get_next_test(info, 2);
  drop_down(info);
  attach(info);

  drop_new_tetramino();
  get_next_test(info, 2);
  shift_right(info);
  shift_right(info);
  shift_right(info);
  drop_down(info);
  attach(info);

  ck_assert_int_eq(info->moving->row, 18);
  ck_assert_int_eq(info->moving->col, 7);

  for (int i = 0; i < FIELD_COLUMNS; i++) {
    ck_assert_int_eq(info->field[FIELD_ROWS - 1][i], 2);
  }

  ck_assert_int_eq(count_filled_rows(info), 1);
  move_field_down(info);
  ck_assert_int_eq(count_filled_rows(info), 0);
  ck_assert_int_eq(info->field[19][1], info->moving->figure[1][1]);
  ck_assert_int_eq(info->field[19][0], info->moving->figure[1][1]);
  ck_assert_int_eq(info->field[18][0], info->moving->figure[1][1]);
  ck_assert_int_eq(info->field[18][1], info->moving->figure[1][1]);
  ck_assert_int_eq(info->field[19][4], info->moving->figure[1][1]);
  ck_assert_int_ne(info->field[19][2], info->moving->figure[1][1]);
  ck_assert_int_eq(info->field[19][7], info->moving->figure[1][1]);
  ck_assert_int_ne(info->field[19][8], info->moving->figure[1][1]);

  destroy_game_info();
}
END_TEST

Suite *tetris_field_test_suite() {
  Suite *s;
  TCase *tc;

  s = suite_create("tetris_field_test_suite");
  tc = tcase_create("tetris_field_test_case");

  tcase_add_test(tc, shift_down_test_1);
  tcase_add_test(tc, shift_down_test_2);

  tcase_add_test(tc, shift_right_test_1);
  tcase_add_test(tc, shift_right_test_2);
  tcase_add_test(tc, shift_right_test_3);
  tcase_add_test(tc, shift_right_test_4);
  tcase_add_test(tc, shift_right_test_5);

  tcase_add_test(tc, shift_left_test_1);
  tcase_add_test(tc, shift_left_test_2);
  tcase_add_test(tc, shift_left_test_3);
  tcase_add_test(tc, shift_left_test_4);
  tcase_add_test(tc, shift_left_test_5);

  tcase_add_test(tc, drop_down_test_1);
  tcase_add_test(tc, drop_down_test_2);
  tcase_add_test(tc, drop_down_test_3);
  tcase_add_test(tc, drop_down_test_4);
  tcase_add_test(tc, drop_down_test_5);
  tcase_add_test(tc, drop_down_test_6);

  tcase_add_test(tc, game_over_test_1);
  tcase_add_test(tc, bottom_filling_test_1);

  suite_add_tcase(s, tc);

  return s;
}