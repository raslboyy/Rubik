#pragma once

#include "genetic_algorithm.h"
#include "CFitness.h"

class genetic_algorithm::CGeneration {
 public:
  CGeneration(const Cube &, const Parameters &);

  void update();
  void reset();
  [[nodiscard]] bool check() const;
  [[nodiscard]] unsigned best_fitness() const;
 private:
  std::vector<CGene> genes;
  Cube cube;
  Parameters parameters;

  void mutation();
  void selection();
  void elitism();
  void crossover();
};