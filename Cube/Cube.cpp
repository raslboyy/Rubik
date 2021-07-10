#include "Cube.h"

#include <sstream>
#include <algorithm>
#include <ctime>

#include "../Random.h"

Cube::Cube(size_t n) :
    n_(n),
    scramble_(n) {
  for (int i = 0; i < 6; i++)
    sides.emplace_back(n, i);
}
Cube::Cube(std::vector<Side> &m) : sides(m), n_(m[0].n()), scramble_(m[0].n()) {}

// fix count >
std::string Cube::random_scramble(size_t size) {
  auto new_scramble = dynamic_cast<const Scramble &>(Scramble(n(), size).operator()(*this));
  scramble_ += new_scramble;
  return new_scramble.to_string();
}

void Cube::apply_scramble(const std::string &s) {
  // проверка
  scramble_ += dynamic_cast<const Scramble &>(Scramble(n(), s).operator()(*this));
}

std::string Cube::get_scramble() const {
  return scramble_.to_string();
}

unsigned Cube::stupidFitness() const {
  unsigned count = 0;
  for (char i = 0; i < 6; i++)
    count += sides[i].count_without(i);
  return count;
}
unsigned Cube::layerFitness() const {
  return 0;
}

Cube::Move::Move(size_t n) :
    deep_(Random::randU32(n - 1)),
    count_(Random::randU32(1, 3)),
    side_(static_cast<SIDE>(Random::randU32(6))) {}
Cube::Move::Move(unsigned deep, unsigned count, SIDE side) :
    deep_(deep),
    count_(count),
    side_(side) {}
Cube::Move::Move(const std::string &s) {
  int i = 0;
  static std::string moves = "UDLRFB";
  size_t k = std::string::npos;
  while (k == std::string::npos)
    k = s.find(moves[i++]);
  side_ = static_cast<SIDE>(i - 1);

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
}

const Cube::IAction &Cube::Move::operator()(Cube &cube) const {
  for (int i = 0; i < count_; i++)
    operator()(cube, side_, deep_);
  return *this;
}
std::string Cube::Move::to_string() const {
  static std::string moves = "UDLRFB";
  return std::to_string(deep_ + 1) + moves[side_] + std::to_string(count_);
}

auto &Cube::Move::GetOrder() {
  static const std::vector<std::vector<SIDE>> order = {
      {Cube::FRONT, Cube::LEFT, Cube::BACK, Cube::RIGHT}, // UP
      {Cube::FRONT, Cube::RIGHT, Cube::BACK, Cube::LEFT}, // DOWN
      {Cube::UP, Cube::FRONT, Cube::DOWN, Cube::BACK}, // LEFT
      {Cube::UP, Cube::BACK, Cube::DOWN, Cube::FRONT}, // RIGHT
      {Cube::UP, Cube::RIGHT, Cube::DOWN, Cube::LEFT}, // FRONT
      {Cube::UP, Cube::LEFT, Cube::DOWN, Cube::RIGHT} // BACK
  };
  return order;
}
auto &Cube::Move::GetIsRow() {
  static const std::vector<std::vector<bool>> is_row = {
      {true, true, true, true},
      {true, true, true, true},
      {false, false, false, false},
      {false, false, false, false},
      {true, false, true, false},
      {true, false, true, false},
  };
  return is_row;
}
auto &Cube::Move::GetIsNormalDeep() {
  static const std::vector<std::vector<bool>> is_normal_deep = {
      {true, true, true, true},
      {false, false, false, false},
      {true, true, true, false},
      {false, true, false, false},
      {false, true, true, false},
      {true, true, false, false},
  };
  return is_normal_deep;
}
auto &Cube::Move::GetIsReverse() {
  static const std::vector<std::vector<bool>> is_reverse = {
      {false, false, false, false},
      {false, false, false, false},
      {false, false, true, true},
      {true, true, false, false},
      {false, true, false, true},
      {true, false, true, false},
  };
  return is_reverse;
}

