#include "tetris_suites.h"

void get_next_test(GameInfo_t *info, int i) {
  info->next = get_tetramino(i);
  info->next_idx = i;
}

void fill_bottom_test(GameInfo_t *info) {
  drop_new_tetramino();
  get_next_test(info, 1);
  drop_new_tetramino();
  get_next_test(info, 1);
  drop_down(info);
  attach(info);

  drop_new_tetramino();
  get_next_test(info, 4);
  shift_left(info);
  shift_left(info);
  shift_left(info);
  shift_left(info);
  drop_down(info);
  attach(info);

  drop_new_tetramino();
  get_next_test(info, 4);
  shift_right(info);
  shift_right(info);
  shift_right(info);
  shift_right(info);
  drop_down(info);
  attach(info);
}

START_TEST(load_existing_record_test) {
  int record_correct = 200;
  char *user_name = (char *)malloc(sizeof(char) * 6);
  strcpy(user_name, "serge");
  update_user_record(user_name, record_correct, TETRIS_ID);
  int record_from_file = load_user_record(user_name, TETRIS_ID);
  ck_assert_int_eq(record_correct, record_from_file);
  free(user_name);
}
END_TEST

START_TEST(load_non_existing_record_test) {
  int record_correct = 0;
  char *user_name = (char *)malloc(sizeof(char) * 7);
  strcpy(user_name, "kirill");
  int record_from_file = load_user_record(user_name, TETRIS_ID);
  ck_assert_int_eq(record_correct, record_from_file);
  free(user_name);
}
END_TEST

START_TEST(update_record_test) {
  char *user_name = (char *)malloc(sizeof(char) * 6);
  strcpy(user_name, "pavel");
  GameInfo_t *info = init_game_info_tetris(user_name);
  info = current_game_info(info);
  int new_record = info->high_score + 10;
  update_user_record(info->user_name, new_record, TETRIS_ID);
  int record_from_file = load_user_record(info->user_name, TETRIS_ID);
  ck_assert_int_eq(new_record, record_from_file);
  destroy_game_info();
}
END_TEST

START_TEST(rotate_test_1) {
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
  info->field[2][4] = 1;
  rotate_tetramino();

  attach(info);
  ck_assert_int_eq(info->moving->row, 0);
  ck_assert_int_eq(info->moving->col, 4);
  ck_assert_int_eq(info->field[0][5], info->moving->figure[1][1]);
  ck_assert_int_eq(info->field[0][6], info->moving->figure[1][1]);
  ck_assert_int_eq(info->field[1][5], info->moving->figure[1][1]);
  ck_assert_int_eq(info->field[2][5], info->moving->figure[1][1]);
  ck_assert_int_ne(info->field[0][4], info->moving->figure[1][1]);
  ck_assert_int_ne(info->field[1][4], info->moving->figure[1][1]);

  destroy_game_info();
}
END_TEST

START_TEST(rotate_test_2) {
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
  info->field[2][5] = 1;
  rotate_tetramino();

  attach(info);
  ck_assert_int_eq(info->moving->row, 0);
  ck_assert_int_eq(info->moving->col, MOVING_INIT_COL);
  ck_assert_int_eq(info->field[0][4], info->moving->figure[1][1]);
  ck_assert_int_eq(info->field[1][4], info->moving->figure[1][1]);
  ck_assert_int_eq(info->field[1][5], info->moving->figure[1][1]);
  ck_assert_int_eq(info->field[1][6], info->moving->figure[1][1]);
  ck_assert_int_ne(info->field[0][5], info->moving->figure[1][1]);
  ck_assert_int_ne(info->field[0][6], info->moving->figure[1][1]);

  destroy_game_info();
}
END_TEST

START_TEST(rotate_test_3) {
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
  info->field[2][4] = 1;
  rotate_tetramino();
  rotate_tetramino();
  rotate_tetramino();

  attach(info);
  ck_assert_int_eq(info->moving->row, 0);
  ck_assert_int_eq(info->moving->col, MOVING_INIT_COL);
  ck_assert_int_eq(info->field[1][4], info->moving->figure[1][1]);
  ck_assert_int_eq(info->field[1][5], info->moving->figure[1][1]);
  ck_assert_int_eq(info->field[1][6], info->moving->figure[1][1]);
  ck_assert_int_eq(info->field[2][6], info->moving->figure[1][1]);
  ck_assert_int_ne(info->field[2][5], info->moving->figure[1][1]);
  ck_assert_int_ne(info->field[0][5], info->moving->figure[1][1]);

  destroy_game_info();
}
END_TEST

