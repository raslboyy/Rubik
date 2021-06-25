#include "Cube.h"

#include <sstream>

const std::vector<std::vector<char>> Cube::adjacent_ = {{LEFT, BACK, RIGHT, FRONT},
                                                        {FRONT, RIGHT, BACK, LEFT},
                                                        {UP, BACK, DOWN, FRONT},
                                                        {FRONT, DOWN, BACK, UP},
                                                        {UP, RIGHT, DOWN, LEFT},
                                                        {LEFT, DOWN, RIGHT, UP}};

const std::string Command::commands  = "UDLRFB";

Cube::Cube(size_t n) :
    n_(n) {
  for (int i = 0; i < 6; i++)
    faces_.emplace_back(n, i);
}

char Cube::get(char face, size_t i, size_t j) const {
  // проверка face
  return faces_[0].get(i, j);
}

void Cube::rotation(char face, size_t deep) {
  // проверка deep < n_
  if (deep == 0)
    faces_[face].rotate();
  std::vector<std::vector<char>> t;
  if (face == LEFT || face == RIGHT) {
    if (face == RIGHT)
      deep = n_ - deep - 1;
    for (auto i : adjacent_[face])
      t.push_back(faces_[i].get_col(deep));
    for (int i = 0; i < 4; i++)
      faces_[adjacent_[face][(i + 1) % 4]].set_col(deep, t[i]);
  } else {
    for (auto i : adjacent_[face])
      t.push_back(faces_[i].get_row(deep));
    for (int i = 0; i < 4; i++)
      faces_[adjacent_[face][(i + 1) % 4]].set_row(deep, t[i]);
  }
}

void Cube::scramble(const std::string &s) {
  // проверка
  std::stringstream ss(s);
  std::string command;
  while (ss >> command)
    Command(command).solve(this);
}

std::ostream &operator<<(std::ostream &os, const Cube &c) {
  os << c.faces_[c.UP];
  os << c.faces_[c.DOWN];
  os << c.faces_[c.FRONT];
  os << c.faces_[c.RIGHT];
  os << c.faces_[c.BACK];
  os << c.faces_[c.LEFT];
  return os;
}

Command::Command(const std::string &s) {
  size_t k = std::string::npos;
  int i = 0;
  while (k == std::string::npos)
    k = s.find(commands[i++]);
  deep_ = std::stoul(s.substr(0, k));
  count_ = std::stoul(s.substr(k + 1, s.size() - k - 1));
  type_ = i-1;
}
