#include "common_functions.h"

int parse_user_record(char *line_from_file, char *user_name) {
  int result = -1;
  if (!strncmp(user_name, line_from_file, strlen(user_name))) {
    char *result_str = strtok(line_from_file, " ");
    result_str = strtok(NULL, " ");
    result = (int)atof(result_str);
  }
  return result;
}

int load_user_record(char *user_name, int game) {
  int result = -1;
  char line_from_file[USER_RECORD_LINE_LENGTH] = {0}, *read = NULL;
  FILE *fp = NULL;
  if (game == TETRIS_ID) {
    fp = fopen("build/tetris_record.txt", "r+");
  } else if (game == SNAKE_ID) {
    fp = fopen("build/snake_record.txt", "r+");
  }
  if (fp) {
    while ((read = fgets(line_from_file, USER_RECORD_LINE_LENGTH, fp)) !=
               NULL &&
           result == -1) {
      result = parse_user_record(line_from_file, user_name);
    }
  }

  if (result == -1) {
    if (fp) fprintf(fp, "%s %d\n", user_name, 0);
    result = 0;
  }
  if (fp) fclose(fp);
  return result;
}

void update_user_record(char *user_name, int new_record, int game) {
  int prev_record = load_user_record(user_name, game);
  if (new_record > prev_record) {
    FILE *fp = NULL;
    if (game == TETRIS_ID) {
      fp = fopen("build/tetris_record.txt", "r");
    } else if (game == SNAKE_ID) {
      fp = fopen("build/snake_record.txt", "r");
    }
    FILE *fp_copy = fopen("tmp.txt", "w");
    char line_from_file[USER_RECORD_LINE_LENGTH] = {0}, *read = NULL;
    if (fp) {
      while ((read = fgets(line_from_file, USER_RECORD_LINE_LENGTH, fp)) !=
             NULL) {
        if (!strncmp(user_name, line_from_file, strlen(user_name))) {
          fprintf(fp_copy, "%s %d\n", user_name, new_record);
        } else {
          fprintf(fp_copy, "%s", line_from_file);
        }
      }
    }
    fclose(fp_copy);
    if (game == TETRIS_ID) {
      if (fp) {
        fclose(fp);
        remove("build/tetris_record.txt");
        rename("tmp.txt", "build/tetris_record.txt");
      }
    } else if (game == SNAKE_ID) {
      if (fp) {
        fclose(fp);
        remove("build/snake_record.txt");
        rename("tmp.txt", "build/snake_record.txt");
      }
    }
  }
}

void get_tick_limit() {
  struct timespec *start = (struct timespec *)malloc(sizeof(struct timespec));
  clock_gettime(CLOCK_REALTIME, start);
  GameInfo_t *info = current_game_info(NULL);
  long tick_ns = info->delay * 1000 * 1000;
  long start_nsec_left = 999999999 - start->tv_nsec;
  if (start_nsec_left < tick_ns) {
    info->tick_end_time->tv_sec = start->tv_sec + 1;
    info->tick_end_time->tv_nsec = tick_ns - start_nsec_left;
  } else {
    info->tick_end_time->tv_sec = start->tv_sec;
    info->tick_end_time->tv_nsec = start->tv_nsec + tick_ns;
  }
  free(start);
}

int check_tick_limit() {
  GameInfo_t *info = current_game_info(NULL);
  struct timespec *now = (struct timespec *)malloc(sizeof(struct timespec));
  clock_gettime(CLOCK_REALTIME, now);
  int result = 0;
  if (now->tv_sec < info->tick_end_time->tv_sec)
    result = 1;
  else if (now->tv_sec == info->tick_end_time->tv_sec &&
           now->tv_nsec < info->tick_end_time->tv_nsec)
    result = 1;

  free(now);
  return result;
}

void add_greeting(GameInfo_t *info) {
  if (!info->bottom_text) info->bottom_text = (char *)calloc(sizeof(char), 256);
  strcat(info->bottom_text, "Hi, ");
  strcat(info->bottom_text, info->user_name);
  strcat(info->bottom_text, "!\n   ");
  add_init_text(info);
}

void add_init_text(GameInfo_t *info) {
  if (!info->bottom_text) info->bottom_text = (char *)calloc(sizeof(char), 256);
  strcat(info->bottom_text, "Press ENTER to start\n   Press \"q\" to quit");
}

void prepare_win_screen() {
  GameInfo_t *info = current_game_info(NULL);
  info->game_won = true;
  clear_matrix(info->field, FIELD_ROWS, FIELD_COLUMNS);
  char win_text[] = "YOU WON!";
  for (int i = 0; i < 8; ++i) {
    info->field[Y_WIN][i] = win_text[i];
  }
  add_init_text(info);
}

void prepare_game_over_screen() {
  GameInfo_t *info = current_game_info(NULL);
  info->game_over = true;
  clear_matrix(info->field, FIELD_ROWS, FIELD_COLUMNS);
  char game_over_text[] = "GAME OVER";
  for (int i = 0; i < 9; ++i) {
    info->field[Y_WIN][i] = game_over_text[i];
  }
  add_init_text(info);
}

void prepare_pause_screen() {
  GameInfo_t *info = current_game_info(NULL);
  copy_matrix(info->field_copy, info->field, FIELD_ROWS, FIELD_COLUMNS);
  clear_matrix(info->field, FIELD_ROWS, FIELD_COLUMNS);
  char pause_text[] = "PAUSE";
  for (int i = 0; i < 5; ++i) {
    info->field[Y_WIN][3 + i] = pause_text[i];
  }
  if (info->bottom_text) free(info->bottom_text);
  info->bottom_text = (char *)calloc(sizeof(char), 256);
  strcat(info->bottom_text, "Tap \'p\' to continue");
}