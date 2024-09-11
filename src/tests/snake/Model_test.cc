#include "test_entry.h"

TEST(SnakeController, test_user_input_start_1) {
  char *user_name = (char *)malloc(sizeof(char) * 6);
  std::strcpy(user_name, "pavel");
  brickGame::Model *m = new brickGame::Model(user_name);
  brickGame::SnakeController c((char *)"pavel", m);

  GameInfo_t *info = current_game_info(NULL);

  c.userInput(START);
  EXPECT_EQ(m->get_state(), brickGame::Model::State::MOVING_STATE);
  EXPECT_EQ(info->bottom_text, nullptr);
}

TEST(SnakeController, test_user_input_start_2) {
  char *user_name = (char *)malloc(sizeof(char) * 6);
  std::strcpy(user_name, "pavel");
  brickGame::Model *m = new brickGame::Model(user_name);
  brickGame::SnakeController c((char *)"pavel", m);

  GameInfo_t *info = current_game_info(NULL);

  c.userInput(ACTION);
  EXPECT_EQ(m->get_state(), brickGame::Model::State::START_STATE);
  c.userInput(UP);
  EXPECT_EQ(m->get_state(), brickGame::Model::State::START_STATE);

  c.userInput(TERMINATE);
  EXPECT_EQ(m->get_state(), brickGame::Model::State::EXIT_STATE);
  EXPECT_EQ(info->score, -1);
}

TEST(SnakeController, test_user_input_moving_opposite) {
  char *user_name = (char *)malloc(sizeof(char) * 6);
  std::strcpy(user_name, "pavel");
  brickGame::Model *m = new brickGame::Model(user_name);
  brickGame::SnakeController c((char *)"pavel", m);

  GameInfo_t *info = current_game_info(NULL);
  c.userInput(START);

  c.userInput(LEFT);
  EXPECT_EQ(m->get_state(), brickGame::Model::State::MOVING_STATE);
  EXPECT_EQ(info->field[SNAKE_DEFAULT_Y][SNAKE_DEFAULT_X], SNAKE_COLOR);
}

TEST(SnakeController, test_user_input_moving_up) {
  char *user_name = (char *)malloc(sizeof(char) * 6);
  std::strcpy(user_name, "pavel");
  brickGame::Model *m = new brickGame::Model(user_name);
  brickGame::SnakeController c((char *)"pavel", m);

  GameInfo_t *info = current_game_info(NULL);
  c.userInput(START);
  c.userInput(UP);

  EXPECT_NE(info->field[SNAKE_DEFAULT_Y][SNAKE_DEFAULT_X], SNAKE_COLOR);
  EXPECT_EQ(info->field[SNAKE_DEFAULT_Y - 1][SNAKE_DEFAULT_X + 3], SNAKE_COLOR);
  EXPECT_EQ(m->get_state(), brickGame::Model::State::MOVING_STATE);

  c.userInput(TERMINATE);
  EXPECT_EQ(m->get_state(), brickGame::Model::State::START_STATE);
  EXPECT_NE(info->bottom_text, nullptr);
}

TEST(SnakeController, test_user_input_moving_terminate) {
  char *user_name = (char *)malloc(sizeof(char) * 6);
  std::strcpy(user_name, "pavel");
  brickGame::Model *m = new brickGame::Model(user_name);
  brickGame::SnakeController c((char *)"pavel", m);

  GameInfo_t *info = current_game_info(NULL);
  c.userInput(START);
  c.userInput(UP);

  c.userInput(TERMINATE);
  EXPECT_EQ(m->get_state(), brickGame::Model::State::START_STATE);
  EXPECT_NE(info->bottom_text, nullptr);
  EXPECT_FALSE(info->game_over);
  EXPECT_EQ(info->field[SNAKE_DEFAULT_Y][SNAKE_DEFAULT_X], 0);
}

