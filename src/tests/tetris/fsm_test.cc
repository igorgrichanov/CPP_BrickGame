#include "tetris_suites.h"

START_TEST(user_input_start_test_1) {
  current_state_machine(init_state_machine_tetris());
  char *user_name = (char *)malloc(sizeof(char) * 5);
  strcpy(user_name, "igor");
  GameInfo_t *info = init_game_info_tetris(user_name);
  current_game_info(info);
  user_input(START);
  ck_assert_int_eq(1, *current_state_machine(NULL) == MOVING_STATE);
  ck_assert_ptr_eq(updateCurrentState().bottom_text, NULL);

  destroy_state_machine();
  destroy_game_info();
}
END_TEST

START_TEST(user_input_start_test_2) {
  StateMachine_tetris *state =
      current_state_machine(init_state_machine_tetris());
  char *user_name = (char *)malloc(sizeof(char) * 5);
  strcpy(user_name, "igor");
  GameInfo_t *info = init_game_info_tetris(user_name);
  current_game_info(info);
  *state = GAME_OVER_STATE;
  user_input(START);
  ck_assert_int_eq(1, *current_state_machine(NULL) == START_STATE);
  ck_assert_ptr_ne(updateCurrentState().bottom_text, NULL);

  destroy_state_machine();
  destroy_game_info();
}
END_TEST

START_TEST(user_input_start_test_3) {
  current_state_machine(init_state_machine_tetris());
  char *user_name = (char *)malloc(sizeof(char) * 5);
  strcpy(user_name, "igor");
  GameInfo_t *info = init_game_info_tetris(user_name);
  current_game_info(info);
  user_input(START);
  user_input(START);
  ck_assert_int_eq(1, *current_state_machine(NULL) == MOVING_STATE);

  destroy_state_machine();
  destroy_game_info();
}
END_TEST

START_TEST(user_input_pause_test_1) {
  current_state_machine(init_state_machine_tetris());
  char *user_name = (char *)malloc(sizeof(char) * 5);
  strcpy(user_name, "igor");
  GameInfo_t *info = init_game_info_tetris(user_name);
  current_game_info(info);

  user_input(START);

  user_input(PAUSE);
  ck_assert_int_eq(1, *current_state_machine(NULL) == PAUSE_STATE);
  ck_assert_int_eq(updateCurrentState().pause == true, 1);
  ck_assert_int_eq('P', updateCurrentState().field[Y_WIN][3]);

  user_input(PAUSE);
  ck_assert_int_eq(1, *current_state_machine(NULL) == MOVING_STATE);
  ck_assert_int_eq(updateCurrentState().pause == false, 1);
  ck_assert_ptr_eq(updateCurrentState().bottom_text, NULL);

  destroy_state_machine();
  destroy_game_info();
}
END_TEST

START_TEST(user_input_pause_test_2) {
  StateMachine_tetris *state =
      current_state_machine(init_state_machine_tetris());
  char *user_name = (char *)malloc(sizeof(char) * 5);
  strcpy(user_name, "igor");
  GameInfo_t *info = init_game_info_tetris(user_name);
  current_game_info(info);

  *state = PAUSE_STATE;
  user_input(DOWN);
  ck_assert_int_eq(1, *current_state_machine(NULL) == PAUSE_STATE);

  destroy_state_machine();
  destroy_game_info();
}
END_TEST

START_TEST(user_input_terminate_test_1) {
  StateMachine_tetris *state =
      current_state_machine(init_state_machine_tetris());
  *state = START_STATE;

  char *user_name = (char *)malloc(sizeof(char) * 5);
  strcpy(user_name, "igor");
  GameInfo_t *info = init_game_info_tetris(user_name);
  info = current_game_info(info);

  user_input(TERMINATE);
  ck_assert_int_eq(1, *state == EXIT_STATE);
  ck_assert_int_eq(updateCurrentState().score, -1);

  destroy_state_machine();
  destroy_game_info();
}
END_TEST