void Cube::Move::operator()(Cube &cube, SIDE side, unsigned deep) const {
  if (deep == 0)
    cube.get(side).rotate();
  std::vector<std::vector<Side::byte>> t;
  auto order = GetOrder()[side];
  auto is_row = GetIsRow()[side];
  auto is_normal_deep = GetIsNormalDeep()[side];
  auto is_reverse = GetIsReverse()[side];

  t.reserve(4);
  for (int i = 0; i < 4; i++) {
    if (is_row[i])
      t.emplace_back(cube.get(order[i]).get_row(is_normal_deep[i] ? deep : cube.n() - 1 - deep));
    else
      t.emplace_back(cube.get(order[i]).get_column(is_normal_deep[i] ? deep : cube.n() - 1 - deep));

    if (is_reverse[i])
      std::reverse(t[i].begin(), t[i].end());
  }

  for (size_t i = 0; i < 4; i++) {
    size_t cur = i;
    size_t next = (i + 1) % 4;
    if (is_row[next])
      cube.get(order[next]).set_row(is_normal_deep[next] ? deep : cube.n() - 1 - deep, t[cur]);
    else
      cube.get(order[next]).set_column(is_normal_deep[next] ? deep : cube.n() - 1 - deep, t[cur]);
  }
}

auto &Cube::Rotate::GetOrder() {
  static std::vector<std::vector<SIDE>> order = {
      //UP, DOWN, LEFT, RIGHT, FRONT, BACK
      {BACK, FRONT, LEFT, RIGHT, UP, DOWN},
      {FRONT, BACK, LEFT, RIGHT, DOWN, UP},
      {UP, DOWN, BACK, FRONT, LEFT, RIGHT},
      {UP, DOWN, FRONT, BACK, RIGHT, LEFT},
  };
  return order;
}
const Cube::IAction &Cube::Rotate::operator()(Cube &cube) const {
  std::vector<Side> t;
  for (auto &side : GetOrder()[type_])
    t.emplace_back(cube.sides[side]);
  cube.sides = t;
  return *this;
}
std::string Cube::Rotate::to_string() const {
  static std::string commands = "0123";
  return std::string(1, commands[type_]);
}

Cube::Scramble::Scramble(size_t n, size_t size) : n_(n) {
  if (size == std::numeric_limits<size_t>::infinity())
    size = Random::randU32(10, 101);
  for (size_t i = 0; i < size; i++) {
    auto type = Random::randU32(1, 2);
    if (type == 0)
      scramble.emplace_back(new Skip());
    else if (type == 1)
      scramble.emplace_back(new Move(n_));
    else
      scramble.emplace_back(new Rotate());
  }
}
Cube::Scramble::Scramble(size_t n, const std::string &s) : n_(n) {
  std::stringstream ss(s);
  std::string command;
  while (ss >> command) {
    if (command == "-")
      scramble.emplace_back(new Skip());
    else if (command.size() == 1 and command[0] < '4')
      scramble.emplace_back(new Rotate(command));
    else
      scramble.emplace_back(new Move(command));
  }
}
const Cube::IAction &Cube::Scramble::operator()(Cube &cube) const {
  for (auto &pIAction : scramble)
    pIAction->operator()(cube);
  return *this;
}
std::string Cube::Scramble::to_string() const {
  std::string s;
  for (auto &pIAction : scramble)
    s += pIAction->to_string() + " ";
  return s;
}
Cube::Scramble &Cube::Scramble::operator+=(const Cube::Scramble &other) {
  for (auto &pIAction : other.scramble)
    scramble.emplace_back(pIAction);
  return *this;
}
Cube::Scramble operator+(Cube::Scramble s1, const Cube::Scramble &s2) {
  return s1 += s2;
}

std::ostream &operator<<(std::ostream &os, const Cube &c) {
  os << "UP:" << Cube::UP << '\n' << c.sides[c.UP];
  os << "DOWN:" << Cube::DOWN << '\n' << c.sides[c.DOWN];
  os << "LEFT:" << Cube::LEFT << '\n' << c.sides[c.LEFT];
  os << "RIGHT:" << Cube::RIGHT << '\n' << c.sides[c.RIGHT];
  os << "FRONT:" << Cube::FRONT << '\n' << c.sides[c.FRONT];
  os << "BACK:" << Cube::BACK << '\n' << c.sides[c.BACK];
  return os;
}
