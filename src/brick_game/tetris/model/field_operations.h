#ifndef FIELD_OPERATIONS_TETRIS_H
#define FIELD_OPERATIONS_TETRIS_H

/**
 * @file
 * @brief функции, выполняющие операции над игровым полем и падающей фигурой
 */

#include "../../common/common_classes.h"
#include "matrix_operations.h"

/// @brief сдвиг фигуры на один ряд ниже
/// @param info информация об игре
/// @return 0 - фигура не сдвинута, 1 - сдвинута
int shift_down(GameInfo_t *info);

/// @brief проверка возможности сдвига вниз
/// @param info информация об игре
/// @return 0 - нельзя сдвинуть фигуру вниз, 1 - можно
int check_down(GameInfo_t *info);

/// @brief сдвиг фигуры на один ряд левее
/// @param info информация об игре
void shift_left(GameInfo_t *info);

/// @brief проверка возмодности сдвига влево
/// @param info информация об игре
/// @return 0 - нельзя сдвинуть фигуру влево, 1 - можно
int check_left(GameInfo_t *info);

/// @brief сдвиг фигуры на один ряд вправо
/// @param info информация об игре
void shift_right(GameInfo_t *info);

/// @brief проверка возмодности сдвига вправо
/// @param info информация об игре
/// @return 0 - нельзя сдвинуть фигуру вправо, 1 - можно
int check_right(GameInfo_t *info);

/// @brief проверка коллизий - возможности поворота фигуры
/// @param info структура с повернутой фигурой
/// @return 0 - нет коллизий, 1 - есть коллизии
int check_collide(GameInfo_t *info);

/// @brief дроп фигуры
/// @param info информация об игре
void drop_down(GameInfo_t *info);

/// @brief прикрепление фигуры ко дну или ранее прикрепленным фигурам
/// @param info информация об игре
void attach(GameInfo_t *info);

/// @brief проверка заполненности верхнего ряда
/// @param info информация об игре
/// @return 0 - ряд пуст, 1 - ряд не пуст
int check_ceiling(GameInfo_t *info);

/// @brief проверка заполненности ряда по индексу
/// @param info информация об игре
/// @param idx индекс ряда
/// @return 0 – ряд заполнен не полностью, 1 – полностью
int check_row_filling_by_idx(GameInfo_t *info, int idx);

/// @brief сдвиг поля на один уровень вниз
/// @param info информация об игре
void move_field_down(GameInfo_t *info);

/// @brief подсчет заполненных рядов снизу
/// @param info информация об игре
/// @return количество заполненных рядов снизу
int count_filled_rows(GameInfo_t *info);

/// @brief получить поле с границами
/// @details поле игры из GameInfo_t имеет строгий размер 20х10. Для проверок
/// смещения в стороны и вниз удобно было бы иметь "стенки" - столбцы и строки
/// по краям поля, заполненные числами
/// @param field игровое поле 20х10 без стенок
/// @return игровое поле со стенками
int **get_field_with_borders(int **field);
#endif