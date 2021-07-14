#include "Scramble.h"

#include <sstream>
#include "../../Random.h"
#include "Move.h"
#include "Rotate.h"
#include "Skip.h"

Scramble::Scramble(size_t n, size_t size) : n_(n) {
  if (size == std::numeric_limits<size_t>::infinity())
    size = Random::randU32(10, 101);
  for (size_t i = 0; i < size; i++) {
    auto type = Random::randU32(1, 2);
    if (type == 0)
      scramble.emplace_back(new Skip());
    else if (type == 1)
      scramble.emplace_back(new Move(n_));
    else
      scramble.emplace_back(new Rotate());
  }
}
Scramble::Scramble(size_t n, const std::string &s) : n_(n) {
  std::stringstream ss(s);
  std::string command;
  while (ss >> command) {
    if (command == "-")
      scramble.emplace_back(new Skip());
    else if (command.size() == 1 and command[0] < '4')
      scramble.emplace_back(new Rotate(command));
    else
      scramble.emplace_back(new Move(command));
  }
}
const IAction &Scramble::operator()(Cube &cube) const {
  for (auto &pIAction : scramble)
    pIAction->operator()(cube);
  return *this;
}
std::string Scramble::to_string() const {
  std::string s;
  for (auto &pIAction : scramble)
    s += pIAction->to_string() + " ";
  return s;
}
Scramble &Scramble::operator+=(const Scramble &other) {
  for (auto &pIAction : other.scramble)
    scramble.emplace_back(pIAction);
  return *this;
}
Scramble operator+(Scramble s1, const Scramble &s2) {
  return s1 += s2;
}