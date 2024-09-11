#include "game_kernel.h"

namespace brickGame {
GameKernel::GameKernel(char *user_name)
    : snake_(new Snake),
      apple_(Segment(APPLE_DEFAULT_Y, APPLE_DEFAULT_X)),
      info_(init_game_info_snake(user_name)) {
  current_game_info(info_);
  set_random_seed();
}

GameKernel::~GameKernel() {
  delete snake_;
  destroy_game_info();
}

bool GameKernel::change_direction(UserAction_t direction) noexcept {
  return snake_->change_direction(direction);
}

bool GameKernel::shift_forward() noexcept {
  bool is_apple_eaten = false;
  try {
    is_apple_eaten = snake_->move_forward(apple_);
  } catch (const std::exception &e) {
    std::cerr << e.what() << '\n';
  }
  return is_apple_eaten;
}

bool GameKernel::check_game_over() noexcept {
  return (snake_->check_collide() || snake_->check_out_of_bounds());
}

void GameKernel::update_game_info() noexcept {
  fill_field();
  info_->moving->row = apple_.get_y();
  info_->moving->col = apple_.get_x();
  change_level();
  info_->delay = 860 - 60 * info_->level;
  if (info_->bottom_text) {
    free(info_->bottom_text);
    info_->bottom_text = nullptr;
  }
}

void GameKernel::prepare_new_game() noexcept {
  delete snake_;
  snake_ = new Snake;
  apple_ = Segment(-1, APPLE_DEFAULT_X);
  info_->score = 0;
  info_->high_score = load_user_record(info_->user_name, SNAKE_ID);
  update_game_info();
  add_greeting(info_);
  info_->game_over = false;
  info_->game_won = false;
  clear_matrix(info_->field, FIELD_ROWS, FIELD_COLUMNS);
}

int GameKernel::get_score() noexcept { return info_->score; }

void GameKernel::update_record() noexcept {
  update_user_record(info_->user_name, info_->score, SNAKE_ID);
}

void GameKernel::add_point() noexcept {
  info_->score++;
  if (info_->score > info_->high_score) info_->high_score = info_->score;
}

void GameKernel::generate_apple() {
  std::vector<Segment> empty_grids;
  for (int i = 0; i < FIELD_ROWS; ++i) {
    for (int j = 0; j < FIELD_COLUMNS; ++j) {
      if (!snake_->is_part_of_snake(Segment(i, j)))
        empty_grids.push_back(Segment(i, j));
    }
  }
  if (empty_grids.size() > 0) {
    apple_ = empty_grids[std::rand() % empty_grids.size()];
  } else
    throw std::length_error("Trying to generate apple in full field");
}

void GameKernel::free_bottom_text() noexcept {
  if (info_->bottom_text) free(info_->bottom_text);
  info_->bottom_text = nullptr;
}

void GameKernel::prepare_for_pause() noexcept {
  prepare_pause_screen();
  info_->pause = true;
}

void GameKernel::recover_after_pause() noexcept {
  info_->pause = false;
  copy_matrix(info_->field, info_->field_copy, FIELD_ROWS, FIELD_COLUMNS);
  free_bottom_text();
}

void GameKernel::prepare_exit_state() noexcept { info_->score = -1; }

GameInfo_t *GameKernel::init_game_info_snake(char *user_name) noexcept {
  GameInfo_t *info = (GameInfo_t *)malloc(sizeof(GameInfo_t));
  info->field = create_matrix(FIELD_ROWS, FIELD_COLUMNS);
  info->field_copy = create_matrix(FIELD_ROWS, FIELD_COLUMNS);
  info->moving = init_moving_snake();
  info->next = NULL;
  info->next_idx = 0;
  info->score = 0;
  info->user_name = user_name;
  info->high_score = load_user_record(user_name, SNAKE_ID);
  info->level = 1;
  info->delay = 800;
  info->pause = false;
  info->game_over = false;
  info->game_won = false;
  info->bottom_text = nullptr;
  add_greeting(info);
  info->tick_end_time = (struct timespec *)malloc(sizeof(struct timespec));
  info->game_id = SNAKE_ID;
  return info;
}

moving_t *GameKernel::init_moving_snake() noexcept {
  moving_t *moving = (moving_t *)malloc(sizeof(moving_t));
  moving->figure = create_matrix(1, 1);
  moving->figure[0][0] = APPLE_COLOR;
  moving->idx = APPLE_COLOR;
  moving->row = -1;
  moving->col = 0;
  moving->rows = 1;
  moving->columns = 1;
  return moving;
}

void GameKernel::set_random_seed() noexcept { std::srand(std::time(nullptr)); }

void GameKernel::fill_field() noexcept {
  clear_matrix(info_->field, FIELD_ROWS, FIELD_COLUMNS);
  for (auto it = snake_->cbegin(); it != snake_->cend(); ++it) {
    int y = it->get_y(), x = it->get_x();
    info_->field[y][x] = SNAKE_COLOR;
  }
}

void GameKernel::change_level() noexcept {
  info_->level = info_->score / 5 + 1;
  if (info_->level > 10) info_->level = 10;
}
}  // namespace brickGame