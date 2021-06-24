#pragma once
#include <vector>

class Field {
 public:
  explicit Field(std::vector<std::vector<char>> &array);
  Field(size_t n, char color);

  void rotate_right() { state_ = (state_ + 1) % 4; };
  void rotate_left() { state_ = (state_ - 1) % 4; }



  char get(size_t i, size_t j);

  [[nodiscard]] size_t n() const { return n_; }
 private:
  size_t n_;
  int state_;
  std::vector<std::vector<char>> array_;
};
