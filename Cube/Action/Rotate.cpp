#include "Rotate.h"

#include "../Cube.h"

auto &Rotate::GetOrder() {
  static std::vector<std::vector<SIDE>> order = {
      //UP, DOWN, LEFT, RIGHT, FRONT, BACK
      {SIDE::BACK, SIDE::FRONT, SIDE::LEFT, SIDE::RIGHT, SIDE::UP, SIDE::DOWN}, // UP
      {SIDE::FRONT, SIDE::BACK, SIDE::LEFT, SIDE::RIGHT, SIDE::DOWN, SIDE::UP}, // DOWN
      {SIDE::UP, SIDE::DOWN, SIDE::BACK, SIDE::FRONT, SIDE::LEFT, SIDE::RIGHT}, // LEFT
      {SIDE::UP, SIDE::DOWN, SIDE::FRONT, SIDE::BACK, SIDE::RIGHT, SIDE::LEFT}, // RIGHT
  };
  return order;
}
auto &Rotate::GetRotate() {
  static std::vector<std::vector<int>> rotate = {
      //UP, DOWN, LEFT, RIGHT, FRONT, BACK
      {0, 2, 1, 3, 0, 2}, // UP
      {2, 0, 3, 1, 0, 2}, // DOWN
      {3, 1, 0, 0, 0, 0}, // LEFT
      {1, 3, 0, 0, 0, 0} // RIGHT
  };
  return rotate;
}

const IAction &Rotate::operator()(Cube &cube) const {
  for (size_t i = 0; i != 6; i++)
    for (size_t j = 0; j != GetRotate()[type_][i]; j++)
      cube.sides[i].rotate();

  std::vector<Side> t;
  for (auto &side : GetOrder()[type_])
    t.emplace_back(cube.get(side));
  cube.sides = t;
  return *this;
}
std::string Rotate::to_string() const {
  static std::string commands = "0123";
  return std::string(1, commands[type_]);
}