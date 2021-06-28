#pragma once
#include <vector>
#include <iostream>

class Field {
 public:
  explicit Field(std::vector<std::vector<char>> &array);
  Field(size_t n, char color);

  void rotate() { state_ = (state_ + 1) % 4; };
  void rotate_() { state_ = (state_ - 1) % 4; }

  char &get(size_t i, size_t j);
  [[nodiscard]] char get(size_t i, size_t j) const { return const_cast<Field*>(this)->get(i, j); };

  std::vector<char> get_row(size_t i);
  void set_row(size_t i, const std::vector<char> &row);
  std::vector<char> get_col(size_t j);
  void set_col(size_t j, const std::vector<char> &col);

  [[nodiscard]] size_t n() const { return n_; }
  [[nodiscard]] unsigned count_without(char c) const;

  friend std::ostream &operator<<(std::ostream &os, const Field &f);
 private:
  size_t n_;
  int state_;
  std::vector<std::vector<char>> array_;
};