TEST(SnakeController, test_user_input_moving_pause) {
  char *user_name = (char *)malloc(sizeof(char) * 6);
  std::strcpy(user_name, "pavel");
  brickGame::Model *m = new brickGame::Model(user_name);
  brickGame::SnakeController c((char *)"pavel", m);

  GameInfo_t *info = current_game_info(NULL);
  c.userInput(START);
  c.userInput(UP);

  c.userInput(PAUSE);
  EXPECT_EQ(m->get_state(), brickGame::Model::State::PAUSE_STATE);
  EXPECT_TRUE(info->pause);
  EXPECT_EQ(info->field[Y_WIN][3], 'P');
  EXPECT_NE(info->field_copy[SNAKE_DEFAULT_Y][SNAKE_DEFAULT_X], SNAKE_COLOR);
  EXPECT_EQ(info->field_copy[SNAKE_DEFAULT_Y - 1][SNAKE_DEFAULT_X + 3],
            SNAKE_COLOR);

  c.userInput(TERMINATE);
  EXPECT_EQ(m->get_state(), brickGame::Model::State::PAUSE_STATE);
  c.userInput(START);
  EXPECT_EQ(m->get_state(), brickGame::Model::State::PAUSE_STATE);
  c.userInput(LEFT);
  EXPECT_EQ(m->get_state(), brickGame::Model::State::PAUSE_STATE);

  c.userInput(PAUSE);
  EXPECT_EQ(info->field_copy[SNAKE_DEFAULT_Y - 1][SNAKE_DEFAULT_X + 3],
            SNAKE_COLOR);
  EXPECT_EQ(info->field[SNAKE_DEFAULT_Y - 1][SNAKE_DEFAULT_X + 3], SNAKE_COLOR);
  EXPECT_EQ(m->get_state(), brickGame::Model::State::MOVING_STATE);
  EXPECT_EQ(info->bottom_text, nullptr);
}

TEST(SnakeController, test_user_input_moving_action) {
  char *user_name = (char *)malloc(sizeof(char) * 6);
  std::strcpy(user_name, "pavel");
  brickGame::Model *m = new brickGame::Model(user_name);
  brickGame::SnakeController c((char *)"pavel", m);

  GameInfo_t *info = current_game_info(NULL);
  c.userInput(START);

  struct timespec *init_limit =
      (struct timespec *)malloc(sizeof(struct timespec));
  init_limit->tv_sec = info->tick_end_time->tv_sec;
  init_limit->tv_nsec = info->tick_end_time->tv_nsec;

  c.userInput(ACTION);
  EXPECT_EQ(m->get_state(), brickGame::Model::State::MOVING_STATE);
  EXPECT_EQ(info->field[SNAKE_DEFAULT_Y][SNAKE_DEFAULT_X], SNAKE_COLOR);
  EXPECT_EQ(info->tick_end_time->tv_nsec, init_limit->tv_nsec);

  c.userInput(ACTION);
  EXPECT_EQ(m->get_state(), brickGame::Model::State::MOVING_STATE);
  EXPECT_NE(info->tick_end_time->tv_nsec, init_limit->tv_nsec);
  EXPECT_NE(info->field[SNAKE_DEFAULT_Y][SNAKE_DEFAULT_X], SNAKE_COLOR);
  EXPECT_EQ(info->field[SNAKE_DEFAULT_Y][SNAKE_DEFAULT_X + 4], SNAKE_COLOR);

  c.userInput(ACTION);
  EXPECT_NE(info->field[SNAKE_DEFAULT_Y][SNAKE_DEFAULT_X + 5], SNAKE_COLOR);

  free(init_limit);
}

TEST(SnakeController, test_user_input_moving_no_action) {
  char *user_name = (char *)malloc(sizeof(char) * 6);
  std::strcpy(user_name, "pavel");
  brickGame::Model *m = new brickGame::Model(user_name);
  brickGame::SnakeController c((char *)"pavel", m);

  GameInfo_t *info = current_game_info(NULL);
  c.userInput(START);

  struct timespec *init_limit =
      (struct timespec *)malloc(sizeof(struct timespec));
  init_limit->tv_sec = info->tick_end_time->tv_sec;
  init_limit->tv_nsec = info->tick_end_time->tv_nsec;

  c.userInput(NO_ACTION);
  EXPECT_EQ(m->get_state(), brickGame::Model::State::MOVING_STATE);
  EXPECT_EQ(info->field[SNAKE_DEFAULT_Y][SNAKE_DEFAULT_X], SNAKE_COLOR);
  EXPECT_EQ(info->tick_end_time->tv_nsec, init_limit->tv_nsec);

  c.userInput(ACTION);
  EXPECT_EQ(m->get_state(), brickGame::Model::State::MOVING_STATE);
  EXPECT_EQ(info->tick_end_time->tv_nsec, init_limit->tv_nsec);
  EXPECT_EQ(info->field[SNAKE_DEFAULT_Y][SNAKE_DEFAULT_X], SNAKE_COLOR);
  EXPECT_NE(info->field[SNAKE_DEFAULT_Y][SNAKE_DEFAULT_X + 4], SNAKE_COLOR);
  EXPECT_EQ(info->tick_end_time->tv_nsec, init_limit->tv_nsec);

  free(init_limit);
}

