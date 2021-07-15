#include "CGene.h"

genetic_algorithm::CGene::CGene(const Cube &start)
    : cube(start),
      allele(start.n(), 0),
      fitness_(std::numeric_limits<unsigned>::infinity()),
      fitness_is_valid(false) {}
genetic_algorithm::CGene::CGene(const Cube &start, const Scramble &scramble) :
    cube(start),
    allele(scramble),
    fitness_(std::numeric_limits<unsigned>::infinity()),
    fitness_is_valid(false) {
  allele(cube);
}

unsigned genetic_algorithm::CGene::fitness() const {
  if (fitness_is_valid)
    return fitness_;
  else {
    const_cast<CGene *>(this)->fitness_is_valid = true;
    const_cast<CGene *>(this)->fitness_ = fitness(cube);
    const_cast<CGene *>(this)->fitness_history.emplace_back(fitness_);
    if (fitness_history.size() > 5)
      const_cast<CGene *>(this)->fitness_history.pop_front();
    return fitness_;
  }
}
unsigned genetic_algorithm::CGene::fitness(const Cube &cube) {
  return cube.stupidFitness();
}

void genetic_algorithm::CGene::mutation(size_t n) {
  fitness_is_valid = false;
  allele += dynamic_cast<const Scramble &>(Scramble(cube.n(), n).operator()(cube));
}

bool operator<(const genetic_algorithm::CGene &gene1, const genetic_algorithm::CGene &gene2) {
  return gene1.fitness() < gene2.fitness();
}
bool operator>(const genetic_algorithm::CGene &gene1, const genetic_algorithm::CGene &gene2) {
  return gene2 < gene1;
}
bool operator<=(const genetic_algorithm::CGene &gene1, const genetic_algorithm::CGene &gene2) {
  return !(gene1 > gene2);
}
bool operator>=(const genetic_algorithm::CGene &gene1, const genetic_algorithm::CGene &gene2) {
  return !(gene1 < gene2);
}
bool operator==(const genetic_algorithm::CGene &gene1, const genetic_algorithm::CGene &gene2) {
  return gene1.fitness() == gene2.fitness();
}
bool operator!=(const genetic_algorithm::CGene &gene1, const genetic_algorithm::CGene &gene2) {
  return !(gene1 == gene2);
}
