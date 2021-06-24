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

char Field::get(size_t i, size_t j) {
  if (state_ == 0) return array_[i][j];
  else if (state_ == 1) return array_[n_ - 1 - j][i];
  else if (state_ == 2) return array_[n_ - 1 - i][n_ - 1 - j];
  else return array_[j][n_ - 1 - i];
}

