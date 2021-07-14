#include "Cube.h"

#include <sstream>
#include <algorithm>
#include <ctime>

Cube::Cube(size_t n) :
    n_(n),
    scramble_(n) {
  for (int i = 0; i < 6; i++)
    sides.emplace_back(n, i);
}
Cube::Cube(size_t n, std::vector<Side> m) : sides(std::move(m)), n_(n), scramble_(n) {}

// fix count >
std::string Cube::random_scramble(size_t size) {
  auto new_scramble = dynamic_cast<const Scramble &>(Scramble(n(), size).operator()(*this));
  scramble_ += new_scramble;
  return new_scramble.to_string();
}

void Cube::apply_scramble(const std::string &s) {
  // проверка
  scramble_ += dynamic_cast<const Scramble &>(Scramble(n(), s).operator()(*this));
}

std::string Cube::get_scramble() const {
  return scramble_.to_string();
}

unsigned Cube::stupidFitness() const {
  unsigned count = 0;
  for (char i = 0; i < 6; i++)
    count += sides[i].count_without(i);
  return count;
}

std::ostream &operator<<(std::ostream &os, const Cube &c) {
  os << "UP:" << Cube::SIDE::UP << '\n' << c.sides[Cube::SIDE::UP];
  os << "DOWN:" << Cube::SIDE::DOWN << '\n' << c.sides[Cube::SIDE::DOWN];
  os << "LEFT:" << Cube::SIDE::LEFT << '\n' << c.sides[Cube::SIDE::LEFT];
  os << "RIGHT:" << Cube::SIDE::RIGHT << '\n' << c.sides[Cube::SIDE::RIGHT];
  os << "FRONT:" << Cube::SIDE::FRONT << '\n' << c.sides[Cube::SIDE::FRONT];
  os << "BACK:" << Cube::SIDE::BACK << '\n' << c.sides[Cube::SIDE::BACK];
  return os;
}
