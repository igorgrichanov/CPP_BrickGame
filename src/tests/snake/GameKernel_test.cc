#include "test_entry.h"

TEST(GameKernel, test_update_game_info) {
  char *user_name = (char *)malloc(sizeof(char) * 6);
  std::strcpy(user_name, "pavel");
  brickGame::GameKernel k(user_name);
  GameInfo_t *info = current_game_info(NULL);
  k.update_game_info();
  EXPECT_EQ(info->delay, 800);
  EXPECT_EQ(info->moving->row, APPLE_DEFAULT_Y);
  EXPECT_EQ(info->moving->col, APPLE_DEFAULT_X);
  EXPECT_EQ(info->level, 1);
  EXPECT_EQ(info->field[SNAKE_DEFAULT_Y][SNAKE_DEFAULT_X + 3], SNAKE_COLOR);
  EXPECT_NE(info->field[SNAKE_DEFAULT_Y][SNAKE_DEFAULT_X + 4], SNAKE_COLOR);
  EXPECT_EQ(info->bottom_text, nullptr);
}

TEST(GameKernel, test_shift_forward) {
  char *user_name = (char *)malloc(sizeof(char) * 6);
  std::strcpy(user_name, "pavel");
  brickGame::GameKernel k(user_name);
  GameInfo_t *info = current_game_info(NULL);
  EXPECT_FALSE(k.shift_forward());
  EXPECT_FALSE(k.shift_forward());
  EXPECT_FALSE(k.shift_forward());
  EXPECT_TRUE(k.shift_forward());
  k.generate_apple();
  EXPECT_FALSE(k.shift_forward());
  k.update_game_info();
  EXPECT_NE(info->field[SNAKE_DEFAULT_Y][SNAKE_DEFAULT_X + 2], SNAKE_COLOR);
  EXPECT_EQ(info->field[SNAKE_DEFAULT_Y][SNAKE_DEFAULT_X + 7], SNAKE_COLOR);
}

TEST(GameKernel, test_check_game_over_collide) {
  char *user_name = (char *)malloc(sizeof(char) * 6);
  std::strcpy(user_name, "pavel");
  brickGame::GameKernel k(user_name);
  GameInfo_t *info = current_game_info(NULL);
  EXPECT_TRUE(k.change_direction(UP));
  EXPECT_FALSE(k.shift_forward());

  EXPECT_TRUE(k.change_direction(LEFT));
  EXPECT_FALSE(k.shift_forward());

  EXPECT_FALSE(k.check_game_over());
  k.change_direction(DOWN);
  EXPECT_FALSE(k.shift_forward());

  EXPECT_FALSE(k.check_game_over());
  k.update_game_info();
  EXPECT_NE(info->field[SNAKE_DEFAULT_Y][SNAKE_DEFAULT_X + 1], SNAKE_COLOR);
  EXPECT_EQ(info->field[SNAKE_DEFAULT_Y - 1][SNAKE_DEFAULT_X + 2], SNAKE_COLOR);
  EXPECT_EQ(info->field[SNAKE_DEFAULT_Y][SNAKE_DEFAULT_X + 2], SNAKE_COLOR);
}

TEST(GameKernel, test_check_game_over_bounds) {
  char *user_name = (char *)malloc(sizeof(char) * 6);
  std::strcpy(user_name, "pavel");
  brickGame::GameKernel k(user_name);
  GameInfo_t *info = current_game_info(NULL);
  EXPECT_FALSE(k.shift_forward());
  EXPECT_FALSE(k.shift_forward());
  EXPECT_FALSE(k.shift_forward());
  EXPECT_TRUE(k.shift_forward());
  k.generate_apple();
  EXPECT_FALSE(k.check_game_over());
  EXPECT_FALSE(k.shift_forward());
  EXPECT_TRUE(k.check_game_over());

  k.update_game_info();
  EXPECT_NE(info->field[SNAKE_DEFAULT_Y][SNAKE_DEFAULT_X + 3], SNAKE_COLOR);
  EXPECT_EQ(info->field[SNAKE_DEFAULT_Y][SNAKE_DEFAULT_X + 4], SNAKE_COLOR);
}

TEST(GameKernel, test_change_direction_opposite) {
  char *user_name = (char *)malloc(sizeof(char) * 6);
  std::strcpy(user_name, "pavel");
  brickGame::GameKernel k(user_name);
  GameInfo_t *info = current_game_info(NULL);
  EXPECT_FALSE(k.change_direction(LEFT));
  k.shift_forward();
  k.update_game_info();
  EXPECT_NE(info->field[SNAKE_DEFAULT_Y][SNAKE_DEFAULT_X], SNAKE_COLOR);
}

TEST(GameKernel, test_change_direction_90) {
  char *user_name = (char *)malloc(sizeof(char) * 6);
  std::strcpy(user_name, "pavel");
  brickGame::GameKernel k(user_name);
  GameInfo_t *info = current_game_info(NULL);
  EXPECT_TRUE(k.change_direction(UP));
  k.shift_forward();
  k.update_game_info();
  EXPECT_NE(info->field[SNAKE_DEFAULT_Y][SNAKE_DEFAULT_X + 4], SNAKE_COLOR);
  EXPECT_NE(info->field[SNAKE_DEFAULT_Y][SNAKE_DEFAULT_X], SNAKE_COLOR);
  EXPECT_EQ(info->field[SNAKE_DEFAULT_Y - 1][SNAKE_DEFAULT_X + 3], SNAKE_COLOR);
}

