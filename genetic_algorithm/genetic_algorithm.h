#pragma once

#include <vector>
#include <random>
#include <string>
#include <array>

#include "../Cube/Cube.h"

class genetic_algorithm {
 public:
  explicit genetic_algorithm(const Cube &);

  class Gene;
  struct Parameters {
    size_t max_resets = 5;
    size_t max_generations = 500;
    size_t population_size = 1000;
    double elitism_num = 0.2;
    double max_kill_by_rank = 0.1;
    double max_random_kill = 0.01;
    size_t max_mutation_size = 1;
  };

  bool solve(const Parameters &);

 private:

  Parameters parameters;
  std::vector<Gene> genes;
  Cube cube;

  void generation();
  void selection();
  void new_generation();
  std::vector<Gene> crossover(const std::vector<Gene> &random_genes);
  Gene crossover(const Gene &gene1, const Gene &gene2);
  void mutation();

  [[nodiscard]] bool check() const;
  unsigned best_fitness() const;

  static std::vector<unsigned int> random_unique_array(size_t n, unsigned int l, unsigned int r);
};

class genetic_algorithm::Gene {
 public:
  explicit Gene(const Cube &start);
  explicit Gene(const Cube &start, std::vector<Cube::move> alleles);

  Gene(const Gene &other) = default;
  Gene &operator=(const Gene &other) = default;

  void mutation(size_t n);

  [[nodiscard]] size_t len() const { return alleles.size(); }
  [[nodiscard]] unsigned fitness() const;

  [[nodiscard]] std::string to_string() const;

  [[nodiscard]] std::vector<Cube::move> get_subAlleles(unsigned, unsigned) const;

  friend bool operator<(const Gene &gene1, const Gene &gene2);
  friend bool operator>(const Gene &gene1, const Gene &gene2);
  friend bool operator<=(const Gene &gene1, const Gene &gene2);
  friend bool operator>=(const Gene &gene1, const Gene &gene2);
  friend bool operator==(const Gene &gene1, const Gene &gene2);
  friend bool operator!=(const Gene &gene1, const Gene &gene2);
 private:
  std::vector<Cube::move> alleles;
  Cube cube;
  bool fitness_is_valid;
  unsigned fitness_;

  struct Permutation {
    Permutation();

    void operator()(Cube &c) const;

   private:
    static const size_t N = 15;
    std::array<Cube::move> set;
  };
  static const Permutation permutation;
};

