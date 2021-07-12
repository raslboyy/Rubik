#include "Random.h"

unsigned int Random::randU32(unsigned int l, unsigned int r) {
  static std::mt19937 mersenne(std::random_device().operator()());
  return mersenne() % (r - l) + l;
}

unsigned int Random::randU32(unsigned int r) {
  return randU32(0, r);
}

double Random::randD(double r) {
  static std::random_device rd;
  static std::default_random_engine eng(rd());
  std::uniform_real_distribution<> distr(0, r);
  return distr(eng);
}

double Random::randD(double l, double r) {
  static std::random_device rd;
  static std::default_random_engine eng(rd());
  std::uniform_real_distribution<> distr(l, r);
  return distr(eng);
}

std::vector<unsigned> Random::random_unique_array(size_t n, unsigned l, unsigned r) {
  std::vector<unsigned> array(n);
  for (size_t i = 0, j = 0; i != n;) {
    array[i] = randU32(l, r);
    for (j = 0; j != i; j++)
      if (array[i] != array[j])
        break;
    if (j == i)
      i++;
  }
  return std::move(array);
}