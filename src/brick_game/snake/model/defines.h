#ifndef DEFINES_SNAKE_H
#define DEFINES_SNAKE_H

#include "../../common/common_defines.h"

/**
 * @file
 * @brief определение констант, используемых в игре "Змейка"
 */

namespace brickGame {

#define SNAKE_DEFAULT_X 2
#define SNAKE_DEFAULT_Y 10
#define SNAKE_DEFAULT_LENGTH 4
#define MAX_SCORE 200 - SNAKE_DEFAULT_LENGTH
#define SNAKE_COLOR 3
#define APPLE_COLOR 4
#define APPLE_DEFAULT_X SNAKE_DEFAULT_X + SNAKE_DEFAULT_LENGTH + 3
#define APPLE_DEFAULT_Y SNAKE_DEFAULT_Y

}  // namespace brickGame

#endif