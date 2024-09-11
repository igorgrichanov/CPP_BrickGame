#ifndef MATRIX_OPERATIONS_H
#define MATRIX_OPERATIONS_H

/**
 * @file
 * @brief функции по работе с двумерными массивами
 */

#include <stdlib.h>

#include "../../common/common_matrix.h"
#include "defines.h"

/// @brief получение исходной позиции одного из семи тетрамино в порядке их
/// расположения на картинке в src/SRS-pieces.png
/// @param i номер тетрамино на картинке по порядку
/// @return матрица в динамической памяти, соответствующая рисунку
int **get_tetramino(int i);

/// @brief поворот матрицы на 90 градусов по часовой стрелке
/// @param matrix матрица для поворота
/// @param rows количество рядов
/// @param columns количество столбцов
void rotate_matrix_90_clockwise(int **matrix, int rows, int columns);

#endif