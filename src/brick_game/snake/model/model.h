#ifndef MODEL_SHAKE_H
#define MODEL_SHAKE_H

#include <vector>

#include "defines.h"
#include "game_kernel.h"

/**
 * @file
 * @brief класс модели игры "Змейка"
 */

namespace brickGame {

/**
 * @class Model класс модели змейки, методы которого вызывает контроллер
 *
 */
class Model final {
 public:
  /**
   * @brief состояния конечного автомата змейки
   *
   */
  enum class State : unsigned int {
    START_STATE,
    SPAWN_STATE,
    MOVING_STATE,
    PAUSE_STATE,
    SHIFTING_STATE,
    END_STATE,
    EXIT_STATE
  };

  Model(char *user_name);
  ~Model();

  /**
   * @brief обработка ввода пользователя
   *
   * @param action ввод пользователя
   */
  void userInput(UserAction_t action) noexcept;

  /**
   * @brief сигнал о том, что время такта MOVING_STATE истекло
   *
   */
  void moving_timer_has_expired() noexcept;

  /**
   * @brief получить копию текущего состояния. Метод необходим для тестирования
   * класса
   *
   */
  State get_state() noexcept;

 private:
  GameKernel *kernel_;
  State state_;
  UserAction_t prev_action;  //< предыдущее нажатие пользователя. Необходимо для
                             // реализации ускорения

  /**
   * @brief конечный автомат игры "Змейка"
   *
   * @param action действие пользователя
   *
   */
  void sigact(UserAction_t action) noexcept;
};
}  // namespace brickGame

#endif