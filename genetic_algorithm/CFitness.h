#pragma once

#include "genetic_algorithm.h"

class genetic_algorithm::CFitness {
 public:
  CFitness(size_t n, size_t pow);

  unsigned operator()(const Cube &) const;
 private:

};