#pragma once
#include <vector>
#include <string>
#include "Field.h"

class Cube {
 public:

  explicit Cube(size_t n = 3);
  Cube(const Cube &other) = default;
  Cube &operator=(const Cube &other) = default;

  void R(size_t deep = 0) { rotation(*this, RIGHT, deep); }
  void L(size_t deep = 0) { rotation(*this, LEFT, deep); }
  void U(size_t deep = 0) { rotation(*this, UP, deep); }
  void D(size_t deep = 0) { rotation(*this, DOWN, deep); }
  void F(size_t deep = 0) { rotation(*this, FRONT, deep); }
  void B(size_t deep = 0) { rotation(*this, BACK, deep); }

  [[nodiscard]] size_t n() const { return n_; }
  [[nodiscard]] char get(char face, size_t i, size_t j) const;

  std::string scramble();
  void scramble(const std::string &s);

  class move;

  [[nodiscard]] unsigned fitness() const;
  std::vector<move> solve();

  friend std::ostream &operator<<(std::ostream &os, const Cube &c);
  enum {
    UP = 0,
    DOWN,
    LEFT,
    RIGHT,
    FRONT,
    BACK
  };
 private:
  size_t n_;
  std::vector<Field> faces;

  class Rotate {
   public:
    void operator()(Cube &cube, char, unsigned) const;
   private:
    static const std::vector<std::vector<char>> order_;
    static const std::vector<std::vector<bool>> is_row_;
    static const std::vector<std::vector<bool>> is_normal_deep_;
    static const std::vector<std::vector<bool>> is_reverse_;
  };
  constexpr const static Rotate rotation{};

  Field &get(char face) { return faces[face]; }
};

class Cube::move {
 public:
  move() : deep_(0), count_(0), type_(0) {};
  explicit move(const std::string &);
  move(unsigned deep, unsigned count, int type) : deep_(deep), count_(count), type_(type) {};
  move(const move &other) = default;

  void operator()(Cube &) const;
  [[nodiscard]] std::string to_string() const;

  void set_deep(unsigned deep) { deep_ = deep; }
  void set_count(unsigned count) { count_ = count; }
  void set_type(int type) { type_ = type; }
 private:
  unsigned deep_{};
  unsigned count_{};
  int type_{};
};