#ifndef BACKEND_TETRIS_H
#define BACKEND_TETRIS_H

/**
 * @file
 * @brief функции, выполняющие ключевые операции в игре
 */

#include <time.h>

#include "../../common/common_classes.h"
#include "../../common/common_functions.h"
#include "../../common/common_matrix.h"
#include "field_operations.h"
#include "matrix_operations.h"

/// @brief забрать тетрамино из секции NEXT для выбрасывания на поле
void drop_new_tetramino();

/// @brief генерация следующего тетрамино
/// @param info структура, хранящая информацию об игре
void get_next_tetramino(GameInfo_t *info);

/// @brief узнать размер тетрамино по индексу
/// @param idx индекс от 1 до 7 включительно
/// @return размер тетрамино
int get_tetramino_size(int idx);

/// @brief проверка заполнения нижних рядов
void handle_bottom_filling();

/// @brief добавление очков
/// @param filled_rows количество заполненных рядов
void add_points(int filled_rows);

/// @brief синхронизация уровня и количества очков
void change_level();

/// @brief инициализация структуры, хранящей информацию о падающей фигуре
/// @param idx порядковый номер тетрамино (0-6)
/// @return структура, хранящая информацию о падающей фигуре
moving_t *init_moving_tetris(int idx);

/// @brief инициализация структуры, содержащей информацию об игре
/// @param user_name имя пользователя, введенное при авторизации
/// @return данные об игре и игроке
GameInfo_t *init_game_info_tetris(char *user_name);

/// @brief обнуление переменной типа GameInfo_t
void clear_game_info_tetris();

/// @brief поворот падающего тетрамино
void rotate_tetramino();

#endif