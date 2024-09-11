#ifndef CONTROLLER_TETRIS_H
#define CONTROLLER_TETRIS_H

#include "model/fsm.h"

/**
 * @file
 * @brief контроллер игры "Тетрис"
 */

namespace brickGame {
/**
 * @class TetrisController класс контроллера тетриса
 *
 */
class TetrisController final : public Controller {
 public:
  /**
   * @brief обработка ввода пользователя
   *
   * @param action ввод пользователя
   */
  void userInput(UserAction_t action) noexcept override { user_input(action); }
};
}  // namespace brickGame

#endif