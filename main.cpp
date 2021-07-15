#include <iostream>
#include <fstream>
#include "Cube/Side.h"
#include "Cube/Cube.h"
#include "genetic_algorithm/genetic_algorithm.h"

using namespace std;

template<size_t N = 10>
struct A{
  A() : n(N) {}
  int n;
};

int main() {

  Cube a(3, vector<Side>{
      Side({{4, 5, 5},
            {0, 0, 4},
            {4, 3, 0}}),
      Side({{5, 2, 4},
            {2, 1, 2},
            {0, 1, 5}}),
      Side({{1, 4, 1},
            {5, 2, 3},
            {5, 5, 3}}),
      Side({{4, 2, 1},
            {0, 3, 0},
            {3, 0, 1}}),
      Side({{3, 4, 2},
            {1, 4, 3},
            {0, 1, 0}}),
      Side({{2, 3, 2},
            {5, 5, 1},
            {3, 4, 2}})
  });
//  a.apply_scramble(
//      "2F2 1R1 2F2 2B2 2D1 2D2 2R2 1R2 2U1 2D2 2L2 1B2 2D1 2F1 2R1 1B2 2U2 2F1 1F1 1R1 2B1 1U1 2U2 1F1 2R2 1U1 2F2 1B1 2D1 2D1 1L1 2F2 2U1 2R1 1B2 2U2 2B2 2F2 2L2 2L1 2U1 1R2 2U2 2L2 2B2 2F1 2D2 2R1 2B1 3 0");
//  a.apply_scramble("0 1 2 3");
//  cout << a;
  genetic_algorithm::solve(a);
  int k = 14;
  A<k> aa;

  return 0;
}