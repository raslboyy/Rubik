#include <iostream>
#include <fstream>
#include "Cube/Side.h"
#include "Cube/Cube.h"
//#include "genetic_algorithm/genetic_algorithm.h"

using namespace std;

int main() {

  Cube a;
  a.apply_scramble("2F2 1R1 2F2 2B2 2D1 2D2 2R2 1R2 2U1 2D2 2L2 1B2 2D1 2F1 2R1 1B2 2U2 2F1 1F1 1R1 2B1 1U1 2U2 1F1 2R2 1U1 2F2 1B1 2D1 2D1 1L1 2F2 2U1 2R1 1B2 2U2 2B2 2F2 2L2 2L1 2U1 1R2 2U2 2L2 2B2 2F1 2D2 2R1 2B1 3");
  cout << a;

  return 0;
}