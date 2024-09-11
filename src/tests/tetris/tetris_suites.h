#ifndef TESTS_TETRIS
#define TESTS_TETRIS

#include <check.h>
#include <unistd.h>

#include "../../brick_game/tetris/controller.h"
#include "../../brick_game/tetris/model/backend.h"
#include "string.h"

Suite *tetris_backend_test_suite();
Suite *matrix_test_suite();
Suite *tetris_field_test_suite();
Suite *tetris_controller_test_suite();

void get_next_test(GameInfo_t *info, int i);
void fill_bottom_test(GameInfo_t *info);

#endif