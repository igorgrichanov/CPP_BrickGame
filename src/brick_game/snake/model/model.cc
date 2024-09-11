#include "model.h"

namespace brickGame {
Model::Model(char* user_name)
    : kernel_(new GameKernel(user_name)),
      state_(State::START_STATE),
      prev_action(NO_ACTION) {}

Model::~Model() { delete kernel_; }

void Model::userInput(UserAction_t action) noexcept {
  if (!check_tick_limit()) moving_timer_has_expired();
  switch (action) {
    case START:
      if (state_ == State::START_STATE) {
        state_ = State::SPAWN_STATE;
        kernel_->free_bottom_text();
        sigact(action);
      } else if (state_ == Model::State::END_STATE) {
        state_ = State::START_STATE;
        sigact(action);
      }
      break;
    case PAUSE:
      if (state_ == State::MOVING_STATE) {
        state_ = State::PAUSE_STATE;
        sigact(action);
      } else if (state_ == State::PAUSE_STATE) {
        kernel_->recover_after_pause();
        get_tick_limit();
        state_ = State::MOVING_STATE;
      }
      break;
    case TERMINATE:
      if (state_ == State::START_STATE || state_ == State::END_STATE) {
        state_ = State::EXIT_STATE;
        sigact(action);
      } else if (state_ != State::PAUSE_STATE) {
        state_ = State::START_STATE;
        sigact(action);
      }
      break;
    case ACTION:
      if (state_ == State::MOVING_STATE && prev_action == action) {
        state_ = State::SHIFTING_STATE;
        prev_action = NO_ACTION;
        sigact(action);
      } else
        prev_action = action;
      break;
    case NO_ACTION:
      break;
    default:
      if (state_ == State::MOVING_STATE) sigact(action);
      break;
  }
}

void Model::moving_timer_has_expired() noexcept {
  if (state_ == State::MOVING_STATE) {
    state_ = State::SHIFTING_STATE;
    prev_action = NO_ACTION;
    sigact(NO_ACTION);
  }
}

Model::State Model::get_state() noexcept { return state_; }

void Model::sigact(UserAction_t action) noexcept {
  bool break_flag = false;
  while (!break_flag) {
    switch (state_) {
      case State::START_STATE: {
        kernel_->prepare_new_game();
        break_flag = true;
        break;
      }
      case State::SPAWN_STATE: {
        try {
          kernel_->generate_apple();
        } catch (const std::length_error& e) {
          std::cerr << e.what() << '\n';
        }
        kernel_->update_game_info();
        state_ = State::MOVING_STATE;
        get_tick_limit();
        break_flag = true;
        break;
      }
      case State::MOVING_STATE: {
        if (kernel_->change_direction(action))
          state_ = State::SHIFTING_STATE;
        else
          break_flag = true;
        break;
      }
      case State::PAUSE_STATE: {
        kernel_->prepare_for_pause();
        break_flag = true;
        break;
      }
      case State::SHIFTING_STATE: {
        bool is_apple_eaten = kernel_->shift_forward();
        if (is_apple_eaten) {
          kernel_->add_point();
          state_ = State::SPAWN_STATE;
        } else if (kernel_->check_game_over()) {
          state_ = State::END_STATE;
        } else {
          state_ = State::MOVING_STATE;
          get_tick_limit();
          kernel_->update_game_info();
          break_flag = true;
        }
        break;
      }
      case State::END_STATE: {
        kernel_->update_record();
        if (kernel_->get_score() == MAX_SCORE)
          prepare_win_screen();
        else
          prepare_game_over_screen();
        break_flag = true;
        break;
      }
      case State::EXIT_STATE: {
        kernel_->prepare_exit_state();
        break_flag = true;
        break;
      }
    }
  }
}
}  // namespace brickGame