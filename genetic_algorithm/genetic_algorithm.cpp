#include "genetic_algorithm.h"

#include <algorithm>
#include <utility>
#include <fstream>
#include <limits>

#include "../Random.h"

genetic_algorithm::Parameters::Parameters(size_t max_resets,
                                          size_t max_generations,
                                          size_t population_size,
                                          double elitism_num,
                                          double max_kill_by_rank,
                                          double max_random_kill,
                                          size_t max_mutation_size,
                                          size_t out_frequency,
                                          size_t pow) :
    max_resets(max_resets),
    max_generations(max_generations),
    population_size(population_size),
    elitism_num(std::max(0., Random::randD(elitism_num - 0.05, elitism_num + 0.05))),
    max_kill_by_rank(std::max(0., Random::randD(max_kill_by_rank - 0.05, max_kill_by_rank + 0.05))),
    max_random_kill(std::max(0., Random::randD(max_random_kill - 0.05, max_random_kill + 0.05))),
    max_mutation_size(max_mutation_size),
    out_frequency(out_frequency),
    pow(pow) {}

bool genetic_algorithm::solve(const Cube &cube, const Parameters &parameters) {
  std::ofstream log("log.txt");
  auto generation = CGeneration<CFitness>(cube, parameters, CFitness(cube.n(), parameters.GetPow()));
  for (int attempt = 0; attempt < parameters.GetMaxResets() && !generation.check(); attempt++) {
    log << "Attempt " << attempt << std::endl;
    for (int i = 1; i <= parameters.GetMaxGenerations() && !generation.check(); i++) {
      generation.update();
      if (i % parameters.GetOutFrequency() == 0)
        log << "\t" << i << ". " << generation.best_fitness() << std::endl;
    }
    generation.reset();
  }
  return generation.check();
}

genetic_algorithm::CFitness::CFitness(size_t n, size_t pow) :
    fitness(6, std::vector<std::vector<unsigned>>(n, std::vector<unsigned>(n, 0))) {

}
unsigned genetic_algorithm::CFitness::operator()(const Cube &cube) const {
  return cube.stupidFitness();
}

template<typename FitnessFunc>
genetic_algorithm::CGeneration<FitnessFunc>::CGeneration(const Cube &c, const Parameters &p, const CFitness &f) :
    cube(c),
    parameters(p),
    genes(),
    fitness_function(c.n(), p.GetPow()) {
  genes.assign(parameters.GetPopulationSize(), Gene(cube, f));
}

template<typename FitnessFunc>
void genetic_algorithm::CGeneration<FitnessFunc>::update() {
  std::sort(genes.begin(), genes.end());
  selection();
  elitism();
  mutation();
}
template<typename FitnessFunc>
void genetic_algorithm::CGeneration<FitnessFunc>::reset() {
  genes.assign(parameters.GetPopulationSize(), Gene<FitnessFunc>(cube, fitness_function));
}

template<typename FitnessFunc>
void genetic_algorithm::CGeneration<FitnessFunc>::selection() {
  size_t n = genes.size();
  std::vector<bool> is_survived(n, true);
  auto kill_by_rank = parameters.GetMaxKillByRank();
  auto random_kill = parameters.GetMaxRandomKill();

  for (int i = 1; i <= kill_by_rank; i++)
    is_survived[n - i] = false;
  for (int i = 0, j = 0; i < random_kill;)
    if (is_survived[j = static_cast<int>(Random::randU32(n - kill_by_rank))]) {
      is_survived[j] = false;
      i++;
    }

  std::vector<Gene<FitnessFunc>> t;
  for (int i = 0; i < n - kill_by_rank; i++)
    if (is_survived[i])
      t.emplace_back(genes[i]);
  genes = t;
}
template<typename FitnessFunc>
void genetic_algorithm::CGeneration<FitnessFunc>::elitism() {
  while (genes.size() <= parameters.GetPopulationSize())
    for (auto &i : Random::random_unique_array(parameters.GetElitismNum(), 0, genes.size())) {
      genes.emplace_back(genes[i]);
      if (genes.size() == parameters.GetPopulationSize())
        return;
    }
}
template<typename FitnessFunc>
void genetic_algorithm::CGeneration<FitnessFunc>::mutation() {
  for (size_t i = parameters.GetElitismNum(); i != genes.size(); i++)
    genes[i].mutation(parameters.GetMaxMutationSize());
}

