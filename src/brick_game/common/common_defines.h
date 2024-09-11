#ifndef COMMON_DEFINES_H
#define COMMON_DEFINES_H

/**
 * @file
 * @brief объявление констант, общих для обеих игр
 */

#define USER_NAME_SIZE 255

#define FIELD_ROWS 20
#define FIELD_COLUMNS 10

#define TETRIS_ID 0
#define SNAKE_ID 1

/// отступ от границы окна терминала
#define BOARD 3

/// координаты рамки с игрой
#define TOP_T BOARD - 1
#define BOTTOM_T TOP_T + FIELD_ROWS + 1
#define LEFT_T BOARD
#define RIGHT_T LEFT_T + FIELD_COLUMNS + 1

/// координаты рамки с дополнительной информацией
#define TOP_A TOP_T
#define BOTTOM_A BOTTOM_T
#define LEFT_A RIGHT_T + 4
#define RIGHT_A LEFT_A + 10

/// координаты надписи SCORE
#define Y_SCORE TOP_A + 1
#define X_SCORE LEFT_A + 3

/// координаты рамки для SCORE
#define TOP_SCORE Y_SCORE + 1
#define BOTTOM_SCORE TOP_SCORE + 2
#define LEFT_SCORE LEFT_A + 2
#define RIGHT_SCORE RIGHT_A - 2

#define MAX_SCORE_LENGTH 5

/// координаты надписи BEST
#define Y_BEST BOTTOM_SCORE + 1
#define X_BEST LEFT_A + 3

/// координаты рамки для BEST
#define TOP_BEST Y_BEST + 1
#define BOTTOM_BEST TOP_BEST + 2
#define LEFT_BEST LEFT_SCORE
#define RIGHT_BEST RIGHT_SCORE

/// координаты надписи LEVEL
#define Y_LEVEL BOTTOM_BEST + 1
#define X_LEVEL LEFT_A + 3

/// координаты рамки для LEVEL
#define TOP_LEVEL Y_LEVEL + 1
#define BOTTOM_LEVEL TOP_LEVEL + 2
#define LEFT_LEVEL LEFT_BEST
#define RIGHT_LEVEL RIGHT_BEST

/// координаты надписи NEXT
#define Y_NEXT BOTTOM_LEVEL + 3
#define X_NEXT LEFT_A + 3

/// координаты рамки для NEXT
#define TOP_NEXT Y_NEXT + 1
#define BOTTOM_NEXT TOP_NEXT + 4
#define LEFT_NEXT LEFT_LEVEL
#define RIGHT_NEXT RIGHT_LEVEL

/// координаты welcome-текста
#define Y_WELCOME_TEXT TOP_T + 8
#define X_WELCOME_TEXT LEFT_T + 2

/// координаты надписи OPTIONS
#define Y_OPTIONS TOP_A + 7
#define X_OPTIONS RIGHT_A + 11

/// координаты рамки для OPTIONS
#define TOP_OPTIONS Y_OPTIONS + 1
#define BOTTOM_OPTIONS TOP_OPTIONS + 5
#define LEFT_OPTIONS RIGHT_A + 4
#define RIGHT_OPTIONS LEFT_OPTIONS + 21

/// координаты сообщения о победе и поражении
#define Y_WIN TOP_T + 7

/// частота обновления экрана и приема ввода от пользователя
#define UPD_FREQUENCY_MICROSECONDS 50000

#endif