START_TEST(user_input_terminate_test_2) {
  StateMachine_tetris *state =
      current_state_machine(init_state_machine_tetris());
  *state = PAUSE_STATE;
  char *user_name = (char *)malloc(sizeof(char) * 5);
  strcpy(user_name, "igor");
  GameInfo_t *info = init_game_info_tetris(user_name);
  info = current_game_info(info);
  user_input(TERMINATE);
  ck_assert_int_eq(1, *current_state_machine(NULL) == PAUSE_STATE);
  ck_assert_int_ne(updateCurrentState().score, -1);

  destroy_state_machine();
  destroy_game_info();
}
END_TEST

START_TEST(user_input_terminate_test_3) {
  StateMachine_tetris *state =
      current_state_machine(init_state_machine_tetris());
  *state = MOVING_STATE;
  char *user_name = (char *)malloc(sizeof(char) * 5);
  strcpy(user_name, "igor");
  GameInfo_t *info = init_game_info_tetris(user_name);
  info = current_game_info(info);
  user_input(TERMINATE);
  ck_assert_int_eq(1, *current_state_machine(NULL) == START_STATE);
  ck_assert_int_eq(updateCurrentState().score, 0);
  ck_assert_int_eq(updateCurrentState().game_over == false, 1);
  ck_assert_ptr_ne(updateCurrentState().bottom_text, NULL);

  destroy_state_machine();
  destroy_game_info();
}
END_TEST

START_TEST(timer_expired_test_1) {
  current_state_machine(init_state_machine_tetris());
  char *user_name = (char *)malloc(sizeof(char) * 5);
  strcpy(user_name, "igor");
  GameInfo_t *info = init_game_info_tetris(user_name);
  info = current_game_info(info);
  user_input(START);

  drop_new_tetramino();
  get_next_test(info, 1);
  drop_new_tetramino();
  get_next_test(info, 1);
  user_input(LEFT);

  moving_timer_has_expired();
  ck_assert_int_eq(1, *current_state_machine(NULL) == MOVING_STATE);
  ck_assert_int_eq(info->moving->row, MOVING_INIT_ROW + 1);
  ck_assert_int_eq(info->moving->col, MOVING_INIT_COL - 1);
  ck_assert_ptr_eq(updateCurrentState().bottom_text, NULL);

  destroy_state_machine();
  destroy_game_info();
}
END_TEST

START_TEST(timer_expired_test_2) {
  current_state_machine(init_state_machine_tetris());
  char *user_name = (char *)malloc(sizeof(char) * 5);
  strcpy(user_name, "igor");
  GameInfo_t *info = init_game_info_tetris(user_name);
  info = current_game_info(info);
  user_input(START);

  drop_new_tetramino();
  get_next_test(info, 1);
  drop_new_tetramino();
  get_next_test(info, 1);
  user_input(LEFT);
  drop_down(info);

  moving_timer_has_expired();
  ck_assert_int_eq(1, *current_state_machine(NULL) == MOVING_STATE);
  ck_assert_int_eq(info->moving->row, MOVING_INIT_ROW);
  ck_assert_int_eq(info->moving->col, MOVING_INIT_COL);
  ck_assert_int_eq(info->field[19][MOVING_INIT_COL - 1], 1);
  ck_assert_int_eq(info->field[19][MOVING_INIT_COL + 2], 1);
  ck_assert_int_ne(info->field[19][MOVING_INIT_COL + 3], 1);
  ck_assert_ptr_eq(updateCurrentState().bottom_text, NULL);

  destroy_state_machine();
  destroy_game_info();
}
END_TEST

