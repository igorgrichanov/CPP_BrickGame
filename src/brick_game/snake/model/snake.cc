#include "snake.h"

namespace brickGame {
bool Segment::operator==(const Segment &other) noexcept {
  return y_ == other.y_ && x_ == other.x_;
}

bool Segment::operator==(const Segment &other) const noexcept {
  return y_ == other.y_ && x_ == other.x_;
}

int Segment::get_y() const noexcept { return y_; }

int Segment::get_x() const noexcept { return x_; }

Snake::Snake() {
  for (int i = 0; i < SNAKE_DEFAULT_LENGTH; ++i) {
    snake_.push_back(Segment(SNAKE_DEFAULT_Y, SNAKE_DEFAULT_X + i));
  }
}

bool Snake::change_direction(UserAction_t new_dir) noexcept {
  bool changed = false;
  for (size_t i = 1; i < possible_dirs.size() - 1; ++i) {
    if (dir_ == possible_dirs[i]) {
      if (new_dir == possible_dirs[i - 1] || new_dir == possible_dirs[i + 1]) {
        changed = true;
        dir_ = new_dir;
      }
    }
  }
  return changed;
}

bool Snake::move_forward(const Segment &apple) {
  for (size_t i = 0; i < snake_.size(); ++i) {
    if (apple == snake_[i]) {
      throw std::invalid_argument(
          "Apple is placed on the same cell as the part of Snake");
    }
  }
  if (apple.get_y() >= FIELD_ROWS || apple.get_x() >= FIELD_COLUMNS ||
      apple.get_y() < 0 || apple.get_x() < 0) {
    throw std::invalid_argument("Apple is placed outside the field");
  }
  stretch_out_forward();
  if (snake_.back() == apple)
    return true;
  else
    snake_.pop_front();
  return false;
}

bool Snake::check_collide() noexcept {
  Segment head = snake_.back();
  for (size_t i = 0; i < snake_.size() - 1; ++i) {
    if (head == snake_[i]) {
      return true;
    }
  }
  return false;
}

bool Snake::check_out_of_bounds() noexcept {
  int y = snake_.back().get_y(), x = snake_.back().get_x();
  if (y == -1 || y == FIELD_ROWS || x == -1 || x == FIELD_COLUMNS) return true;
  return false;
}

bool Snake::is_part_of_snake(const Segment &other) noexcept {
  for (const_iterator it = cbegin(); it != cend(); ++it) {
    if (*it == other) return true;
  }
  return false;
}

size_t Snake::size() noexcept { return snake_.size(); }

Snake::const_iterator Snake::cbegin() const { return snake_.cbegin(); }

Snake::const_iterator Snake::cend() const { return snake_.cend(); }

void Snake::stretch_out_forward() noexcept {
  int y = snake_.back().get_y(), x = snake_.back().get_x();
  switch (dir_) {
    case UP:
      snake_.push_back(Segment(y - 1, x));
      break;
    case DOWN:
      snake_.push_back(Segment(y + 1, x));
      break;
    case LEFT:
      snake_.push_back(Segment(y, x - 1));
      break;
    case RIGHT:
      snake_.push_back(Segment(y, x + 1));
      break;
    default:
      break;
  }
}
}  // namespace brickGame