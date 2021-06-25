#include "Field.h"

Field::Field(std::vector<std::vector<char>> &array) :
    array_(array),
    n_(array.size()),
    state_(0) {
  // проверка размерности и 6 цветов (0-5)

}

Field::Field(size_t n, char color) :
    array_(std::vector<std::vector<char>>(n, std::vector<char>(n, color))),
    n_(n),
    state_(0) {
  // проверка цвета
}

char &Field::get(size_t i, size_t j) {
  if (state_ == 0) return array_[i][j];
  else if (state_ == 1) return array_[n_ - 1 - j][i];
  else if (state_ == 2) return array_[n_ - 1 - i][n_ - 1 - j];
  else return array_[j][n_ - 1 - i];
}
std::vector<char> Field::get_row(size_t i) {
  std::vector<char> row(n_);
  for (size_t j = 0; j != n_; j++)
    row[j] = get(i, j);
  return row;
}
void Field::set_row(size_t i, const std::vector<char> &row) {
  for (size_t j = 0; j != n_; j++)
    get(i, j) = row[j];
}
std::vector<char> Field::get_col(size_t j) {
  std::vector<char> col(n_);
  for (size_t i = 0; i != n_; i++)
    col[i] = get(i, j);
  return col;
}
void Field::set_col(size_t j, const std::vector<char> &col) {
  for (size_t i = 0; i != n_; i++)
    get(i, j) = col[i];
}

std::ostream &operator<<(std::ostream &os, const Field &f) {
  for (size_t i = 0; i != f.n_; i++) {
    for (size_t j = 0; j != f.n_; j++)
      os << int(f.get(i, j)) << ' ';
    os << '\n';
  }
  return os;
}