START_TEST(timer_expired_test_3) {
  current_state_machine(init_state_machine_tetris());
  char *user_name = (char *)malloc(sizeof(char) * 5);
  strcpy(user_name, "igor");
  GameInfo_t *info = init_game_info_tetris(user_name);
  info = current_game_info(info);

  user_input(START);
  drop_new_tetramino();
  get_next_test(info, 1);
  drop_new_tetramino();
  get_next_test(info, 1);
  moving_timer_has_expired();
  moving_timer_has_expired();
  moving_timer_has_expired();
  ck_assert_int_eq(info->moving->row, MOVING_INIT_ROW + 3);
  attach(info);

  drop_new_tetramino();
  get_next_test(info, 1);
  drop_new_tetramino();
  get_next_test(info, 1);
  moving_timer_has_expired();
  moving_timer_has_expired();
  ck_assert_int_eq(1, *current_state_machine(NULL) == MOVING_STATE);
  moving_timer_has_expired();

  ck_assert_int_eq(1, *current_state_machine(NULL) == GAME_OVER_STATE);
  ck_assert_int_eq(info->moving->row, -1);
  ck_assert_int_eq(info->moving->col, MOVING_INIT_COL);
  ck_assert_int_eq(info->field[0][MOVING_INIT_COL], 0);
  ck_assert_int_eq(info->field[0][MOVING_INIT_COL + 2], 0);
  ck_assert_int_eq(info->field[19][MOVING_INIT_COL + 3], 0);
  ck_assert_int_eq(1, info->game_over == true);
  ck_assert_ptr_ne(updateCurrentState().bottom_text, NULL);

  destroy_state_machine();
  destroy_game_info();
}
END_TEST

START_TEST(user_input_left_test_1) {
  current_state_machine(init_state_machine_tetris());

  char *user_name = (char *)malloc(sizeof(char) * 5);
  strcpy(user_name, "igor");
  GameInfo_t *info = init_game_info_tetris(user_name);
  info = current_game_info(info);
  user_input(START);

  drop_new_tetramino();
  get_next_test(info, 1);
  drop_new_tetramino();
  get_next_test(info, 1);

  user_input(LEFT);
  ck_assert_int_eq(info->moving->row, MOVING_INIT_ROW);
  ck_assert_int_eq(info->moving->col, MOVING_INIT_COL - 1);
  ck_assert_int_eq(1, *current_state_machine(NULL) == MOVING_STATE);

  destroy_state_machine();
  destroy_game_info();
}
END_TEST

START_TEST(user_input_left_test_2) {
  StateMachine_tetris *state =
      current_state_machine(init_state_machine_tetris());
  *state = SHIFTING_STATE;

  char *user_name = (char *)malloc(sizeof(char) * 5);
  strcpy(user_name, "igor");
  GameInfo_t *info = init_game_info_tetris(user_name);
  info = current_game_info(info);

  drop_new_tetramino();
  get_next_test(info, 1);
  drop_new_tetramino();
  get_next_test(info, 1);

  user_input(LEFT);
  ck_assert_int_eq(info->moving->row, MOVING_INIT_ROW);
  ck_assert_int_eq(info->moving->col, MOVING_INIT_COL);
  ck_assert_int_eq(1, *current_state_machine(NULL) == SHIFTING_STATE);

  destroy_state_machine();
  destroy_game_info();
}
END_TEST

START_TEST(user_input_right_test_1) {
  current_state_machine(init_state_machine_tetris());

  char *user_name = (char *)malloc(sizeof(char) * 5);
  strcpy(user_name, "igor");
  GameInfo_t *info = init_game_info_tetris(user_name);
  info = current_game_info(info);
  user_input(START);

  drop_new_tetramino();
  get_next_test(info, 1);
  drop_new_tetramino();
  get_next_test(info, 1);

  user_input(RIGHT);
  ck_assert_int_eq(info->moving->row, MOVING_INIT_ROW);
  ck_assert_int_eq(info->moving->col, MOVING_INIT_COL + 1);
  ck_assert_int_eq(1, *current_state_machine(NULL) == MOVING_STATE);

  destroy_state_machine();
  destroy_game_info();
}
END_TEST

