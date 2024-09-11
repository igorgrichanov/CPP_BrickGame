#ifndef SNAKE_H
#define SNAKE_H

#include <array>
#include <deque>
#include <exception>
#include <stdexcept>

#include "../../common/common_classes.h"
#include "defines.h"

/**
 * @file
 * @brief функции, выполняющие операции над полем и змейкой
 */

namespace brickGame {

/**
 * @class Segment класс, описывающий клетку поля, занятую яблоком или змейкой
 *
 */
class Segment final {
 public:
  Segment(int y, int x) : y_(y), x_(x) {}
  Segment(const Segment &other) = default;
  Segment(Segment &&other) = default;
  Segment &operator=(const Segment &other) = default;
  Segment &operator=(Segment &&other) = default;

  bool operator==(const Segment &other) noexcept;
  bool operator==(const Segment &other) const noexcept;

  /**
   * @brief ассессоры координат сегмента
   *
   * @details методы константные, так как не меняют поля объекта и вызываются из
   * константного итератора Snake
   *
   * @return int координата сегмента на поле
   */
  int get_y() const noexcept;
  int get_x() const noexcept;

 private:
  int y_;
  int x_;
};

/**
 * @class Snake класс змейки
 *
 */
class Snake final {
 public:
  /**
   * @brief создание объекта Snake
   *
   * @details вносит в поле snake_ позицию змейки по умолчанию
   */
  Snake();

  Snake(const Snake &other) = default;
  Snake &operator=(const Snake &other) = default;
  Snake(Snake &&other) = default;
  Snake &operator=(Snake &&other) = default;

  /**
   * @brief изменить направление движения змейки
   *
   * @details направление изменится в случае, если оно меняется на 90 градусов.
   * Иначе никаких изменений не произойдет
   *
   * @param direction новое направление движения
   *
   * @return true направление изменилось
   * @return false направление не изменилось
   */
  bool change_direction(UserAction_t direction) noexcept;

  /**
   * @brief движение вперед относительно текущего направления
   *
   * @exception яблоко имеет некорректные координаты
   *
   * @param apple позиция яблока

   * @return true яблоко съедено
   * @return false яблоко не съедено
   */
  bool move_forward(const Segment &apple);

  /**
   * @brief проверка столкновения змейки с самой собой
   *
   * @return true змейка столкнулась сама с собой
   * @return false змейка не столкнулась сама с собой
   */
  bool check_collide() noexcept;

  /**
   * @brief проверка выхода змейки за пределы поля
   *
   * @return true змейка вышла за пределы поля
   * @return false змейка не вышла за пределы поля
   */
  bool check_out_of_bounds() noexcept;

  /**
   * @brief проверка, является ли клетка частью змейки
   *
   * @param other клетка для проверки
   * @return true клетка является частью змейки
   * @return false клетка не является частью змейки
   */
  bool is_part_of_snake(const Segment &other) noexcept;

  /// @brief получить длину змейки
  /// @return длина змейки от 4 до 200 включительно
  size_t size() noexcept;

  using const_iterator = std::deque<Segment>::const_iterator;

  const_iterator cbegin() const;
  const_iterator cend() const;

 private:
  std::deque<Segment> snake_;
  UserAction_t dir_ = RIGHT;

  /// поле, описывающее возможные повороты змейки. Для каждого элемента массива
  /// с индексом от 1 до n-1 поворот возможен в направлении, заданном соседними
  /// элементами в массиве
  std::array<UserAction_t, 6> possible_dirs = {UP,   RIGHT, DOWN,
                                               LEFT, UP,    RIGHT};

  /**
   * @brief вытянуть змейку по направлению движения
   *
   * @details хвост остается на месте, а голова перемещается на одну клетку
   * вперед
   */
  void stretch_out_forward() noexcept;
};
}  // namespace brickGame

#endif