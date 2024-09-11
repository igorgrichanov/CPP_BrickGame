#include "common_matrix.h"

int **create_matrix(int rows, int columns) {
  int **result =
      (int **)malloc(sizeof(int *) * rows + sizeof(int) * rows * columns);
  int *start = (int *)((char *)result + sizeof(int *) * rows);
  for (int i = 0; i < rows; i++) {
    result[i] = start + i * columns;
  }
  clear_matrix(result, rows, columns);
  return result;
}

void copy_matrix(int **dest, int **src, int rows, int columns) {
  if (!dest || !src) return;
  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < columns; j++) {
      dest[i][j] = src[i][j];
    }
  }
}

void clear_matrix(int **matrix, int rows, int columns) {
  if (!matrix) return;
  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < columns; j++) {
      matrix[i][j] = 0;
    }
  }
}

int eq_matrix(int **A, int **B, int rows, int columns) {
  if (!A || !B) return 0;
  int result = 1;
  for (int i = 0; i < rows && result; i++) {
    for (int j = 0; j < columns && result; j++) {
      if (A[i][j] != B[i][j]) result = 0;
    }
  }
  return result;
}

void remove_matrix(int **A) {
  if (A) {
    free(A);
  }
}