#include "common_classes.h"

GameInfo_t *current_game_info(GameInfo_t *game_info) {
  static GameInfo_t *info = NULL;
  if (game_info == NULL) return info;
  info = game_info;
  return info;
}

GameInfo_t updateCurrentState() {
  GameInfo_t *game_info = current_game_info(NULL);
  return *game_info;
}

void destroy_moving(moving_t *moving_info) {
  if (moving_info) {
    remove_matrix(moving_info->figure);
    free(moving_info);
  }
}

void destroy_game_info() {
  GameInfo_t *info = current_game_info(NULL);
  if (info) {
    if (info->field) remove_matrix(info->field);
    if (info->field_copy) remove_matrix(info->field_copy);
    if (info->next) remove_matrix(info->next);
    destroy_moving(info->moving);
    if (info->bottom_text) free(info->bottom_text);
    free(info->tick_end_time);
    free(info->user_name);
    free(info);
  }
}