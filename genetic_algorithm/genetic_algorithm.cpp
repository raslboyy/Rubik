#include "genetic_algorithm.h"

#include <algorithm>
#include <utility>
#include <fstream>
#include <climits>

std::mt19937 genetic_algorithm::mersenne(std::random_device().operator()());

genetic_algorithm::genetic_algorithm(const Cube &cube) :
    cube(cube),
    genes(population_size, gene(cube)),
    elitism_num(population_size * 0.1),
    max_kill_by_rank(population_size * 0.1),
    max_random_kill(population_size * 0) {
  for (size_t i = 1; i != genes.size(); i++)
    genes[i] = gene(cube);
}

bool genetic_algorithm::solve() {
  std::ofstream out("log.txt");
  bool is_found = check();
  for (int attempt = 0; attempt < max_resets && !is_found; attempt++) {
    out << "attempt " << attempt << std::endl;
    for (int i = 0; i < max_generations && !is_found; i++) {
      out << "\t" << i << ". ";
      generation();
      out << best_fitness() << std::endl;
      is_found = check();
    }
  }
  return is_found;
}

void genetic_algorithm::generation() {
  std::sort(genes.begin(), genes.end());

  selection();
  mutation();
  new_generation();
}

void genetic_algorithm::selection() {
  size_t n = genes.size();
  std::vector<bool> is_survived(n, true);

  unsigned kill_by_rank = randU32(max_kill_by_rank / 2, max_kill_by_rank + 1);
  unsigned random_kill = randU32(max_random_kill / 2, max_random_kill + 1);
  for (int i = 1; i <= kill_by_rank; i++)
    is_survived[n - i] = false;

  for (int i = 0, j = 0; i < random_kill;)
    if (is_survived[j = randU32(0, n - kill_by_rank)]) {
      is_survived[j] = false;
      i++;
    }

  std::vector<gene> t;
  for (int i = 0; i < n - kill_by_rank; i++)
    if (is_survived[i])
      t.emplace_back(genes[i]);
  genes = t;
}

void genetic_algorithm::new_generation() {
  size_t n = genes.size();
  genes.reserve(population_size);
  while (genes.size() < population_size) {
    auto i = random_unique_array(4, 0, n);
    for (auto &g : crossover({genes[i[0]], genes[i[1]], genes[i[2]], genes[i[3]]}))
      genes.emplace_back(g);
  }
}

void genetic_algorithm::mutation() {
  size_t n = genes.size();
  std::vector<bool> is_elitism(n, false);
  for (auto i : random_unique_array(elitism_num, 0, elitism_num * 2))
    is_elitism[i] = true;

  for (size_t i = 0; i != n; i++) {
    if (is_elitism[i])
      genes.push_back(genes[i]);
    genes[i].mutation(randU32(1, max_mutation + 1));
  }
}

std::vector<genetic_algorithm::gene> genetic_algorithm::crossover(const std::vector<gene> &random_genes) {
  std::pair<const gene *, const gene *> A{&random_genes[0], &random_genes[1]};
  std::pair<const gene *, const gene *> B{&random_genes[2], &random_genes[3]};
  if (*A.first > *A.second)
    std::swap(A.first, A.second);
  if (*B.first > *B.second)
    std::swap(B.first, B.second);
  std::vector<genetic_algorithm::gene> t;
  t.emplace_back(crossover(*A.first, *B.first));
  t.emplace_back(crossover(*A.second, *B.second));
  return t;
}
genetic_algorithm::gene genetic_algorithm::crossover(const genetic_algorithm::gene &gene1,
                                                     const genetic_algorithm::gene &gene2) {
  unsigned partition1 = randU32(0, gene1.len());
  unsigned partition2 = randU32(0, gene2.len());
  if (randU32(0, 2)) {
    auto t(std::move(gene2.get_subAlleles(0, partition2)));
    for (auto &i : gene1.get_subAlleles(partition1, gene1.len()))
      t.emplace_back(i);
    return gene(cube, t);
  } else {
    auto t(std::move(gene1.get_subAlleles(0, partition1)));
    for (auto &i : gene2.get_subAlleles(partition2, gene2.len()))
      t.emplace_back(i);
    return gene(cube, t);
  }
}
std::vector<unsigned> genetic_algorithm::random_unique_array(size_t n, unsigned l, unsigned r) {
  std::vector<unsigned> array(n);
  for (size_t i = 0, j = 0; i != n; ) {
    array[i] = randU32(l, r);
    for (j = 0; j != i; j++)
      if (array[i] != array[j])
        break;
    if (j == i)
      i++;
  }
  return array;
}
bool genetic_algorithm::check() const {
  for (const auto &g : genes)
    if (g.fitness() == 0)
      return true;
  return false;
}
unsigned genetic_algorithm::best_fitness() const {
  unsigned min = UINT32_MAX;
  for (const auto &g : genes)
    min = std::min(min, g.fitness());
  return min;
}

genetic_algorithm::gene::gene(const Cube &start)
    : cube(start), alleles(randU32(1, start_len)), fitness_(0), fitness_is_valid(false) {
  if (cube.fitness() == 0)
    return;
  for (auto &m : alleles) {
    std::cout << randU32(0, cube.n() - 1) << std::endl;
    m.set_deep(randU32(0, cube.n() - 1));
    m.set_count(randU32(1, 4));
    m.set_type(static_cast<int>(randU32(0, 6)));
    m(cube);
  }
}
unsigned genetic_algorithm::gene::fitness() const {
  if (fitness_is_valid)
    return fitness_;
  else {
    const_cast<gene*>(this)->fitness_is_valid = true;
    const_cast<gene*>(this)->fitness_ = cube.fitness();
    return fitness_;
  }
}

bool operator<(const genetic_algorithm::gene &gene1, const genetic_algorithm::gene &gene2) {
  return gene1.fitness() < gene2.fitness();
}
bool operator>(const genetic_algorithm::gene &gene1, const genetic_algorithm::gene &gene2) {
  return gene2 < gene1;
}
bool operator<=(const genetic_algorithm::gene &gene1, const genetic_algorithm::gene &gene2) {
  return !(gene1 > gene2);
}
bool operator>=(const genetic_algorithm::gene &gene1, const genetic_algorithm::gene &gene2) {
  return !(gene1 < gene2);
}
bool operator==(const genetic_algorithm::gene &gene1, const genetic_algorithm::gene &gene2) {
  return gene1.fitness() == gene2.fitness();
}
bool operator!=(const genetic_algorithm::gene &gene1, const genetic_algorithm::gene &gene2) {
  return !(gene1 == gene2);
}
genetic_algorithm::gene::gene(const Cube &start, std::vector<Cube::move> alleles_) :
    cube(start),
    alleles(std::move(alleles_)),
    fitness_(0),
    fitness_is_valid(false) {
  for (auto &i : alleles)
    i(cube);
}

std::vector<Cube::move> genetic_algorithm::gene::get_subAlleles(unsigned int l, unsigned int r) const {
  std::vector<Cube::move> t;
  for (size_t i = l; i != r; i++)
    t.emplace_back(alleles[i]);
  return t;
}
std::string genetic_algorithm::gene::to_string() const {
  std::string s;
  for (const auto &i : alleles)
    s += i.to_string() + " ";
  return s;
}

void genetic_algorithm::gene::mutation(size_t n) {
  fitness_is_valid = false;
  for (size_t i = 0; i != n; i++) {
    alleles.emplace_back(randU32(0, cube.n() - 1), randU32(1, 4), static_cast<int>(randU32(0, 6)));
    alleles.back().operator()(cube);
  }
}