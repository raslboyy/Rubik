#pragma once
#include <utility>
#include <vector>
#include <iostream>
#include <memory>

class Side {
 private:
  struct Line;
 public:
  using byte = char;
  using array = std::vector<std::vector<byte>>;

  explicit Side(const array &);
  Side(size_t, byte);
  Side(const Side &) = default;
  Side &operator=(const Side &) = default;

  void rotate() { state = (state + 1) % 4; };
  void rotate_() { state = (state - 1) % 4; }

  Line operator[](size_t i) const { return Line(*this, i); }

  [[nodiscard]] std::vector<byte> get_row(size_t) const;
  void set_row(size_t i, const std::vector<byte> &);
  [[nodiscard]] std::vector<byte> get_column(size_t) const;
  void set_column(size_t j, const std::vector<byte> &);

  [[nodiscard]] size_t n() const { return n_; }
  [[nodiscard]] unsigned count_without(byte) const;

  enum SIDE : size_t { UP = 0, DOWN, LEFT, RIGHT, FRONT, BACK };

  friend std::ostream &operator<<(std::ostream &, const Side &);
//  friend std::istream &operator>>(std::istream &is, Side &s);
 private:
  array a;
  size_t n_;
  int state;
  struct Line {
    Line(const Side &rs, size_t i) : rs(rs), i(i) {};
    byte operator[](size_t j) { return rs.get(i, j); }
   private:
    const Side &rs;
    size_t i;
  };

  byte &get(size_t, size_t);
  [[nodiscard]] byte get(size_t, size_t) const;
};

