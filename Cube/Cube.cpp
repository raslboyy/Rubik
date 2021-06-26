#include "Cube.h"

#include <sstream>
#include <algorithm>

const std::vector<std::vector<char>> Cube::Rotate::order_ = {
    {Cube::FRONT, Cube::LEFT, Cube::BACK, Cube::RIGHT}, // UP
    {Cube::FRONT, Cube::RIGHT, Cube::BACK, Cube::LEFT}, // DOWN
    {Cube::UP, Cube::FRONT, Cube::DOWN, Cube::BACK}, // LEFT
    {Cube::UP, Cube::BACK, Cube::DOWN, Cube::FRONT}, // RIGHT
    {Cube::UP, Cube::RIGHT, Cube::DOWN, Cube::LEFT}, // FRONT
    {Cube::UP, Cube::LEFT, Cube::DOWN, Cube::RIGHT} // BACK
};

const std::vector<std::vector<bool>> Cube::Rotate::is_reverse_ = {
    {false, false, false, false},
    {false, false, false, false},
    {false, false, true, true},
    {true, true, false, false},
    {false, true, false, true},
    {true, false, true, false},
};

const std::vector<std::vector<bool>> Cube::Rotate::is_row_ = {
    {true, true, true, true},
    {true, true, true, true},
    {false, false, false, false},
    {false, false, false, false},
    {true, false, true, false},
    {true, false, true, false},
};

const std::vector<std::vector<bool>> Cube::Rotate::is_normal_deep_ = {
    {true, true, true, true},
    {false, false, false, false},
    {true, true, true, false},
    {false, true, false, false},
    {false, true, true, false},
    {true, true, false, false},
};

Cube::Cube(size_t n) :
    n_(n),
    rotation(*this) {
  for (int i = 0; i < 6; i++)
    faces_.emplace_back(n, i);
}

char Cube::get(char face, size_t i, size_t j) const {
  // проверка face
  return faces_[0].get(i, j);
}

void Cube::scramble(const std::string &s) {
  // проверка
  std::stringstream ss(s);
  std::string command;
  while (ss >> command)
    Command(command).solve(this);
}

std::ostream &operator<<(std::ostream &os, const Cube &c) {
  os << "UP:" << Cube::UP << '\n' << c.faces_[c.UP];
  os << "DOWN:" << Cube::DOWN << '\n' << c.faces_[c.DOWN];
  os << "LEFT:" << Cube::LEFT << '\n' << c.faces_[c.LEFT];
  os << "RIGHT:" << Cube::RIGHT << '\n' << c.faces_[c.RIGHT];
  os << "FRONT:" << Cube::FRONT << '\n' << c.faces_[c.FRONT];
  os << "BACK:" << Cube::BACK << '\n' << c.faces_[c.BACK];
  return os;
}

Cube::Command::Command(const std::string &s) {
  size_t k = std::string::npos;
  int i = 0;
  std::string commands = "UDLRFB";
  while (k == std::string::npos)
    k = s.find(commands[i++]);
  deep_ = std::stoul(s.substr(0, k)) - 1;
  count_ = std::stoul(s.substr(k + 1, s.size() - k - 1));
  type_ = i - 1;
}

void Cube::Rotate::operator()(char face, unsigned deep) {
  if (deep == 0)
    cube.get(face).rotate();
  std::vector<std::vector<char>> t;
  std::vector<char> order = order_[face];
  std::vector<bool> is_row = is_row_[face];
  std::vector<bool> is_normal_deep = is_normal_deep_[face];
  std::vector<bool> is_reverse = is_reverse_[face];

  t.reserve(4);
  for (int i = 0; i < 4; i++) {
    if (is_row[i])
      t.push_back(cube.get(order[i]).get_row(is_normal_deep[i] ? deep : cube.n() - 1 - deep));
    else
      t.push_back(cube.get(order[i]).get_col(is_normal_deep[i] ? deep : cube.n() - 1 - deep));

    if (is_reverse[i])
      std::reverse(t[i].begin(), t[i].end());
  }

  for (int i = 0; i < 4; i++) {
    char cur = i;
    char next = (i + 1) % 4;
    if (is_row[next])
      cube.get(order[next]).set_row(is_normal_deep[next] ? deep : cube.n() - 1 - deep, t[cur]);
    else
      cube.get(order[next]).set_col(is_normal_deep[next] ? deep : cube.n() - 1 - deep, t[cur]);
  }
}
