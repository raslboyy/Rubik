#include "Model3D.h"

#include <algorithm>

Model3D::Model3D(const Cube &c) : cube(c.n()), n_(c.n()) {
  size_t n = n_;
  static std::vector<SIDE> sides{SIDE::LEFT, SIDE::FRONT, SIDE::RIGHT, SIDE::BACK};
  for (int k = 0; k != 4; k++) {
    for (size_t i = 0; i != n; i++)
      for (size_t j = 0; j != n - 1; j++) {
        if (i == 0 && j == 0)
          cube[i].emplace_back(new CCornerElement(SIDE::UP, sides[(k - 1) % 4], sides[k]));
        else if (i == n - 1 && j == 0)
          cube[i].emplace_back(new CCornerElement(SIDE::DOWN, sides[(k - 1) % 4], sides[k]));
        
      }
  }
}

bool Model3D::Element::equals(const Model3D::Element &other, bool is_orientation) const {
  if (sides.size() != other.sides.size())
    return false;
  for (auto &i : sides)
    if (std::find(other.sides.begin(), other.sides.end(), i) == other.sides.end())
      return false;
  if (!is_orientation)
    return true;
  for (size_t i = 0; i != sides.size(); i++)
    if (sides[i] != other.sides[i])
      return false;
  return true;
}