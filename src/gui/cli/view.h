#ifndef VIEW_CLI_H
#define VIEW_CLI_H

#include <unistd.h>

#include "../../brick_game/snake/controller.h"
#include "../../brick_game/tetris/controller.h"
#include "frontend.h"

/**
 * @file
 * @brief реализация класса ConsoleView, отвечающего за консольные игры
 */

namespace brickGame {
/**
 * @brief класс, отвечающий за отображение консольных игр отправку ввода
 * пользователя на контроллер
 *
 */
class ConsoleView final {
 public:
  ConsoleView(Controller *controller);
  void cli_event_loop() noexcept;

 private:
  Controller *controller_;

  /// @brief трансляция ввода пользователя в тип UserAction_t
  /// @param user_input ввод пользователя с клавиатуры
  /// @return ввод пользователя. NO_ACTION возвращается в случае отсутствия
  /// ввода
  UserAction_t get_signal(int user_input);
};
}  // namespace brickGame

#endif