START_TEST(rotate_test_at_the_bottom) {
  char *user_name = (char *)malloc(sizeof(char) * 5);
  strcpy(user_name, "igor");
  GameInfo_t *info = init_game_info_tetris(user_name);
  info = current_game_info(info);
  drop_new_tetramino();
  get_next_test(info, 2);
  drop_new_tetramino();
  get_next_test(info, 2);
  drop_down(info);
  rotate_tetramino();

  attach(info);
  ck_assert_int_eq(info->moving->row, 18);
  ck_assert_int_eq(info->moving->col, MOVING_INIT_COL);
  ck_assert_int_eq(info->field[18][4], info->moving->figure[1][1]);
  ck_assert_int_eq(info->field[19][4], info->moving->figure[1][1]);
  ck_assert_int_eq(info->field[19][5], info->moving->figure[1][1]);
  ck_assert_int_eq(info->field[19][6], info->moving->figure[1][1]);
  ck_assert_int_ne(info->field[18][6], info->moving->figure[1][1]);
  ck_assert_int_ne(info->field[17][6], info->moving->figure[1][1]);

  destroy_game_info();
}
END_TEST

START_TEST(rotate_test_in_buffer) {
  char *user_name = (char *)malloc(sizeof(char) * 5);
  strcpy(user_name, "igor");
  GameInfo_t *info = init_game_info_tetris(user_name);
  info = current_game_info(info);
  drop_new_tetramino();
  get_next_test(info, 2);
  drop_new_tetramino();
  get_next_test(info, 2);
  rotate_tetramino();
  shift_down(info);
  shift_down(info);
  shift_down(info);

  attach(info);
  ck_assert_int_eq(info->moving->row, 0);
  ck_assert_int_eq(info->moving->col, MOVING_INIT_COL);
  ck_assert_int_eq(info->field[0][5], info->moving->figure[1][1]);
  ck_assert_int_eq(info->field[0][6], info->moving->figure[1][1]);
  ck_assert_int_eq(info->field[1][5], info->moving->figure[1][1]);
  ck_assert_int_eq(info->field[2][5], info->moving->figure[1][1]);
  ck_assert_int_ne(info->field[0][4], info->moving->figure[1][1]);
  ck_assert_int_ne(info->field[1][4], info->moving->figure[1][1]);

  destroy_game_info();
}
END_TEST

START_TEST(rotate_test_left_border) {
  char *user_name = (char *)malloc(sizeof(char) * 5);
  strcpy(user_name, "igor");
  GameInfo_t *info = init_game_info_tetris(user_name);
  info = current_game_info(info);
  drop_new_tetramino();
  get_next_test(info, 1);
  drop_new_tetramino();
  get_next_test(info, 1);
  shift_down(info);
  shift_down(info);
  shift_down(info);
  rotate_tetramino();

  shift_left(info);
  shift_left(info);
  shift_left(info);
  shift_left(info);
  shift_left(info);
  shift_left(info);
  shift_left(info);

  attach(info);
  ck_assert_int_eq(info->moving->row, 0);
  ck_assert_int_eq(info->moving->col, -2);
  ck_assert_int_eq(info->field[0][0], info->moving->figure[1][2]);
  ck_assert_int_eq(info->field[1][0], info->moving->figure[1][2]);
  ck_assert_int_eq(info->field[2][0], info->moving->figure[1][2]);
  ck_assert_int_eq(info->field[3][0], info->moving->figure[1][2]);
  ck_assert_int_ne(info->field[1][1], info->moving->figure[1][2]);
  ck_assert_int_ne(info->field[2][1], info->moving->figure[1][2]);

  destroy_game_info();
}
END_TEST

START_TEST(rotate_test_right_border) {
  char *user_name = (char *)malloc(sizeof(char) * 5);
  strcpy(user_name, "igor");
  GameInfo_t *info = init_game_info_tetris(user_name);
  info = current_game_info(info);
  drop_new_tetramino();
  get_next_test(info, 1);
  drop_new_tetramino();
  get_next_test(info, 1);
  shift_down(info);
  shift_down(info);
  shift_down(info);
  rotate_tetramino();
  rotate_tetramino();
  rotate_tetramino();

  shift_right(info);
  shift_right(info);
  shift_right(info);
  shift_right(info);
  shift_right(info);

  attach(info);
  ck_assert_int_eq(info->moving->row, 0);
  ck_assert_int_eq(info->moving->col, 8);
  ck_assert_int_eq(info->field[0][9], info->moving->figure[1][1]);
  ck_assert_int_eq(info->field[1][9], info->moving->figure[1][1]);
  ck_assert_int_eq(info->field[2][9], info->moving->figure[1][1]);
  ck_assert_int_eq(info->field[3][9], info->moving->figure[1][1]);
  ck_assert_int_ne(info->field[2][8], info->moving->figure[1][1]);
  ck_assert_int_ne(info->field[1][8], info->moving->figure[1][1]);

  destroy_game_info();
}
END_TEST

