#pragma once
#include <vector>
#include <string>
#include "Field.h"

class Cube {
 public:
  class Command;
  class Rotate {
   public:
    explicit Rotate(Cube &c) : cube(c) {};
    void operator()(char, unsigned);
   private:
    Cube &cube;
    static const std::vector<std::vector<char>> order_;
    static const std::vector<std::vector<bool>> is_row_;
    static const std::vector<std::vector<bool>> is_normal_deep_;
    static const std::vector<std::vector<bool>> is_reverse_;
  };

  explicit Cube(size_t n = 3);

  void R(size_t deep = 0) { rotation(RIGHT, deep); }
  void L(size_t deep = 0) { rotation(LEFT, deep); }
  void U(size_t deep = 0) { rotation(UP, deep); }
  void D(size_t deep = 0) { rotation(DOWN, deep); }
  void F(size_t deep = 0) { rotation(FRONT, deep); }
  void B(size_t deep = 0) { rotation(BACK, deep); }

  [[nodiscard]] size_t n() const { return n_; }
  [[nodiscard]] char get(char face, size_t i, size_t j) const;
  void scramble(const std::string &s);

  friend std::ostream &operator<<(std::ostream &os, const Cube &c);

 private:
  std::vector<Field> faces_;
  size_t n_;
  Rotate rotation;

  enum side {
    UP = 0,
    DOWN,
    LEFT,
    RIGHT,
    FRONT,
    BACK
  };

  Field &get(char face) { return faces_[face]; }
};

class Cube::Command {
 public:
  explicit Command(const std::string &);

  void solve(Cube *c) const {
    for (unsigned i = 0; i != count_; i++)
      c->rotation(type_, deep_);
  }
 private:
  unsigned deep_{};
  unsigned count_{};
  int type_{};
};