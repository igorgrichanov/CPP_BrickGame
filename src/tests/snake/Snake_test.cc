#include "test_entry.h"

TEST(Segment, test_equalty) {
  brickGame::Segment s1(2, 4);
  brickGame::Segment s2 = s1;
  EXPECT_EQ(s1, s2);
}

TEST(Segment, test_equalty_const) {
  const brickGame::Segment s1(2, 4);
  const brickGame::Segment s2 = s1;
  EXPECT_EQ(s1, s2);
}

TEST(Segment, test_get_y) {
  brickGame::Segment s1(2, 4);
  EXPECT_EQ(s1.get_y(), 2);
}

TEST(Segment, test_get_x) {
  const brickGame::Segment s1(2, 4);
  EXPECT_EQ(s1.get_x(), 4);
}

TEST(Snake, test_default_constructor) {
  brickGame::Snake s;
  int i = 0;
  for (auto it = s.cbegin(); it != s.cend(); ++it) {
    EXPECT_EQ(it->get_y(), SNAKE_DEFAULT_Y);
    EXPECT_EQ(it->get_x(), SNAKE_DEFAULT_X + i);
    ++i;
  }
  EXPECT_EQ(i, SNAKE_DEFAULT_LENGTH);
}

TEST(Snake, test_change_dir_opposite) {
  brickGame::Snake s;
  brickGame::Segment apple(SNAKE_DEFAULT_Y, SNAKE_DEFAULT_X + 4);
  s.change_direction(LEFT);
  s.move_forward(apple);
  EXPECT_EQ(s.size(), static_cast<size_t>(5));
}

TEST(Snake, test_change_dir_90) {
  brickGame::Snake s;
  brickGame::Segment apple(SNAKE_DEFAULT_Y - 1, SNAKE_DEFAULT_X + 3);
  s.change_direction(UP);
  s.move_forward(apple);
  EXPECT_EQ(s.size(), static_cast<size_t>(5));
}

TEST(Snake, test_change_dir_the_same) {
  brickGame::Snake s;
  brickGame::Segment apple(SNAKE_DEFAULT_Y, SNAKE_DEFAULT_X + 4);
  s.change_direction(RIGHT);
  s.move_forward(apple);
  EXPECT_EQ(s.size(), static_cast<size_t>(5));
}

TEST(Snake, test_move_forward_exception) {
  brickGame::Snake s;
  brickGame::Segment apple(SNAKE_DEFAULT_Y, SNAKE_DEFAULT_X);
  EXPECT_ANY_THROW(s.move_forward(apple));
  EXPECT_EQ(s.size(), static_cast<size_t>(4));
}

TEST(Snake, test_check_collide) {
  brickGame::Snake s;
  s.move_forward(brickGame::Segment(SNAKE_DEFAULT_Y, SNAKE_DEFAULT_X + 4));
  s.move_forward(brickGame::Segment(SNAKE_DEFAULT_Y, SNAKE_DEFAULT_X + 5));
  s.move_forward(brickGame::Segment(SNAKE_DEFAULT_Y, SNAKE_DEFAULT_X + 6));
  s.change_direction(DOWN);
  s.move_forward(brickGame::Segment(SNAKE_DEFAULT_Y + 1, SNAKE_DEFAULT_X + 6));
  s.change_direction(LEFT);
  s.move_forward(brickGame::Segment(SNAKE_DEFAULT_Y - 1, SNAKE_DEFAULT_X));
  s.change_direction(UP);
  s.move_forward(brickGame::Segment(SNAKE_DEFAULT_Y - 1, SNAKE_DEFAULT_X));

  EXPECT_TRUE(s.check_collide());
  EXPECT_EQ(s.size(), static_cast<size_t>(8));
}

TEST(Snake, test_check_out_of_bounds) {
  brickGame::Snake s;
  s.move_forward(brickGame::Segment(SNAKE_DEFAULT_Y, SNAKE_DEFAULT_X + 4));
  s.move_forward(brickGame::Segment(SNAKE_DEFAULT_Y, SNAKE_DEFAULT_X + 5));
  s.move_forward(brickGame::Segment(SNAKE_DEFAULT_Y, SNAKE_DEFAULT_X + 6));
  s.move_forward(brickGame::Segment(SNAKE_DEFAULT_Y, SNAKE_DEFAULT_X + 7));
  EXPECT_FALSE(s.check_out_of_bounds());
  s.move_forward(brickGame::Segment(SNAKE_DEFAULT_Y - 1, SNAKE_DEFAULT_X));

  EXPECT_TRUE(s.check_out_of_bounds());
  EXPECT_EQ(s.size(), static_cast<size_t>(8));
}

TEST(Snake, test_check_part_of_snake_that_has_eaten_an_apple) {
  brickGame::Snake s;
  s.move_forward(brickGame::Segment(SNAKE_DEFAULT_Y, SNAKE_DEFAULT_X + 4));

  EXPECT_TRUE(s.is_part_of_snake(
      brickGame::Segment(SNAKE_DEFAULT_Y, SNAKE_DEFAULT_X + 4)));
  EXPECT_TRUE(
      s.is_part_of_snake(brickGame::Segment(SNAKE_DEFAULT_Y, SNAKE_DEFAULT_X)));
}

TEST(Snake, test_check_part_of_snake_that_has_not_eaten_an_apple) {
  brickGame::Snake s;
  s.move_forward(brickGame::Segment(SNAKE_DEFAULT_Y, SNAKE_DEFAULT_X - 1));

  EXPECT_TRUE(s.is_part_of_snake(
      brickGame::Segment(SNAKE_DEFAULT_Y, SNAKE_DEFAULT_X + 4)));
  EXPECT_FALSE(
      s.is_part_of_snake(brickGame::Segment(SNAKE_DEFAULT_Y, SNAKE_DEFAULT_X)));
}