START_TEST(add_points_test_1) {
  char *user_name = (char *)malloc(sizeof(char) * 5);
  strcpy(user_name, "igor");
  GameInfo_t *info = init_game_info_tetris(user_name);
  info = current_game_info(info);

  for (int i = FIELD_ROWS - 6; i < FIELD_ROWS; i++) {
    for (int j = 0; j < FIELD_ROWS; j++) {
      info->field[i][j] = 1;
    }
  }
  info->field[FIELD_ROWS - 7][1] = 1;
  info->field[FIELD_ROWS - 7][2] = 1;
  info->field[FIELD_ROWS - 7][10] = 1;
  info->field[FIELD_ROWS - 8][3] = 1;

  add_points(count_filled_rows(info));
  ck_assert_int_eq(info->score, 1800);
  int filled_rows = count_filled_rows(info);
  for (int i = 0; i < filled_rows; i++) {
    move_field_down(info);
  }
  ck_assert_int_eq(count_filled_rows(info), 0);
  ck_assert_int_eq(info->field[FIELD_ROWS - 1][1], 1);
  ck_assert_int_eq(info->field[FIELD_ROWS - 1][2], 1);
  ck_assert_int_eq(info->field[FIELD_ROWS - 1][10], 1);
  ck_assert_int_eq(info->field[FIELD_ROWS - 2][3], 1);

  change_level();
  update_user_record((char *)"igor", info->score, TETRIS_ID);
  ck_assert_int_eq(info->level, 4);

  destroy_game_info();
}
END_TEST

START_TEST(fsm_test_1) {
  StateMachine_tetris *machine = current_state_machine(NULL);
  ck_assert_ptr_null(machine);
  StateMachine_tetris *mem = init_state_machine_tetris();
  machine = current_state_machine(mem);
  ck_assert_ptr_nonnull(machine);
  destroy_state_machine();
}
END_TEST

START_TEST(delay_test_1) {
  char *user_name = (char *)malloc(sizeof(char) * 5);
  strcpy(user_name, "igor");
  GameInfo_t *info = init_game_info_tetris(user_name);
  info = current_game_info(info);

  get_tick_limit();
  usleep(750000);
  ck_assert_int_eq(check_tick_limit(), 1);

  destroy_game_info();
}
END_TEST

START_TEST(delay_test_2) {
  char *user_name = (char *)malloc(sizeof(char) * 5);
  strcpy(user_name, "igor");
  GameInfo_t *info = init_game_info_tetris(user_name);
  info = current_game_info(info);

  get_tick_limit();
  usleep(850000);
  ck_assert_int_eq(check_tick_limit(), 0);

  destroy_game_info();
}
END_TEST

START_TEST(handle_bottom_filling_test_1) {
  char *user_name = (char *)malloc(sizeof(char) * 5);
  strcpy(user_name, "igor");
  GameInfo_t *info = init_game_info_tetris(user_name);
  info = current_game_info(info);
  fill_bottom_test(info);

  handle_bottom_filling();
  ck_assert_int_eq(info->level, 1);
  ck_assert_int_eq(info->score, 100);

  destroy_game_info();
}
END_TEST

START_TEST(handle_bottom_filling_test_2) {
  char *user_name = (char *)malloc(sizeof(char) * 5);
  strcpy(user_name, "igor");
  GameInfo_t *info = init_game_info_tetris(user_name);
  info = current_game_info(info);
  fill_bottom_test(info);
  fill_bottom_test(info);
  fill_bottom_test(info);
  fill_bottom_test(info);
  fill_bottom_test(info);
  fill_bottom_test(info);
  fill_bottom_test(info);

  handle_bottom_filling();
  ck_assert_int_eq(info->level, 4);
  ck_assert_int_eq(info->score, 2200);

  destroy_game_info();
}
END_TEST

START_TEST(clear_game_info_test) {
  char *user_name = (char *)malloc(sizeof(char) * 5);
  strcpy(user_name, "igor");
  GameInfo_t *info = init_game_info_tetris(user_name);
  info = current_game_info(info);
  fill_bottom_test(info);

  clear_game_info_tetris();

  ck_assert_int_eq(updateCurrentState().level, 1);
  ck_assert_int_eq(updateCurrentState().score, 0);
  ck_assert_int_eq(updateCurrentState().field[FIELD_ROWS - 1][9], 0);
  ck_assert_int_eq(updateCurrentState().moving->idx, 1);
  ck_assert_ptr_eq(updateCurrentState().bottom_text, NULL);

  destroy_game_info();
}
END_TEST

Suite *tetris_backend_test_suite() {
  Suite *s;
  TCase *tc;

  s = suite_create("tetris_backend_test_suite");
  tc = tcase_create("tetris_backend_test_case");

  tcase_add_test(tc, load_existing_record_test);
  tcase_add_test(tc, load_non_existing_record_test);
  tcase_add_test(tc, update_record_test);
  tcase_add_test(tc, rotate_test_1);
  tcase_add_test(tc, rotate_test_2);
  tcase_add_test(tc, rotate_test_3);
  tcase_add_test(tc, rotate_test_left_border);
  tcase_add_test(tc, rotate_test_right_border);
  tcase_add_test(tc, rotate_test_in_buffer);
  tcase_add_test(tc, rotate_test_at_the_bottom);
  tcase_add_test(tc, add_points_test_1);
  tcase_add_test(tc, fsm_test_1);
  tcase_add_test(tc, delay_test_1);
  tcase_add_test(tc, delay_test_2);
  tcase_add_test(tc, handle_bottom_filling_test_1);
  tcase_add_test(tc, handle_bottom_filling_test_2);
  tcase_add_test(tc, clear_game_info_test);

  suite_add_tcase(s, tc);

  return s;
}
