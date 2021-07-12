#pragma once

#include <random>

namespace Random {
unsigned randU32(unsigned, unsigned);
unsigned randU32(unsigned);
double randD(double);
double randD(double, double);
std::vector<unsigned int> random_unique_array(size_t n, unsigned l, unsigned r);
}