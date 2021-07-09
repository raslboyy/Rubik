#include "Cube.h"

#include <sstream>
#include <algorithm>
#include <ctime>

const std::vector<std::vector<char>> Cube::Rotation::order_ = {
    {Cube::FRONT, Cube::LEFT, Cube::BACK, Cube::RIGHT}, // UP
    {Cube::FRONT, Cube::RIGHT, Cube::BACK, Cube::LEFT}, // DOWN
    {Cube::UP, Cube::FRONT, Cube::DOWN, Cube::BACK}, // LEFT
    {Cube::UP, Cube::BACK, Cube::DOWN, Cube::FRONT}, // RIGHT
    {Cube::UP, Cube::RIGHT, Cube::DOWN, Cube::LEFT}, // FRONT
    {Cube::UP, Cube::LEFT, Cube::DOWN, Cube::RIGHT} // BACK
};

const std::vector<std::vector<bool>> Cube::Rotation::is_reverse_ = {
    {false, false, false, false},
    {false, false, false, false},
    {false, false, true, true},
    {true, true, false, false},
    {false, true, false, true},
    {true, false, true, false},
};

const std::vector<std::vector<bool>> Cube::Rotation::is_row_ = {
    {true, true, true, true},
    {true, true, true, true},
    {false, false, false, false},
    {false, false, false, false},
    {true, false, true, false},
    {true, false, true, false},
};

const std::vector<std::vector<bool>> Cube::Rotation::is_normal_deep_ = {
    {true, true, true, true},
    {false, false, false, false},
    {true, true, true, false},
    {false, true, false, false},
    {false, true, true, false},
    {true, true, false, false},
};

Cube::Cube(size_t n) :
    n_(n) {
  for (int i = 0; i < 6; i++)
    faces.emplace_back(n, i);
}

char Cube::get(char face, size_t i, size_t j) const {
  // проверка face
  return faces[0][i][j];
}

void Cube::scramble(const std::string &s) {
  // проверка
  std::stringstream ss(s);
  std::string command;
  while (ss >> command)
    move(command).operator()(*this);
}

std::string Cube::scramble(size_t count) {
  srand(time(NULL));
  std::string s;
  if (count == 0)
    count = std::rand() % 90 + 10;
  std::string commands = "UDLRFB";
  while (count--)
    s += std::to_string(1 + rand() % (n_ - 1)) + commands[rand() % 6] + std::to_string(1 + rand() % 2) + " ";
  scramble(s);
  return s;
}

std::ostream &operator<<(std::ostream &os, const Cube &c) {
  os << "UP:" << Cube::UP << '\n' << c.faces[c.UP];
  os << "DOWN:" << Cube::DOWN << '\n' << c.faces[c.DOWN];
  os << "LEFT:" << Cube::LEFT << '\n' << c.faces[c.LEFT];
  os << "RIGHT:" << Cube::RIGHT << '\n' << c.faces[c.RIGHT];
  os << "FRONT:" << Cube::FRONT << '\n' << c.faces[c.FRONT];
  os << "BACK:" << Cube::BACK << '\n' << c.faces[c.BACK];
  return os;
}
std::vector<Cube::move> Cube::solve() {

  return std::vector<move>();
}
unsigned Cube::fitness() const {
  unsigned count = 0;
  for (char i = 0; i < 6; i++)
    count += faces[i].count_without(i);
  return count;
}
Cube::Cube(std::vector<Side> &m) : faces(m), n_(m[0].n()) {}

//void Cube::switch_view(char c) {
//  switch (c) {
//    case '<':
////      view(*this, LEFT);
//  }
//}

Cube::move::move(const std::string &s) {
  size_t k = std::string::npos;
  int i = 0;
  constexpr auto moves = "UDLRFB";
  while (k == std::string::npos)
    k = s.find(moves[i++]);
  if (s.substr(0, k).empty())
    deep_ = 0;
  else
    deep_ = std::stoul(s.substr(0, k)) - 1;

  if (s.substr(k + 1, s.size() - k - 1).empty())
    count_ = 1;
  else {
    if (s[k + 1] == '\'')
      count_ = 3;
    else
      count_ = std::stoul(s.substr(k + 1, s.size() - k - 1));
  }

  type_ = i - 1;
}
void Cube::move::operator()(Cube &cube) const {
  for (unsigned i = 0; i != count_; i++)
    rotation(cube, type_, deep_);
}
std::string Cube::move::to_string() const {
  std::string moves = "UDLRFB";
  return std::to_string(deep_) + moves[type_] + std::to_string(count_);
}

void Cube::Rotation::operator()(Cube &cube, char face, unsigned deep) const {
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
      t.emplace_back(cube.get(order[i]).get_row(is_normal_deep[i] ? deep : cube.n() - 1 - deep));
    else
      t.emplace_back(cube.get(order[i]).get_column(is_normal_deep[i] ? deep : cube.n() - 1 - deep));

    if (is_reverse[i])
      std::reverse(t[i].begin(), t[i].end());
  }

  for (int i = 0; i < 4; i++) {
    char cur = i;
    char next = (i + 1) % 4;
    if (is_row[next])
      cube.get(order[next]).set_row(is_normal_deep[next] ? deep : cube.n() - 1 - deep, t[cur]);
    else
      cube.get(order[next]).set_column(is_normal_deep[next] ? deep : cube.n() - 1 - deep, t[cur]);
  }
}

void Cube::View::operator()(Cube &cube, unsigned int to) const {
  if (to == UP)
    cube.faces =
        {cube.faces[BACK], cube.faces[FRONT], cube.faces[LEFT], cube.faces[RIGHT], cube.faces[UP], cube.faces[DOWN]};
  else if (to == DOWN)
    cube.faces =
        {cube.faces[FRONT], cube.faces[BACK], cube.faces[LEFT], cube.faces[RIGHT], cube.faces[DOWN], cube.faces[UP]};
  else if (to == LEFT)
    cube.faces =
        {cube.faces[UP], cube.faces[DOWN], cube.faces[BACK], cube.faces[FRONT], cube.faces[LEFT], cube.faces[RIGHT]};
  else if (to == RIGHT)
    cube.faces =
        {cube.faces[UP], cube.faces[DOWN], cube.faces[FRONT], cube.faces[BACK], cube.faces[RIGHT], cube.faces[LEFT]};
}
