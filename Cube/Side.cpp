#include "Side.h"

Side::Side(const array &a) :
    a(a),
    n_(a.size()),
    state(0) {
  // проверка размерности и 6 цветов (0-5)

}

Side::Side(size_t n, byte color) :
    a(array(n, std::vector<byte>(n, color))),
    n_(n),
    state(0) {
  // проверка цвета
}

Side::byte &Side::get(size_t i, size_t j) {
  if (state == 0) return a[i][j];
  else if (state == 1) return a[n_ - 1 - j][i];
  else if (state == 2) return a[n_ - 1 - i][n_ - 1 - j];
  else return a[j][n_ - 1 - i];
}
Side::byte Side::get(size_t i, size_t j) const {
  return const_cast<Side *>(this)->get(i, j);
};

std::vector<Side::byte> Side::get_row(size_t i) const {
  std::vector<Side::byte> row(n_);
  for (size_t j = 0; j != n_; j++)
    row[j] = get(i, j);
  return std::move(row);
}
void Side::set_row(size_t i, const std::vector<byte> &row) {
  for (size_t j = 0; j != n_; j++)
    get(i, j) = row[j];
}
std::vector<Side::byte> Side::get_column(size_t j) const {
  std::vector<Side::byte> col(n_);
  for (size_t i = 0; i != n_; i++)
    col[i] = get(i, j);
  return std::move(col);
}
void Side::set_column(size_t j, const std::vector<Side::byte> &col) {
  for (size_t i = 0; i != n_; i++)
    get(i, j) = col[i];
}

unsigned Side::count_without(Side::byte c) const {
  unsigned count = 0;
  for (size_t i = 0; i != n_; i++)
    for (size_t j = 0; j != n_; j++)
      if (get(i, j) != c)
        count++;
  return count;
}

std::ostream &operator<<(std::ostream &os, const Side &f) {
  std::string check = "ROBGDY";
//  std::string check = "UDLRFB";
  for (size_t i = 0; i != f.n_; i++) {
    for (size_t j = 0; j != f.n_; j++)
      os << check[(f[i][j])] << ' ';
    os << '\n';
  }
  return os;
}