template<typename FitnessFunc>
bool genetic_algorithm::CGeneration<FitnessFunc>::check() const {
  for (const auto &g : genes)
    if (g.fitness() == 0)
      return true;
  return false;
}
template<typename FitnessFunc>
unsigned genetic_algorithm::CGeneration<FitnessFunc>::best_fitness() const {
  unsigned min = std::numeric_limits<unsigned>::max();
  for (const auto &g : genes)
    min = std::min(min, g.fitness());
  return min;
}

template<typename FitnessFunc>
genetic_algorithm::Gene<FitnessFunc>::Gene(const Cube &start, FitnessFunc f)
    : cube(start),
      allele(start.n(), 0),
      fitness_(std::numeric_limits<unsigned>::infinity()),
      fitness_is_valid(false),
      fitness_function(f) {}
template<typename FitnessFunc>
genetic_algorithm::Gene<FitnessFunc>::Gene(const Cube &start, const Scramble &scramble, FitnessFunc f) :
    cube(start),
    allele(scramble),
    fitness_(std::numeric_limits<unsigned>::infinity()),
    fitness_is_valid(false),
    fitness_function(f) {
  allele(cube);
}

template<typename FitnessFunc>
unsigned genetic_algorithm::Gene<FitnessFunc>::fitness() const {
  if (fitness_is_valid)
    return fitness_;
  else {
    const_cast<Gene *>(this)->fitness_is_valid = true;
    const_cast<Gene *>(this)->fitness_ = fitness_function(cube);
    const_cast<Gene *>(this)->fitness_history.emplace_back(fitness_);
    if (fitness_history.size() > 5)
      const_cast<Gene *>(this)->fitness_history.pop_front();
    const_cast<Gene *>(this)->fitness_ = std::round(std::accumulate(fitness_history.begin(), fitness_history.end(), 0) / fitness_history.size());
    return fitness_;
  }
}

template<typename FitnessFunc>
void genetic_algorithm::Gene<FitnessFunc>::mutation(size_t n) {
  fitness_is_valid = false;
  allele += dynamic_cast<const Scramble &>(Scramble(cube.n(), n).operator()(cube));
}

template<typename FitnessFunc>
bool operator<(const genetic_algorithm::Gene<FitnessFunc> &gene1, const genetic_algorithm::Gene<FitnessFunc> &gene2) {
  return gene1.fitness() < gene2.fitness();
}
template<typename FitnessFunc>
bool operator>(const genetic_algorithm::Gene<FitnessFunc> &gene1, const genetic_algorithm::Gene<FitnessFunc> &gene2) {
  return gene2 < gene1;
}
template<typename FitnessFunc>
bool operator<=(const genetic_algorithm::Gene<FitnessFunc> &gene1, const genetic_algorithm::Gene<FitnessFunc> &gene2) {
  return !(gene1 > gene2);
}
template<typename FitnessFunc>
bool operator>=(const genetic_algorithm::Gene<FitnessFunc> &gene1, const genetic_algorithm::Gene<FitnessFunc> &gene2) {
  return !(gene1 < gene2);
}
template<typename FitnessFunc>
bool operator==(const genetic_algorithm::Gene<FitnessFunc> &gene1, const genetic_algorithm::Gene<FitnessFunc> &gene2) {
  return gene1.fitness() == gene2.fitness();
}
template<typename FitnessFunc>
bool operator!=(const genetic_algorithm::Gene<FitnessFunc> &gene1, const genetic_algorithm::Gene<FitnessFunc> &gene2) {
  return !(gene1 == gene2);
}

size_t genetic_algorithm::Parameters::GetElitismNum() const {
  return static_cast<size_t>(elitism_num * static_cast<double>(population_size));
}
size_t genetic_algorithm::Parameters::GetMaxKillByRank() const {
  return static_cast<size_t>(max_kill_by_rank * static_cast<double>(population_size));
}
size_t genetic_algorithm::Parameters::GetMaxRandomKill() const {
  return static_cast<size_t>(max_random_kill * static_cast<double>(population_size));
}
size_t genetic_algorithm::Parameters::GetPopulationSize() const {
  return population_size;
}
size_t genetic_algorithm::Parameters::GetMaxGenerations() const {
  return max_generations;
}
size_t genetic_algorithm::Parameters::GetMaxResets() const {
  return max_resets;
}
size_t genetic_algorithm::Parameters::GetMaxMutationSize() const {
  return max_mutation_size;
}
size_t genetic_algorithm::Parameters::GetOutFrequency() const {
  return out_frequency;
}
size_t genetic_algorithm::Parameters::GetPow() const {
  return pow;
}