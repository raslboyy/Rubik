#include "CGeneration.h"
#include "CGene.h"

genetic_algorithm::CGeneration::CGeneration(const Cube &c, const Parameters &p) :
    cube(c),
    parameters(p),
    genes(p.GetPopulationSize(), CGene(c)) {}

void genetic_algorithm::CGeneration::update() {
  std::sort(genes.begin(), genes.end());
  selection();
  elitism();
  mutation();
}

void genetic_algorithm::CGeneration::reset() {
  genes.assign(parameters.GetPopulationSize(), CGene(cube));
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

  std::vector<CGene> t;
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