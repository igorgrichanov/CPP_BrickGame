#include "matrix_operations.h"

int **get_tetramino(int idx) {
  if (idx < 1 || idx > 7) return NULL;
  int rows = 3, columns = 3;
  if (idx == 1) rows = columns = 4;
  if (idx == 4) rows = columns = 2;
  int **result = create_matrix(rows, columns);

  switch (idx) {
    case 1:
      result[1][0] = 1;
      result[1][1] = 1;
      result[1][2] = 1;
      result[1][3] = 1;
      break;
    case 2:
      result[0][0] = 2;
      result[1][0] = 2;
      result[1][1] = 2;
      result[1][2] = 2;
      break;
    case 3:
      result[0][2] = 3;
      result[1][0] = 3;
      result[1][1] = 3;
      result[1][2] = 3;
      break;
    case 4:
      result[0][0] = 4;
      result[0][1] = 4;
      result[1][0] = 4;
      result[1][1] = 4;
      break;
    case 5:
      result[0][1] = 5;
      result[0][2] = 5;
      result[1][0] = 5;
      result[1][1] = 5;
      break;
    case 6:
      result[0][1] = 6;
      result[1][0] = 6;
      result[1][1] = 6;
      result[1][2] = 6;
      break;
    case 7:
      result[0][0] = 7;
      result[0][1] = 7;
      result[1][1] = 7;
      result[1][2] = 7;
      break;
  }
  return result;
}

void rotate_matrix_90_clockwise(int **matrix, int rows, int columns) {
  if (!matrix) return;
  int **temp = create_matrix(rows, columns);
  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < columns; j++) {
      temp[j][rows - i - 1] = matrix[i][j];
    }
  }
  copy_matrix(matrix, temp, rows, columns);
  remove_matrix(temp);
}