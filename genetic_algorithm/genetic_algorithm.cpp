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
                                          size_t out_frequency) :
    max_resets(max_resets),
    max_generations(max_generations),
    population_size(population_size),
    elitism_num(std::max(0., Random::randD(elitism_num - 0.05, elitism_num + 0.05))),
    max_kill_by_rank(std::max(0., Random::randD(max_kill_by_rank - 0.05, max_kill_by_rank + 0.05))),
    max_random_kill(std::max(0., Random::randD(max_random_kill - 0.05, max_random_kill + 0.05))),
    max_mutation_size(max_mutation_size),
    out_frequency(out_frequency) {

}

bool genetic_algorithm::solve(const Cube &cube, const Parameters &parameters) {
  std::ofstream log("log.txt");
  auto generation = CGeneration(cube, parameters);
  for (int attempt = 0; attempt < parameters.GetMaxResets() && !generation.check(); attempt++) {
    log << "Attempt " << attempt << std::endl;
    for (int i = 1; i <= parameters.GetMaxGenerations() && !generation.check(); i++) {
      generation.update();
      if (i % 10 == 0)
        log << "\t" << i << ". " << generation.best_fitness() << std::endl;
    }
    generation.reset();
  }
  return generation.check();
}

genetic_algorithm::CGeneration::CGeneration(const Cube &c, const Parameters &p) :
    cube(c),
    parameters(p),
    genes() {
  genes.assign(parameters.GetPopulationSize(), Gene(cube));
}

void genetic_algorithm::CGeneration::update() {
  std::sort(genes.begin(), genes.end());
  selection();
  elitism();
  mutation();
}
void genetic_algorithm::CGeneration::reset() {
  genes.assign(parameters.GetPopulationSize(), Gene(cube));
}

void genetic_algorithm::CGeneration::selection() {
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

  std::vector<Gene> t;
  for (int i = 0; i < n - kill_by_rank; i++)
    if (is_survived[i])
      t.emplace_back(genes[i]);
  genes = t;
}
void genetic_algorithm::CGeneration::elitism() {
  while (genes.size() <= parameters.GetPopulationSize())
    for (auto &i : Random::random_unique_array(parameters.GetElitismNum(), 0, genes.size())) {
      genes.emplace_back(genes[i]);
      if (genes.size() == parameters.GetPopulationSize())
        return;
    }
}
void genetic_algorithm::CGeneration::mutation() {
  for (size_t i = parameters.GetElitismNum(); i != genes.size(); i++)
    genes[i].mutation(parameters.GetMaxMutationSize());
}

bool genetic_algorithm::CGeneration::check() const {
  for (const auto &g : genes)
    if (g.fitness() == 0)
      return true;
  return false;
}
unsigned genetic_algorithm::CGeneration::best_fitness() const {
  unsigned min = std::numeric_limits<unsigned>::max();
  for (const auto &g : genes)
    min = std::min(min, g.fitness());
  return min;
}

genetic_algorithm::Gene::Gene(const Cube &start)
    : cube(start),
      allele(start.n(), 0),
      fitness_(std::numeric_limits<unsigned>::infinity()),
      fitness_is_valid(false) {}
genetic_algorithm::Gene::Gene(const Cube &start, const Cube::Scramble &scramble) :
    cube(start),
    allele(scramble),
    fitness_(std::numeric_limits<unsigned>::infinity()),
    fitness_is_valid(false) {
  allele(cube);
}

unsigned genetic_algorithm::Gene::fitness() const {
  if (fitness_is_valid)
    return fitness_;
  else {
    const_cast<Gene *>(this)->fitness_is_valid = true;
    const_cast<Gene *>(this)->fitness_ = cube.stupidFitness();
    return fitness_;
  }
}

void genetic_algorithm::Gene::mutation(size_t n) {
  fitness_is_valid = false;
  allele += dynamic_cast<const Cube::Scramble &>(Cube::Scramble(cube.n(), n).operator()(cube));
}

bool operator<(const genetic_algorithm::Gene &gene1, const genetic_algorithm::Gene &gene2) {
  return gene1.fitness() < gene2.fitness();
}
bool operator>(const genetic_algorithm::Gene &gene1, const genetic_algorithm::Gene &gene2) {
  return gene2 < gene1;
}
bool operator<=(const genetic_algorithm::Gene &gene1, const genetic_algorithm::Gene &gene2) {
  return !(gene1 > gene2);
}
bool operator>=(const genetic_algorithm::Gene &gene1, const genetic_algorithm::Gene &gene2) {
  return !(gene1 < gene2);
}
bool operator==(const genetic_algorithm::Gene &gene1, const genetic_algorithm::Gene &gene2) {
  return gene1.fitness() == gene2.fitness();
}
bool operator!=(const genetic_algorithm::Gene &gene1, const genetic_algorithm::Gene &gene2) {
  return !(gene1 == gene2);
}

//genetic_algorithm::Gene::Permutation::Permutation() : set({
//                                                              Cube::move("F' L' B' R' U' R U' B L F R U R' U"),
//                                                              Cube::move("F R B L U L' U B' R' F' L' U' L U'"),
//                                                              Cube::move("U2 B U2 B' R2 F R' F' U2 F' U2 F R'"),
//                                                              Cube::move("U2 R U2 R' F2 L F' L' U2 L' U2 L F'"),
//                                                              Cube::move("U' B2 D2 L' F2 D2 B2 R' U'"),
//                                                              Cube::move("U B2 D2 R F2 D2 B2 L U"),
//                                                              Cube::move("D' R' D R2 U' R B2 L U' L' B2 U R2"),
//                                                              Cube::move("D L D' L2 U L' B2 R' U R B2 U' L2"),
//                                                              Cube::move("R' U L' U2 R U' L R' U L' U2 R U' L U'"),
//                                                              Cube::move("L U' R U2 L' U R' L U' R U2 L' U R' U"),
//                                                              Cube::move("F' U B U' F U B' U'"),
//                                                              Cube::move("F U' B' U F' U' B U"),
//                                                              Cube::move("L' U2 L R' F2 R"),
//                                                              Cube::move("R' U2 R L' B2 L"),
//                                                              Cube::move("2L2 U 2L2 U2 2L2 U 2L2")
//                                                          }) {}
//
//void genetic_algorithm::Gene::Permutation::operator()(Cube &c) const {
//  int n_view = randU32(0, 5);
//  for (int i = 0; i < n_view; i++)
//    c.to_view(randU32(0, 4));
//  set[randU32(0, set.size())].operator()(c);
//}

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
