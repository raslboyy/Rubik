#include "genetic_algorithm.h"

#include <algorithm>
#include <utility>
#include <fstream>
#include <limits>

#include "../Random.h"
#include "CFitness.h"
#include "CGeneration.h"
#include "CGene.h"

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
  CGeneration generation(cube, parameters);
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