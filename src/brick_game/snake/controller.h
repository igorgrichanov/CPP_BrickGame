#ifndef CONTROLLER_SNAKE_H
#define CONTROLLER_SNAKE_H

#include "model/model.h"

/**
 * @file
 * @brief контроллер игры "Змейка"
 */

namespace brickGame {
/**
 * @class SnakeController класс контроллера змейки
 *
 */
class SnakeController final : public Controller {
 public:
  SnakeController(char *user_name, Model *model = nullptr);
  ~SnakeController();

  /**
   * @brief обработка ввода пользователя
   *
   * @param action ввод пользователя
   */
  void userInput(UserAction_t action) noexcept override;

 private:
  Model *model_;
};
}  // namespace brickGame

#endif