#include "controller.h"

namespace brickGame {
SnakeController::SnakeController(char *user_name, Model *model)
    : model_(model) {
  if (!model) model_ = new Model(user_name);
}

SnakeController::~SnakeController() { delete model_; }

void SnakeController::userInput(UserAction_t action) noexcept {
  model_->userInput(action);
}
}  // namespace brickGame