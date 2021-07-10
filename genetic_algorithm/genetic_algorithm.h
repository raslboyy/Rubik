#pragma once

#include <vector>
#include <random>
#include <string>
#include <array>

#include "../Cube/Cube.h"

class genetic_algorithm {
 public:
  explicit genetic_algorithm(const Cube &cube);
  class gene;
  bool solve();
 private:
  size_t population_size = 1000; // 500
  double elitism_num_proportion = 0.2;
  size_t elitism_num; // 0.1
  size_t max_generations = 500;
  size_t max_resets = 5;
  double max_kill_by_rank_proportion = 0.1;
  size_t max_kill_by_rank; // 0.2
  double max_random_kill_proportion = 0.01;
  size_t max_random_kill; // 0.01
  size_t max_mutation = 1; // 10
  // start_len ?
  std::vector<gene> genes;
  Cube cube;

  void generation();
  void selection();
  void new_generation();
  std::vector<gene> crossover(const std::vector<gene> &random_genes);
  gene crossover(const gene &gene1, const gene &gene2);
  void mutation();

  [[nodiscard]] bool check() const;
  unsigned best_fitness() const;

  static unsigned randU32(unsigned l, unsigned r) { return mersenne() % (r - l) + l; }
  static std::vector<unsigned int> random_unique_array(size_t n, unsigned int l, unsigned int r);
};

class genetic_algorithm::gene {
 public:
  explicit gene(const Cube &start);
  explicit gene(const Cube &start, std::vector<Cube::move> alleles);

  gene(const gene &other) = default;
  gene &operator=(const gene &other) = default;

  void mutation(size_t n);

  [[nodiscard]] size_t len() const { return alleles.size(); }
  [[nodiscard]] unsigned fitness() const;

  [[nodiscard]] std::string to_string() const;

  [[nodiscard]] std::vector<Cube::move> get_subAlleles(unsigned, unsigned) const;

  friend bool operator<(const gene &gene1, const gene &gene2);
  friend bool operator>(const gene &gene1, const gene &gene2);
  friend bool operator<=(const gene &gene1, const gene &gene2);
  friend bool operator>=(const gene &gene1, const gene &gene2);
  friend bool operator==(const gene &gene1, const gene &gene2);
  friend bool operator!=(const gene &gene1, const gene &gene2);
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
