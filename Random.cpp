#include "Random.h"

unsigned int Random::randU32(unsigned int l, unsigned int r) {
  static std::mt19937 mersenne(std::random_device().operator()());
  return mersenne() % (r - l) + l;
}

unsigned int Random::randU32(unsigned int r) {
  return randU32(0, r);
}