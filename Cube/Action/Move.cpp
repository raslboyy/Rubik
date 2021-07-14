#include "Move.h"

#include "../../Random.h"
#include "../Cube.h"

Move::Move(size_t n) :
    deep_(Random::randU32(n - 1)),
    count_(Random::randU32(1, 3)),
    side_(static_cast<SIDE>(Random::randU32(6))) {}
Move::Move(unsigned deep, unsigned count, SIDE side) :
    deep_(deep),
    count_(count),
    side_(side) {}
Move::Move(const std::string &s) {
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

const IAction &Move::operator()(Cube &cube) const {
  for (int i = 0; i < count_; i++)
    operator()(cube, side_, deep_);
  return *this;
}
std::string Move::to_string() const {
  static std::string moves = "UDLRFB";
  return std::to_string(deep_ + 1) + moves[side_] + std::to_string(count_);
}

auto &Move::GetOrder() {
  static const std::vector<std::vector<SIDE>> order = {
      {SIDE::FRONT, SIDE::LEFT, SIDE::BACK, SIDE::RIGHT}, // UP
      {SIDE::FRONT, SIDE::RIGHT, SIDE::BACK, SIDE::LEFT}, // DOWN
      {SIDE::UP, SIDE::FRONT, SIDE::DOWN, SIDE::BACK}, // LEFT
      {SIDE::UP, SIDE::BACK, SIDE::DOWN, SIDE::FRONT}, // RIGHT
      {SIDE::UP, SIDE::RIGHT, SIDE::DOWN, SIDE::LEFT}, // FRONT
      {SIDE::UP, SIDE::LEFT, SIDE::DOWN, SIDE::RIGHT} // BACK
  };
  return order;
}
auto &Move::GetIsRow() {
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
auto &Move::GetIsNormalDeep() {
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
auto &Move::GetIsReverse() {
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

void Move::operator()(Cube &cube, SIDE side, unsigned deep) const {
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
