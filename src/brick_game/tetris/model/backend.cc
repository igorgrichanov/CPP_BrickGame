#include "backend.h"

void drop_new_tetramino() {
  GameInfo_t *info = current_game_info(NULL);
  remove_matrix(info->moving->figure);
  info->moving->figure = info->next;
  info->moving->idx = info->next_idx;
  info->moving->row = MOVING_INIT_ROW;
  info->moving->col = MOVING_INIT_COL;
  info->moving->rows = get_tetramino_size(info->moving->idx);
  info->moving->columns = get_tetramino_size(info->moving->idx);
}

void get_next_tetramino(GameInfo_t *info) {
  rand();
  int idx = rand() % 7 + 1;
  info->next = get_tetramino(idx);
  info->next_idx = idx;
}

int get_tetramino_size(int idx) {
  int result = 3;
  if (idx == 1)
    result = 4;
  else if (idx == 4)
    result = 2;
  return result;
}

void handle_bottom_filling() {
  GameInfo_t *info = current_game_info(NULL);
  int filled_rows = count_filled_rows(info);
  add_points(filled_rows);
  for (int i = 0; i < filled_rows; i++) {
    move_field_down(info);
  }
  change_level();
}

void add_points(int filled_rows) {
  GameInfo_t *info = current_game_info(NULL);
  while (filled_rows) {
    if (filled_rows % 4 == 1) {
      info->score += 100;
      filled_rows--;
    } else if (filled_rows % 4 == 2) {
      info->score += 300;
      filled_rows -= 2;
    } else if (filled_rows % 4 == 3) {
      info->score += 700;
      filled_rows -= 3;
    } else if (filled_rows % 4 == 0) {
      info->score += 1500;
      filled_rows -= 4;
    }
  }
  if (info->score > info->high_score) info->high_score = info->score;
}

void change_level() {
  GameInfo_t *info = current_game_info(NULL);
  info->level = info->score / 600 + 1;
  if (info->level > 10) info->level = 10;
  info->delay = 860 - 60 * info->level;
}

moving_t *init_moving_tetris(int idx) {
  moving_t *moving = (moving_t *)malloc(sizeof(moving_t));
  moving->idx = idx;
  moving->rows = get_tetramino_size(moving->idx);
  moving->columns = get_tetramino_size(moving->idx);
  moving->figure = get_tetramino(idx);
  moving->row = MOVING_INIT_ROW;
  moving->col = MOVING_INIT_COL;
  return moving;
}

GameInfo_t *init_game_info_tetris(char *user_name) {
  GameInfo_t *info = (GameInfo_t *)malloc(sizeof(GameInfo_t));
  info->field = create_matrix(FIELD_ROWS, FIELD_COLUMNS);
  info->user_name = user_name;
  info->bottom_text = NULL;
  add_greeting(info);
  info->field_copy = create_matrix(FIELD_ROWS, FIELD_COLUMNS);
  info->moving = init_moving_tetris(1);
  info->next = NULL;
  get_next_tetramino(info);
  info->score = 0;
  info->high_score = load_user_record(user_name, TETRIS_ID);
  info->level = 1;
  info->delay = 800;
  info->pause = false;
  info->game_over = false;
  info->game_won = false;
  info->tick_end_time = (struct timespec *)malloc(sizeof(struct timespec));
  return info;
}

void clear_game_info_tetris() {
  GameInfo_t *info = current_game_info(NULL);
  remove_matrix(info->field);
  info->field = create_matrix(FIELD_ROWS, FIELD_COLUMNS);
  destroy_moving(info->moving);
  info->moving = init_moving_tetris(1);
  if (info->next) remove_matrix(info->next);
  get_next_tetramino(info);
  info->score = 0;
  info->high_score = load_user_record(info->user_name, TETRIS_ID);
  info->level = 1;
  info->delay = 800;
  info->pause = false;
  info->game_over = false;
  if (info->bottom_text) {
    free(info->bottom_text);
    info->bottom_text = NULL;
  }
}

void rotate_tetramino() {
  GameInfo_t *info = current_game_info(NULL);
  int rows = info->moving->rows, columns = info->moving->columns;
  int **figure_copy = create_matrix(rows, columns);
  copy_matrix(figure_copy, info->moving->figure, rows, columns);

  rotate_matrix_90_clockwise(info->moving->figure, rows, columns);
  if (check_collide(info)) {
    remove_matrix(info->moving->figure);
    info->moving->figure = figure_copy;
  } else {
    remove_matrix(figure_copy);
  }
}