START_TEST(user_input_right_test_2) {
  current_state_machine(init_state_machine_tetris());

  char *user_name = (char *)malloc(sizeof(char) * 5);
  strcpy(user_name, "igor");
  GameInfo_t *info = init_game_info_tetris(user_name);
  info = current_game_info(info);
  user_input(START);

  drop_new_tetramino();
  get_next_test(info, 1);
  drop_new_tetramino();
  get_next_test(info, 1);

  shift_right(info);
  shift_right(info);
  shift_right(info);
  shift_right(info);

  ck_assert_int_eq(info->moving->row, MOVING_INIT_ROW);
  ck_assert_int_eq(info->moving->col, 6);

  user_input(RIGHT);
  ck_assert_int_eq(info->moving->row, MOVING_INIT_ROW);
  ck_assert_int_eq(info->moving->col, 6);
  ck_assert_int_eq(1, *current_state_machine(NULL) == MOVING_STATE);

  destroy_state_machine();
  destroy_game_info();
}
END_TEST

START_TEST(user_input_down_test_1) {
  current_state_machine(init_state_machine_tetris());

  char *user_name = (char *)malloc(sizeof(char) * 5);
  strcpy(user_name, "igor");
  GameInfo_t *info = init_game_info_tetris(user_name);
  info = current_game_info(info);
  user_input(START);

  ck_assert_int_eq(1, *current_state_machine(NULL) == MOVING_STATE);

  drop_new_tetramino();
  get_next_test(info, 1);
  drop_new_tetramino();
  get_next_test(info, 1);

  user_input(DOWN);
  ck_assert_int_eq(info->field[19][MOVING_INIT_COL], 1);
  ck_assert_int_eq(info->field[19][MOVING_INIT_COL + 3], 1);
  ck_assert_int_ne(info->field[19][MOVING_INIT_COL + 4], 1);
  ck_assert_int_eq(1, *current_state_machine(NULL) == MOVING_STATE);

  destroy_state_machine();
  destroy_game_info();
}
END_TEST

START_TEST(user_input_down_test_2) {
  current_state_machine(init_state_machine_tetris());

  char *user_name = (char *)malloc(sizeof(char) * 5);
  strcpy(user_name, "igor");
  GameInfo_t *info = init_game_info_tetris(user_name);
  info = current_game_info(info);
  user_input(START);

  ck_assert_int_eq(1, *current_state_machine(NULL) == MOVING_STATE);

  drop_new_tetramino();
  get_next_test(info, 1);
  drop_new_tetramino();
  get_next_test(info, 1);

  drop_down(info);

  user_input(DOWN);
  ck_assert_int_eq(info->field[19][MOVING_INIT_COL], 1);
  ck_assert_int_eq(info->field[19][MOVING_INIT_COL + 3], 1);
  ck_assert_int_ne(info->field[19][MOVING_INIT_COL + 4], 1);
  ck_assert_int_eq(1, *current_state_machine(NULL) == MOVING_STATE);

  destroy_state_machine();
  destroy_game_info();
}
END_TEST

START_TEST(user_input_action_test_1) {
  current_state_machine(init_state_machine_tetris());

  char *user_name = (char *)malloc(sizeof(char) * 5);
  strcpy(user_name, "igor");
  GameInfo_t *info = init_game_info_tetris(user_name);
  info = current_game_info(info);

  user_input(START);

  drop_new_tetramino();
  get_next_test(info, 1);
  drop_new_tetramino();
  get_next_test(info, 1);

  user_input(ACTION);
  shift_down(info);
  shift_down(info);
  shift_down(info);
  attach(info);
  ck_assert_int_eq(info->moving->row, 0);
  ck_assert_int_eq(info->moving->col, MOVING_INIT_COL);
  ck_assert_int_eq(info->field[0][6], info->moving->figure[1][2]);
  ck_assert_int_eq(info->field[1][6], info->moving->figure[1][2]);
  ck_assert_int_eq(info->field[1][7], info->moving->figure[1][1]);
  ck_assert_int_eq(1, *current_state_machine(NULL) == MOVING_STATE);

  destroy_state_machine();
  destroy_game_info();
}
END_TEST

