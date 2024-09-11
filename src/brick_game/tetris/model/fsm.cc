#include "fsm.h"

StateMachine_tetris *init_state_machine_tetris() {
  StateMachine_tetris *state =
      (StateMachine_tetris *)malloc(sizeof(StateMachine_tetris));
  *state = START_STATE;
  return state;
}

StateMachine_tetris *current_state_machine(StateMachine_tetris *machine) {
  static StateMachine_tetris *state = NULL;
  if (machine == NULL) return state;
  state = machine;
  return state;
}

void destroy_state_machine() {
  StateMachine_tetris *machine = current_state_machine(NULL);
  if (machine) free(machine);
}

void user_input(UserAction_t action) {
  if (!check_tick_limit()) moving_timer_has_expired();
  GameInfo_t *info = current_game_info(NULL);
  StateMachine_tetris *state = current_state_machine(NULL);
  switch (action) {
    case START: {
      if (*state == START_STATE) {
        *state = SPAWN_STATE;
        free(info->bottom_text);
        info->bottom_text = NULL;
        sigact();
      } else if (*state == GAME_OVER_STATE) {
        *state = START_STATE;
        sigact();
      }
      break;
    }
    case PAUSE: {
      if (*state == MOVING_STATE && !info->pause) {
        *state = PAUSE_STATE;
        sigact();
      } else if (*state == PAUSE_STATE && info->pause) {
        info->pause = false;
        copy_matrix(info->field, info->field_copy, FIELD_ROWS, FIELD_COLUMNS);
        free(info->bottom_text);
        info->bottom_text = NULL;
        get_tick_limit();
        *state = MOVING_STATE;
      }
      break;
    }
    case TERMINATE: {
      if (*state == START_STATE || *state == GAME_OVER_STATE) {
        *state = EXIT_STATE;
        sigact();
      } else if (*state != PAUSE_STATE) {
        *state = START_STATE;
        sigact();
      }
      break;
    }
    case LEFT: {
      if (*state == MOVING_STATE) {
        shift_left(info);
      }
      break;
    }
    case RIGHT: {
      if (*state == MOVING_STATE) {
        shift_right(info);
      }
      break;
    }
    case DOWN: {
      if (*state == MOVING_STATE) {
        drop_down(info);
        *state = ATTACHING_STATE;
        sigact();
      }
      break;
    }
    case ACTION: {
      if (*state == MOVING_STATE) rotate_tetramino();
      break;
    }
    default:
      break;
  }
}

void sigact() {
  StateMachine_tetris *state = current_state_machine(NULL);
  GameInfo_t *info = current_game_info(NULL);
  bool break_flag = false;
  while (!break_flag) {
    switch (*state) {
      case START_STATE: {
        clear_game_info_tetris();
        add_greeting(info);
        break_flag = true;
        break;
      }
      case SPAWN_STATE: {
        drop_new_tetramino();
        get_next_tetramino(info);
        get_tick_limit();
        *state = MOVING_STATE;
        break;
      }
      case MOVING_STATE: {
        break_flag = true;
        break;
      }
      case PAUSE_STATE: {
        prepare_pause_screen();
        info->pause = true;
        break_flag = true;
        break;
      }
      case SHIFTING_STATE: {
        int shifted = shift_down(info);
        if (shifted) {
          get_tick_limit();
          *state = MOVING_STATE;
        } else {
          *state = ATTACHING_STATE;
        }
        break;
      }
      case ATTACHING_STATE: {
        attach(info);
        if (check_ceiling(info)) {
          *state = GAME_OVER_STATE;
        } else {
          handle_bottom_filling();
          *state = SPAWN_STATE;
        }
        break;
      }
      case GAME_OVER_STATE: {
        update_user_record(current_game_info(NULL)->user_name,
                           current_game_info(NULL)->score, TETRIS_ID);
        prepare_game_over_screen();
        break_flag = true;
        break;
      }
      case EXIT_STATE: {
        info->score = -1;
        break_flag = true;
        break;
      }
    }
  }
}

void moving_timer_has_expired() {
  StateMachine_tetris *state = current_state_machine(NULL);
  if (*state == MOVING_STATE) {
    *state = SHIFTING_STATE;
    sigact();
  }
}