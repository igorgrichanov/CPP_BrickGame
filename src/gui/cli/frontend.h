#ifndef CONSOLE_FRONTEND_H
#define CONSOLE_FRONTEND_H

/**
 * @file
 * @brief функции вывода информации на экран
 */

#include <ncurses.h>
#include <stdlib.h>
#include <string.h>

#include "../../brick_game/common/common_classes.h"
#include "../../brick_game/tetris/model/defines.h"

/// @brief полное обноление экрана
/// @param game_info информация об игре
void print_current_screen(GameInfo_t game_info);

/// @brief ежетактная печать
/// @param game_info информация об игре
void print_moving(GameInfo_t game_info);

/// @brief печать поля
/// @param game_info информация об игре
void print_field(GameInfo_t game_info);

/// @brief обновление экрана в MOVING_STATE
/// @param game_info информация об игре
void update_moving_field(GameInfo_t game_info);

/// @brief отрисовка макета
void print_overlay();

/// @brief очистка игрового поля
void clean_field();

/// @brief отрисовка прямоугольных рамок
/// @param top положение верхней границы
/// @param bottom положение нижней грацицы
/// @param left положение левой границы
/// @param right положение правой границы
void draw_rectangle(int top, int bottom, int left, int right);

/// @brief печать дополнительной информации по игре
/// @param game_info информация об игре
void print_game_info(GameInfo_t game_info);

/// @brief удаление дополнительной информации для обновления
void clean_game_info();

/// @brief печать следующей фигуры
/// @param game_info информация об игре
void print_next(GameInfo_t game_info);

/// @brief очистка поля следующей фигуры
void clean_next();

/// @brief вывод информации о кнопках паузы и завершения игры
void print_options();

/// @brief авторизация пользователя
/// @return имя пользователя
char *ask_user_name();

/// @brief выбор игры
/// @return ID игры
int choose_game();
#endif