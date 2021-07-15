#include "CFitness.h"

genetic_algorithm::CFitness::CFitness(size_t n, size_t pow) {

}
unsigned genetic_algorithm::CFitness::operator()(const Cube &cube) const {
  return cube.stupidFitness();
}