#include "frontend.h"

void print_current_screen(GameInfo_t game_info) {
  clean_game_info();
  print_game_info(game_info);
  clean_next();
  if (game_info.next) print_next(game_info);
  update_moving_field(game_info);
}

void print_moving(GameInfo_t game_info) {
  int row = game_info.moving->row, col = game_info.moving->col;
  int rows = game_info.moving->rows, columns = game_info.moving->columns;
  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < columns; j++) {
      if (game_info.moving->figure[i][j] && row + i >= 0) {
        attron(A_BOLD);
        attrset(COLOR_PAIR(game_info.moving->idx));
        mvaddch(TOP_T + 1 + row + i, LEFT_T + 1 + col + j, ACS_CKBOARD);
        attrset(0);
      }
    }
  }
  refresh();
}

void print_field(GameInfo_t game_info) {
  for (int i = 0; i < FIELD_ROWS; i++) {
    for (int j = 0; j < FIELD_COLUMNS; j++) {
      if (game_info.field[i][j] >= 1 && game_info.field[i][j] <= 7) {
        attron(A_BOLD);
        attrset(COLOR_PAIR(game_info.field[i][j]));
        mvaddch(TOP_T + 1 + i, LEFT_T + 1 + j, ACS_CKBOARD);
        attrset(0);
      } else if (game_info.field[i][j]) {
        mvaddch(TOP_T + 1 + i, LEFT_T + 1 + j, game_info.field[i][j]);
      } else {
        mvprintw(TOP_T + 1 + i, LEFT_T + 1 + j, " ");
      }
    }
  }
  if (game_info.bottom_text)
    mvprintw(BOTTOM_T + 2, LEFT_T, game_info.bottom_text);
  else {
    char spaces[] = "                             ";
    for (int i = 0; i < 3; ++i) {
      mvprintw(BOTTOM_T + 2 + i, LEFT_T, spaces);
    }
  }

  refresh();
}

void update_moving_field(GameInfo_t game_info) {
  clean_field();
  print_field(game_info);
  if (!game_info.game_over && !game_info.pause) print_moving(game_info);
}

void print_overlay() {
  /// отрисовка рамки с игрой
  draw_rectangle(TOP_T, BOTTOM_T, LEFT_T, RIGHT_T);
  /// отрисовка рамки с дополнительной информацией
  draw_rectangle(TOP_A, BOTTOM_A, LEFT_A, RIGHT_A);

  /// отрисовка шаблона для размещения дополнительной информации
  mvprintw(Y_SCORE, X_SCORE, "SCORE");
  draw_rectangle(TOP_SCORE, BOTTOM_SCORE, LEFT_SCORE, RIGHT_SCORE);
  mvprintw(Y_BEST, X_BEST, "BEST");
  draw_rectangle(TOP_BEST, BOTTOM_BEST, LEFT_BEST, RIGHT_BEST);
  mvprintw(Y_LEVEL, X_LEVEL, "LEVEL");
  draw_rectangle(TOP_LEVEL, BOTTOM_LEVEL, LEFT_LEVEL, RIGHT_LEVEL);
  if (updateCurrentState().game_id == TETRIS_ID) {
    mvprintw(Y_NEXT, X_NEXT, "NEXT");
    draw_rectangle(TOP_NEXT, BOTTOM_NEXT, LEFT_NEXT, RIGHT_NEXT);
  }

  refresh();
}

void clean_field() {
  for (int i = TOP_T + 1; i < BOTTOM_T; i++) {
    for (int j = LEFT_T + 1; j < RIGHT_T; j++) {
      mvprintw(i, j, " ");
    }
  }
  refresh();
}

