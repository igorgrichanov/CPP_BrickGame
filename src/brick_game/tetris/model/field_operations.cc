#include "field_operations.h"

int shift_down(GameInfo_t *info) {
  int result = check_down(info);
  if (check_down(info)) info->moving->row++;
  return result;
}

int check_down(GameInfo_t *info) {
  int flag = 1;
  int row = info->moving->row + TETRAMINO_BUFFER,
      col = info->moving->col + WALL_SIZE;
  int rows = info->moving->rows, columns = info->moving->columns;
  int **field_with_borders = get_field_with_borders(info->field);
  for (int i = 0; i < rows && flag; i++) {
    for (int j = 0; j < columns && flag; j++) {
      if (field_with_borders[row + i + 1][col + j] &&
          info->moving->figure[i][j]) {
        flag = 0;
      }
    }
  }
  remove_matrix(field_with_borders);
  return flag;
}

void shift_left(GameInfo_t *info) {
  if (check_left(info)) info->moving->col--;
}

int check_left(GameInfo_t *info) {
  int flag = 1;
  int row = info->moving->row, col = info->moving->col + WALL_SIZE;
  int rows = info->moving->rows, columns = info->moving->columns;
  int **field_with_borders = get_field_with_borders(info->field);
  for (int i = 0; i < rows && flag; i++) {
    for (int j = 0; j < columns && flag; j++) {
      if (field_with_borders[TETRAMINO_BUFFER + row + i][col + j - 1] &&
          info->moving->figure[i][j]) {
        flag = 0;
      }
    }
  }
  remove_matrix(field_with_borders);
  return flag;
}

void shift_right(GameInfo_t *info) {
  if (check_right(info)) info->moving->col++;
}

int check_right(GameInfo_t *info) {
  int flag = 1;
  int row = info->moving->row, col = info->moving->col + WALL_SIZE;
  int rows = info->moving->rows, columns = info->moving->columns;
  int **field_with_borders = get_field_with_borders(info->field);
  for (int i = 0; i < rows && flag; i++) {
    for (int j = 0; j < columns && flag; j++) {
      if (field_with_borders[TETRAMINO_BUFFER + row + i][col + j + 1] &&
          info->moving->figure[i][j]) {
        flag = 0;
      }
    }
  }
  remove_matrix(field_with_borders);
  return flag;
}

int check_collide(GameInfo_t *info) {
  int flag = 0;
  int row = info->moving->row, col = info->moving->col + WALL_SIZE;
  int rows = info->moving->rows, columns = info->moving->columns;
  int **field_with_borders = get_field_with_borders(info->field);
  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < columns; j++) {
      if (field_with_borders[TETRAMINO_BUFFER + row + i][col + j] &&
          info->moving->figure[i][j])
        flag = 1;
    }
  }
  remove_matrix(field_with_borders);
  return flag;
}

void drop_down(GameInfo_t *info) {
  while (check_down(info)) {
    shift_down(info);
  }
}

void attach(GameInfo_t *info) {
  int row = info->moving->row, col = info->moving->col + WALL_SIZE;
  int rows = info->moving->rows, columns = info->moving->columns;

  /// прикрепим падающую фигуру с полю с границами, чтобы не обрабатывать выход
  /// незаполненных частей матрицы с падающей фигурой за пределы поля
  int **field_with_borders = get_field_with_borders(info->field);
  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < columns; j++) {
      if (info->moving->figure[i][j])
        field_with_borders[TETRAMINO_BUFFER + row + i][col + j] =
            info->moving->figure[i][j];
    }
  }

  /// актуализируем игровое поле
  for (int i = 0; i < FIELD_ROWS; i++) {
    for (int j = 0; j < FIELD_COLUMNS; j++) {
      info->field[i][j] =
          field_with_borders[TETRAMINO_BUFFER + i][WALL_SIZE + j];
    }
  }
  remove_matrix(field_with_borders);
}

int check_ceiling(GameInfo_t *info) {
  int result = 0;
  for (int j = 0; j < FIELD_COLUMNS && !result; j++) {
    if (info->field[0][j]) result = 1;
  }
  return result;
}

int check_row_filling_by_idx(GameInfo_t *info, int idx) {
  int result = 1;
  for (int j = 0; j < FIELD_COLUMNS && result; j++) {
    if (!info->field[idx][j]) result = 0;
  }
  return result;
}

void move_field_down(GameInfo_t *info) {
  for (int i = FIELD_ROWS - 1; i > 0; i--) {
    for (int j = 0; j < FIELD_COLUMNS; j++) {
      info->field[i][j] = info->field[i - 1][j];
    }
  }
}

int count_filled_rows(GameInfo_t *info) {
  int flag = 0, filled_rows = 0;
  for (int i = FIELD_ROWS - 1; i >= 0 && !flag; i--) {
    if (check_row_filling_by_idx(info, i))
      filled_rows++;
    else
      flag = 1;
  }
  return filled_rows;
}

int **get_field_with_borders(int **field) {
  /// стенки имеют толщину 2, так как I-тетрамино может иметь 2 пустых
  /// столбца/строки в зависимости от положения

  /// зарезервируем буфер для невидимой части поля, в которую попадает тетрамино
  /// в SPAWN_STATE
  int rows = TETRAMINO_BUFFER + FIELD_ROWS + WALL_SIZE;
  int columns = WALL_SIZE + FIELD_COLUMNS + WALL_SIZE;
  int **field_with_borders = create_matrix(rows, columns);

  /// установка левой и правой грацицы поля
  for (int i = 0; i < rows; i++) {
    field_with_borders[i][0] = 1;
    field_with_borders[i][1] = 1;
    field_with_borders[i][columns - 2] = 1;
    field_with_borders[i][columns - 1] = 1;
  }

  /// установка нижней границы поля
  for (int j = WALL_SIZE; j < columns - WALL_SIZE; j++) {
    field_with_borders[rows - 2][j] = 1;
    field_with_borders[rows - 1][j] = 1;
  }

  for (int i = TETRAMINO_BUFFER; i < FIELD_ROWS + TETRAMINO_BUFFER; i++) {
    for (int j = 0; j < FIELD_COLUMNS; j++) {
      field_with_borders[i][j + WALL_SIZE] = field[i - TETRAMINO_BUFFER][j];
    }
  }
  return field_with_borders;
}