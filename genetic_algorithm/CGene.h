#pragma once

#include "genetic_algorithm.h"
#include "CFitness.h"
#include "CGeneration.h"

class genetic_algorithm::CGene {
 public:
  explicit CGene(const Cube &);
  explicit CGene(const Cube &, const Scramble &);

  CGene(const CGene &other) = default;
  CGene &operator=(const CGene &other) = default;

  void mutation(size_t n);

  [[nodiscard]] size_t len() const { return allele.len(); }
  [[nodiscard]] unsigned fitness() const;
  static unsigned fitness(const Cube &);

  friend bool operator<(const CGene &gene1, const CGene &gene2);
  friend bool operator>(const CGene &gene1, const CGene &gene2);
  friend bool operator<=(const CGene &gene1, const CGene &gene2);
  friend bool operator>=(const CGene &gene1, const CGene &gene2);
  friend bool operator==(const CGene &gene1, const CGene &gene2);
  friend bool operator!=(const CGene &gene1, const CGene &gene2);
 private:
  Scramble allele;
  Cube cube;
  bool fitness_is_valid;
  unsigned fitness_;
  std::list<unsigned> fitness_history;
};