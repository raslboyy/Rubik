#pragma once

#include <vector>
#include <random>
#include <string>
#include <array>
#include <list>

#include "../Cube/Cube.h"
#include "../Cube/Action/Scramble.h"

class genetic_algorithm {
 public:

  genetic_algorithm() = default;
  genetic_algorithm(const genetic_algorithm &) = delete;
  genetic_algorithm &operator=(const genetic_algorithm &) = delete;

  template<typename FitnessFunc>
  class Gene;
  class Parameters{
   public:
    explicit Parameters(size_t = 5,
                        size_t = 500,
                        size_t = 500,
                        double = 0.2,
                        double = 0.6,
                        double = 0.02,
                        size_t = 1,
                        size_t = 10,
                        size_t = 2);
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
    [[nodiscard]] size_t GetOutFrequency() const;
    void SetOutFrequency(size_t value) { out_frequency = value; }
    [[nodiscard]] size_t GetPow() const;
    void SetPow(size_t value) { pow = value; }
   private:
    size_t max_resets;
    size_t max_generations;
    size_t population_size;
    double elitism_num;
    double max_kill_by_rank;
    double max_random_kill;
    size_t max_mutation_size;
    size_t out_frequency;
    size_t pow;
  };

  static bool solve(const Cube &, const Parameters & = Parameters());

 private:

  class CFitness;
  template<typename FitnessFunc>
  class CGeneration;
};

class genetic_algorithm::CFitness {
 public:
  CFitness(size_t n, size_t pow);

  unsigned operator()(const Cube &) const;
 private:
  std::vector<std::vector<std::vector<unsigned>>> fitness;
};

template<typename FitnessFunc>
class genetic_algorithm::CGeneration {
 public:
  explicit CGeneration(const Cube &, const Parameters &, const CFitness &);

  void update();
  void reset();
  [[nodiscard]] bool check() const;
  [[nodiscard]] unsigned best_fitness() const;
 private:
  std::vector<Gene<FitnessFunc>> genes;
  Cube cube;
  Parameters parameters;
  CFitness fitness_function;

  void mutation();
  void selection();
  void elitism();
  void crossover();
};

template<typename FitnessFunc>
class genetic_algorithm::Gene {
 public:
  explicit Gene(const Cube &, FitnessFunc);
  explicit Gene(const Cube &, const Scramble &, FitnessFunc);

  Gene(const Gene &other) = default;
  Gene &operator=(const Gene &other) = default;

  void mutation(size_t n);

  [[nodiscard]] size_t len() const { return allele.len(); }
  [[nodiscard]] unsigned fitness() const;

  template<typename T>
  friend bool operator<(const Gene<T> &gene1, const Gene<T> &gene2);
  template<typename T>
  friend bool operator>(const Gene<T> &gene1, const Gene<T> &gene2);
  template<typename T>
  friend bool operator<=(const Gene<T> &gene1, const Gene<T> &gene2);
  template<typename T>
  friend bool operator>=(const Gene<T> &gene1, const Gene<T> &gene2);
  template<typename T>
  friend bool operator==(const Gene<T> &gene1, const Gene<T> &gene2);
  template<typename T>
  friend bool operator!=(const Gene<T> &gene1, const Gene<T> &gene2);
 private:
  Scramble allele;
  Cube cube;
  bool fitness_is_valid;
  unsigned fitness_;
  std::list<unsigned> fitness_history;
  FitnessFunc fitness_function;
};

