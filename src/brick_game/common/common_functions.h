#ifndef COMMON_FUNCTIONS_H
#define COMMON_FUNCTIONS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

#include "common_classes.h"
#include "common_defines.h"

#define USER_RECORD_LINE_LENGTH 25

/**
 * @file
 * @brief объявления общих для двух игр функций
 *
 */

/// @brief парсинг имени и рекорда из считанной из файла строки
/// @param line_from_file строка, считанная из файла
/// @param user_name имя пользователя
/// @return -1 - строка не содердит имя пользователя. Если строка содержит имя
/// пользователя, возвращается его рекорд
int parse_user_record(char *line_from_file, char *user_name);

/// @brief получение информации о рекорде пользователя в предыдущих сеансах
/// игры. Запись нулевого значения рекорда для нового пользователя
/// @param user_name имя пользователя, полученное на этапе авторизации
/// @param game код игры
/// @return текущий рекорд, если он был установлен. Иначе 0
int load_user_record(char *user_name, int game);

/// @brief обновление рекорда в базе, если он был побит
/// @param user_name имя пользователя, указанное при авторизации
/// @param new_record новый рекорд
/// @param game ID игры
void update_user_record(char *user_name, int new_record, int game);

/// @brief подсчет времени конца такта MOVING_STATE
void get_tick_limit();

/// @brief проверка, не истек ли таймер состояния MOVING_STATE
/// @return 0 - время истекло, 1 - время есть
int check_tick_limit();

/**
 * @brief добавление приветственного текста на поле
 *
 * @param info информация об игре
 */
void add_greeting(GameInfo_t *info);

/**
 * @brief добавление текста о способах начать и покинуть игру
 *
 * @param info информация об игре
 */
void add_init_text(GameInfo_t *info);

/**
 * @brief добавление текста о выигрыше на очищенное поле
 *
 */
void prepare_win_screen();

/**
 * @brief добавление текста о проигрыше на очищенное поле
 *
 */
void prepare_game_over_screen();

/**
 * @brief добавление текста, сообщающего о состоянии паузы, на очищенное
 * игровое поле
 *
 */
void prepare_pause_screen();

#endif