void draw_rectangle(int top, int bottom, int left, int right) {
  /// ставим 4 угла, чтобы рамка была целостной
  mvaddch(top, left, ACS_ULCORNER);
  for (int i = left + 1; i < right; i++) {
    mvaddch(top, i, ACS_HLINE);
  }
  mvaddch(top, right, ACS_URCORNER);
  for (int i = top + 1; i < bottom; i++) {
    mvaddch(i, right, ACS_VLINE);
  }
  mvaddch(bottom, right, ACS_LRCORNER);
  for (int i = right - 1; i > left; i--) {
    mvaddch(bottom, i, ACS_HLINE);
  }
  mvaddch(bottom, left, ACS_LLCORNER);
  for (int i = bottom - 1; i > top; i--) {
    mvaddch(i, left, ACS_VLINE);
  }
}

void print_game_info(GameInfo_t game_info) {
  /// выравнивание значений SCORE и BEST по центру
  int score_shift = 1, best_shift = 1;
  if (game_info.score < 10) {
    score_shift = 3;
  } else if (game_info.score < 1000) {
    score_shift = 2;
  }
  if (game_info.high_score < 10) {
    best_shift = 3;
  } else if (game_info.high_score < 1000) {
    best_shift = 2;
  }

  mvprintw(TOP_SCORE + 1, LEFT_SCORE + score_shift, "%d", game_info.score);
  mvprintw(TOP_BEST + 1, LEFT_BEST + best_shift, "%d", game_info.high_score);
  mvprintw(TOP_LEVEL + 1, LEFT_LEVEL + 3, "%d", game_info.level);
  refresh();
}

void clean_game_info() {
  mvprintw(TOP_SCORE + 1, LEFT_SCORE + 1, "     ");
  mvprintw(TOP_BEST + 1, LEFT_BEST + 1, "     ");
  mvprintw(TOP_LEVEL + 1, LEFT_LEVEL + 1, "     ");
  refresh();
}

void print_next(GameInfo_t game_info) {
  /// все фигуры в базовом положении занимают не более 2 рядов
  int j_shift = 2, rows = 2, columns = 3;
  if (game_info.next_idx == 4) {
    columns = 2;
  } else if (game_info.next_idx == 1) {
    columns = 4;
    j_shift = 1;
  }
  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < columns; j++) {
      if (game_info.next[i][j]) {
        attron(A_BOLD);
        attrset(COLOR_PAIR(game_info.next_idx));
        mvaddch(TOP_NEXT + i + 1, LEFT_NEXT + j + j_shift, ACS_CKBOARD);
        attrset(0);
      }
    }
  }
  refresh();
}

void clean_next() {
  for (int i = LEFT_NEXT + 1; i < RIGHT_NEXT; i++) {
    for (int j = TOP_NEXT + 1; j < BOTTOM_NEXT; j++) {
      mvprintw(j, i, " ");
    }
  }
  refresh();
}

void print_options() {
  draw_rectangle(TOP_OPTIONS, BOTTOM_OPTIONS, LEFT_OPTIONS, RIGHT_OPTIONS);
  mvprintw(TOP_OPTIONS + 1, LEFT_OPTIONS + 2, "\'p\' - pause");
  mvprintw(TOP_OPTIONS + 3, LEFT_OPTIONS + 2, "\'q\' - to main menu");
  /// предпочтительный режим выделения в терминале
  attron(A_STANDOUT);
  attrset(COLOR_PAIR(8));
  mvprintw(Y_OPTIONS, X_OPTIONS, "OPTIONS");
  attrset(0);
  refresh();
}

char *ask_user_name() {
  char *user_name = (char *)calloc(sizeof(char), USER_NAME_SIZE);
  printf("Your name (2-12 characters): ");
  while (!scanf("%s", user_name) || strlen(user_name) < 2 ||
         strlen(user_name) > 12) {
    printf("Please enter at least 2 characters: ");
  }
  return user_name;
}

int choose_game() {
  int game = 0;
  printf(
      "What game do you want to play?\n1. Tetris\n2. Snake\nType game "
      "number: ");
  while (!scanf("%d", &game) || !(game == 1 || game == 2)) {
    printf("Choose one of the suggested options (1 or 2): ");
  }
  return game - 1;
}