TEST(SnakeController, test_moving_timer_has_expired) {
  char *user_name = (char *)malloc(sizeof(char) * 6);
  std::strcpy(user_name, "pavel");
  brickGame::Model *m = new brickGame::Model(user_name);
  brickGame::SnakeController c((char *)"pavel", m);

  GameInfo_t *info = current_game_info(NULL);
  c.userInput(START);

  while (check_tick_limit()) {
    usleep(100000);
  }

  c.userInput(UP);
  EXPECT_EQ(m->get_state(), brickGame::Model::State::MOVING_STATE);
  EXPECT_NE(info->field[SNAKE_DEFAULT_Y][SNAKE_DEFAULT_X + 1], SNAKE_COLOR);
  EXPECT_EQ(info->field[SNAKE_DEFAULT_Y - 1][SNAKE_DEFAULT_X + 4], SNAKE_COLOR);
}

TEST(SnakeController, test_user_input_end) {
  char *user_name = (char *)malloc(sizeof(char) * 6);
  std::strcpy(user_name, "pavel");
  brickGame::Model *m = new brickGame::Model(user_name);
  brickGame::SnakeController c((char *)"pavel", m);

  GameInfo_t *info = current_game_info(NULL);
  c.userInput(START);
  EXPECT_FALSE(info->moving->row == APPLE_DEFAULT_Y &&
               info->moving->col == APPLE_DEFAULT_X);
  c.userInput(TERMINATE);

  EXPECT_EQ(m->get_state(), brickGame::Model::State::START_STATE);
  EXPECT_NE(info->bottom_text, nullptr);
  EXPECT_FALSE(info->game_over);
}

TEST(SnakeController, test_game_over) {
  char *user_name = (char *)malloc(sizeof(char) * 6);
  std::strcpy(user_name, "pavel");
  brickGame::Model *m = new brickGame::Model(user_name);
  brickGame::SnakeController c((char *)"pavel", m);

  GameInfo_t *info = current_game_info(NULL);
  c.userInput(START);

  c.userInput(ACTION);
  c.userInput(ACTION);
  c.userInput(ACTION);
  c.userInput(ACTION);
  c.userInput(ACTION);
  c.userInput(ACTION);
  c.userInput(ACTION);
  c.userInput(ACTION);
  c.userInput(ACTION);
  c.userInput(ACTION);

  EXPECT_EQ(m->get_state(), brickGame::Model::State::END_STATE);
  EXPECT_TRUE(info->game_over);
  EXPECT_EQ(info->field[Y_WIN][0], 'G');

  c.userInput(UP);
  EXPECT_EQ(m->get_state(), brickGame::Model::State::END_STATE);
  c.userInput(TERMINATE);
  EXPECT_EQ(m->get_state(), brickGame::Model::State::EXIT_STATE);
}

TEST(SnakeController, test_win) {
  char *user_name = (char *)malloc(sizeof(char) * 6);
  std::strcpy(user_name, "pavel");
  brickGame::Model *m = new brickGame::Model(user_name);
  brickGame::SnakeController c((char *)"pavel", m);

  GameInfo_t *info = current_game_info(NULL);
  c.userInput(START);

  c.userInput(ACTION);
  c.userInput(ACTION);
  c.userInput(ACTION);
  c.userInput(ACTION);
  c.userInput(ACTION);
  c.userInput(ACTION);
  c.userInput(ACTION);
  c.userInput(ACTION);
  EXPECT_FALSE(info->game_won);
  info->score = 196;
  c.userInput(ACTION);
  c.userInput(ACTION);

  EXPECT_TRUE(info->game_won);
  EXPECT_EQ(m->get_state(), brickGame::Model::State::END_STATE);
  EXPECT_EQ(info->field[Y_WIN][0], 'Y');
}

TEST(SnakeController, test_controller_constructor) {
  char *user_name = (char *)malloc(sizeof(char) * 6);
  std::strcpy(user_name, "pavel");
  brickGame::SnakeController c(user_name);

  GameInfo_t *info = current_game_info(NULL);
  c.userInput(START);

  c.userInput(ACTION);
  c.userInput(ACTION);
  c.userInput(ACTION);
  c.userInput(ACTION);
  c.userInput(ACTION);
  c.userInput(ACTION);
  c.userInput(ACTION);
  c.userInput(ACTION);
  EXPECT_FALSE(info->game_over);
  info->score = 196;
  c.userInput(ACTION);
  c.userInput(ACTION);

  EXPECT_TRUE(info->game_won);
  EXPECT_EQ(info->field[Y_WIN][0], 'Y');
}