TEST(GameKernel, test_change_direction_same) {
  char *user_name = (char *)malloc(sizeof(char) * 6);
  std::strcpy(user_name, "pavel");
  brickGame::GameKernel k(user_name);
  GameInfo_t *info = current_game_info(NULL);
  EXPECT_FALSE(k.change_direction(RIGHT));
  k.shift_forward();
  k.update_game_info();
  EXPECT_EQ(info->field[SNAKE_DEFAULT_Y][SNAKE_DEFAULT_X + 4], SNAKE_COLOR);
  EXPECT_NE(info->field[SNAKE_DEFAULT_Y][SNAKE_DEFAULT_X], SNAKE_COLOR);
}

TEST(GameKernel, test_prepare_new_game) {
  char *user_name = (char *)malloc(sizeof(char) * 6);
  std::strcpy(user_name, "pavel");
  brickGame::GameKernel k(user_name);
  GameInfo_t *info = current_game_info(NULL);
  k.prepare_new_game();
  EXPECT_EQ(k.get_score(), 0);
  EXPECT_NE(info->bottom_text, nullptr);
}

TEST(GameKernel, test_get_score) {
  char *user_name = (char *)malloc(sizeof(char) * 6);
  std::strcpy(user_name, "pavel");
  brickGame::GameKernel k(user_name);
  k.shift_forward();
  k.shift_forward();
  k.shift_forward();
  bool eaten = k.shift_forward();
  if (eaten) k.add_point();

  EXPECT_EQ(k.get_score(), 1);
}

TEST(GameKernel, test_set_record) {
  char *user_name = (char *)malloc(sizeof(char) * 6);
  std::strcpy(user_name, "masha");
  brickGame::GameKernel k(user_name);
  GameInfo_t *info = current_game_info(NULL);
  info->score = 100;
  k.update_record();

  EXPECT_EQ(k.get_score(), 100);
}

TEST(GameKernel, test_update_record) {
  char *user_name = (char *)malloc(sizeof(char) * 6);
  std::strcpy(user_name, "masha");
  brickGame::GameKernel k(user_name);

  EXPECT_EQ(updateCurrentState().high_score, 100);
}

TEST(GameKernel, test_generate_apple) {
  char *user_name = (char *)malloc(sizeof(char) * 6);
  std::strcpy(user_name, "pavel");
  brickGame::GameKernel k(user_name);
  GameInfo_t *info = current_game_info(NULL);
  EXPECT_FALSE(k.shift_forward());
  EXPECT_FALSE(k.shift_forward());
  EXPECT_FALSE(k.shift_forward());
  k.generate_apple();
  k.update_game_info();
  EXPECT_FALSE(k.shift_forward());
  k.update_game_info();
  EXPECT_EQ(info->score, 0);
}

TEST(GameKernel, test_free_bottom_text) {
  char *user_name = (char *)malloc(sizeof(char) * 6);
  std::strcpy(user_name, "pavel");
  brickGame::GameKernel k(user_name);
  GameInfo_t *info = current_game_info(NULL);
  EXPECT_NE(info->bottom_text, nullptr);
  k.free_bottom_text();
  EXPECT_EQ(info->bottom_text, nullptr);
  k.free_bottom_text();
  EXPECT_EQ(info->bottom_text, nullptr);
}

TEST(GameKernel, test_prepare_for_pause) {
  char *user_name = (char *)malloc(sizeof(char) * 6);
  std::strcpy(user_name, "pavel");
  brickGame::GameKernel k(user_name);
  GameInfo_t *info = current_game_info(NULL);
  EXPECT_NE(info->bottom_text, nullptr);
  k.prepare_for_pause();
  EXPECT_TRUE(info->pause);
  EXPECT_NE(info->bottom_text, nullptr);
  EXPECT_EQ(info->field[Y_WIN][3], 'P');
  EXPECT_EQ(info->field_copy[SNAKE_DEFAULT_Y][SNAKE_DEFAULT_X], 0);
}

TEST(GameKernel, test_recover_after_pause) {
  char *user_name = (char *)malloc(sizeof(char) * 6);
  std::strcpy(user_name, "pavel");
  brickGame::GameKernel k(user_name);
  GameInfo_t *info = current_game_info(NULL);
  k.prepare_for_pause();
  k.recover_after_pause();
  EXPECT_FALSE(info->pause);
  EXPECT_EQ(info->bottom_text, nullptr);
  EXPECT_EQ(info->field[SNAKE_DEFAULT_Y][SNAKE_DEFAULT_X], 0);
  EXPECT_EQ(info->field_copy[SNAKE_DEFAULT_Y][SNAKE_DEFAULT_X], 0);
}

TEST(GameKernel, test_prepare_exit_state) {
  char *user_name = (char *)malloc(sizeof(char) * 6);
  std::strcpy(user_name, "pavel");
  brickGame::GameKernel k(user_name);
  GameInfo_t *info = current_game_info(NULL);
  k.prepare_exit_state();
  EXPECT_EQ(info->score, -1);
}

TEST(GameInfo, test_init) {
  char *user_name = (char *)malloc(sizeof(char) * 6);
  std::strcpy(user_name, "pavel");
  brickGame::GameKernel k(user_name);
  GameInfo_t *info = current_game_info(NULL);
  EXPECT_EQ(info->delay, 800);
  EXPECT_EQ(info->moving->row, -1);
  EXPECT_EQ(info->moving->col, 0);
  EXPECT_EQ(info->level, 1);
  EXPECT_NE(info->field[SNAKE_DEFAULT_Y][SNAKE_DEFAULT_X], SNAKE_COLOR);
  EXPECT_NE(info->bottom_text, nullptr);
}