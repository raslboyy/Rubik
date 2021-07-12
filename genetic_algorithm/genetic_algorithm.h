#pragma once

#include <vector>
#include <random>
#include <string>
#include <array>

#include "../Cube/Cube.h"

class genetic_algorithm {
 public:

  genetic_algorithm() = default;
  genetic_algorithm(const genetic_algorithm &) = delete;
  genetic_algorithm &operator=(const genetic_algorithm &) = delete;

  class Gene;
  class Parameters {
   public:
    Parameters(size_t = 5, size_t = 500, size_t = 500, double = 0.2, double = 0.6, double = 0.02, size_t = 2, size_t = 10);
    [[nodiscard]] size_t GetMaxResets() const;
    void SetMaxResets(size_t value) { max_resets = value; }
    [[nodiscard]] size_t GetMaxGenerations() const;
    void SetMaxGenerations(size_t value) { max_generations = value; }
    [[nodiscard]] size_t GetPopulationSize() const;
    void SetPopulationSize(size_t value) { population_size = value; }
    [[nodiscard]] size_t GetElitismNum() const;
    void SetElitismNum(double value) { elitism_num = value; }
    [[nodiscard]] size_t GetMaxKillByRank() const;
    void SetMaxKillByRank(double value) { max_kill_by_rank = value; }
    [[nodiscard]] size_t GetMaxRandomKill() const;
    void SetMaxRandomKill(double value) { max_random_kill = value; }
    [[nodiscard]] size_t GetMaxMutationSize() const;
    void SetMaxMutationSize(size_t value) { max_mutation_size = value; }
   private:
    size_t max_resets;
    size_t max_generations;
    size_t population_size;
    double elitism_num;
    double max_kill_by_rank;
    double max_random_kill;
    size_t max_mutation_size;
    size_t out_frequency;
  };

  static bool solve(const Cube &, const Parameters & = Parameters());

 private:
  class CGeneration {
   public:
    explicit CGeneration(const Cube &, const Parameters &);

    void update();
    void reset();
    [[nodiscard]] bool check() const;
    [[nodiscard]] unsigned best_fitness() const;
   private:
    std::vector<Gene> genes;
    Cube cube;
    Parameters parameters;
    void mutation();
    void selection();
    void elitism();
    void crossover();
  };
};

class genetic_algorithm::Gene {
 public:
  explicit Gene(const Cube &);
  explicit Gene(const Cube &, const Cube::Scramble &);

  Gene(const Gene &other) = default;
  Gene &operator=(const Gene &other) = default;

  void mutation(size_t n);

  [[nodiscard]] size_t len() const { return allele.len(); }
  [[nodiscard]] unsigned fitness() const;

  friend bool operator<(const Gene &gene1, const Gene &gene2);
  friend bool operator>(const Gene &gene1, const Gene &gene2);
  friend bool operator<=(const Gene &gene1, const Gene &gene2);
  friend bool operator>=(const Gene &gene1, const Gene &gene2);
  friend bool operator==(const Gene &gene1, const Gene &gene2);
  friend bool operator!=(const Gene &gene1, const Gene &gene2);
 private:
  Cube::Scramble allele;
  Cube cube;
  bool fitness_is_valid;
  unsigned fitness_;

//  struct Permutation {
//    Permutation();
//
//    void operator()(Cube &c) const;
//
//   private:
//    static const size_t N = 15;
//    std::array<Cube::Scramble> set;
//  };
//  static const Permutation permutation;
};