START_TEST(user_input_action_test_2) {
  current_state_machine(init_state_machine_tetris());

  char *user_name = (char *)malloc(sizeof(char) * 5);
  strcpy(user_name, "igor");
  GameInfo_t *info = init_game_info_tetris(user_name);
  info = current_game_info(info);

  user_input(START);

  drop_new_tetramino();
  get_next_test(info, 1);
  drop_new_tetramino();
  get_next_test(info, 1);

  rotate_tetramino();
  rotate_tetramino();
  rotate_tetramino();
  shift_right(info);
  shift_right(info);
  shift_right(info);
  shift_right(info);
  shift_right(info);
  shift_down(info);
  shift_down(info);
  shift_down(info);
  ck_assert_int_eq(info->moving->row, 0);
  ck_assert_int_eq(info->moving->col, 8);

  brickGame::TetrisController *controller = new brickGame::TetrisController;
  controller->userInput(ACTION);
  ck_assert_int_eq(info->moving->row, 0);
  ck_assert_int_eq(info->moving->col, 8);
  attach(info);
  ck_assert_int_eq(info->field[0][9], info->moving->figure[1][1]);
  ck_assert_int_eq(info->field[1][9], info->moving->figure[1][1]);
  ck_assert_int_eq(info->field[1][8], info->moving->figure[1][2]);
  ck_assert_int_eq(1, *current_state_machine(NULL) == MOVING_STATE);

  delete controller;
  destroy_state_machine();
  destroy_game_info();
}
END_TEST

START_TEST(user_input_up_test_1) {
  StateMachine_tetris *state =
      current_state_machine(init_state_machine_tetris());
  *state = SHIFTING_STATE;

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

  brickGame::TetrisController *controller = new brickGame::TetrisController;
  controller->userInput(UP);
  ck_assert_int_eq(info->moving->row, 0);
  ck_assert_int_eq(info->moving->col, MOVING_INIT_COL);
  attach(info);
  ck_assert_int_eq(info->field[1][4], info->moving->figure[1][1]);
  ck_assert_int_eq(info->field[1][5], info->moving->figure[1][1]);
  ck_assert_int_eq(info->field[0][4], info->moving->figure[0][1]);

  ck_assert_int_eq(1, *current_state_machine(NULL) == SHIFTING_STATE);

  delete controller;
  destroy_state_machine();
  destroy_game_info();
}
END_TEST

Suite *tetris_controller_test_suite() {
  Suite *s;
  TCase *tc;

  s = suite_create("fsm_test_suite");
  tc = tcase_create("fsm_test_case");

  tcase_add_test(tc, user_input_start_test_1);
  tcase_add_test(tc, user_input_start_test_2);
  tcase_add_test(tc, user_input_start_test_3);
  tcase_add_test(tc, user_input_pause_test_1);
  tcase_add_test(tc, user_input_pause_test_2);
  tcase_add_test(tc, user_input_terminate_test_1);
  tcase_add_test(tc, user_input_terminate_test_2);
  tcase_add_test(tc, user_input_terminate_test_3);
  tcase_add_test(tc, timer_expired_test_1);
  tcase_add_test(tc, timer_expired_test_2);
  tcase_add_test(tc, timer_expired_test_3);
  tcase_add_test(tc, user_input_left_test_1);
  tcase_add_test(tc, user_input_left_test_2);
  tcase_add_test(tc, user_input_right_test_1);
  tcase_add_test(tc, user_input_right_test_2);
  tcase_add_test(tc, user_input_down_test_1);
  tcase_add_test(tc, user_input_down_test_2);
  tcase_add_test(tc, user_input_action_test_1);
  tcase_add_test(tc, user_input_action_test_2);
  tcase_add_test(tc, user_input_up_test_1);

  suite_add_tcase(s, tc);

  return s;
}