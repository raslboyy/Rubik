#include "Cube.h"

#include <sstream>
#include <algorithm>

const std::vector<std::vector<char>> Cube::Rotate::order = {{Cube::FRONT, Cube::LEFT, Cube::BACK, Cube::RIGHT},
                                                            {Cube::FRONT, Cube::RIGHT, Cube::BACK, Cube::LEFT},
                                                            {Cube::UP, Cube::FRONT, Cube::DOWN, Cube::BACK},
                                                            {Cube::UP, Cube::BACK, Cube::DOWN, Cube::FRONT},
                                                            {Cube::UP, Cube::RIGHT, Cube::DOWN, Cube::LEFT},
                                                            {Cube::UP, Cube::LEFT, Cube::DOWN, Cube::RIGHT}};

Cube::Cube(size_t n) :
    n_(n),
    rotation(this) {
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

void Cube::Rotate::operator()(char face, unsigned deep_) {
  // проверка
  if (deep_ == 0)
    c_->faces_[face].rotate();
  std::vector<std::vector<char>> t;
  auto current_order = order[face];

  if (face == Cube::DOWN || face == Cube::RIGHT || face == Cube::FRONT)
    deep_ = c_->n_ - deep_ - 1;

  if (face == Cube::RIGHT || face == Cube::LEFT)
    for (auto i : order[face])
      c_->faces_[i].rotate();

  std::vector<unsigned> deep(4, deep_);

  if (face == Cube::FRONT || face == Cube::BACK) {
    c_->faces_[Cube::LEFT].rotate_();
    deep[find(current_order.begin(), current_order.end(), Cube::LEFT) - current_order.begin()] =
        c_->n() - 1 - deep[find(current_order.begin(), current_order.end(), Cube::LEFT) - current_order.begin()];

    c_->faces_[Cube::RIGHT].rotate_();
  }

  if (face == Cube::RIGHT || face == Cube::LEFT)
    deep[find(current_order.begin(), current_order.end(), Cube::BACK) - current_order.begin()] =
        c_->n() - 1 - deep[find(current_order.begin(), current_order.end(), Cube::BACK) - current_order.begin()];

  t.reserve(4);
  for (int i = 0; i < 4; i++)
    t.push_back(c_->faces_[current_order[i]].get_row(deep[i]));
  for (int i = 0; i < 4; i++)
    c_->faces_[current_order[i]].set_row(deep[i], t[(i - 1 + 4) % 4]);

  if (face == Cube::RIGHT || face == Cube::LEFT)
    for (auto i : order[face])
      c_->faces_[i].rotate_();

  if (face == Cube::FRONT || face == Cube::BACK) {
    c_->faces_[Cube::LEFT].rotate();
    c_->faces_[Cube::RIGHT].rotate_();
  }
}
