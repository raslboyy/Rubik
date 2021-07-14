#pragma once
#include <vector>
#include <string>
#include <memory>

#include "Side.h"
#include "Action/IAction.h"
#include "Action/Scramble.h"
#include "Action/Move.h"
#include "../Random.h"

class Cube {
 public:

  using SIDE = Side::SIDE;

  explicit Cube(size_t = 3);
  Cube(size_t, std::vector<Side>);
  Cube(const Cube &) = default;
  Cube &operator=(const Cube &) = default;

  std::string random_scramble(size_t = std::numeric_limits<size_t>::infinity());
  void apply_scramble(const std::string &);
  [[nodiscard]] std::string get_scramble() const;

  [[nodiscard]] unsigned stupidFitness() const;

  const Side &operator[](SIDE s) const { return sides[s]; }

 private:
  size_t n_;
  std::vector<Side> sides;
  Side &get(SIDE face) { return sides[face]; }
  Scramble scramble_;
  friend class Move;
  friend class Rotate;

 public:
  void R(size_t deep = 0) { Move(deep, 1, SIDE::RIGHT).operator()(*this); }
  void L(size_t deep = 0) { Move(deep, 1, SIDE::LEFT).operator()(*this); }
  void U(size_t deep = 0) { Move(deep, 1, SIDE::UP).operator()(*this); }
  void D(size_t deep = 0) { Move(deep, 1, SIDE::DOWN).operator()(*this); }
  void F(size_t deep = 0) { Move(deep, 1, SIDE::FRONT).operator()(*this); }
  void B(size_t deep = 0) { Move(deep, 1, SIDE::BACK).operator()(*this); }

  [[nodiscard]] size_t n() const { return n_; }

  friend std::ostream &operator<<(std::ostream &os, const Cube &c);
};