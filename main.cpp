#include <iostream>
#include "Cube/Field.h"
#include "Cube/Cube.h"
#include "genetic_algorithm/genetic_algorithm.h"

using namespace std;

int main() {

  Cube a;
//  Cube c;
//  c.scramble("1R1 1U2 1B1 1F3 1L2 1D1 1R2");
//  c.scramble("1R2");
////  cout << c;
  Cube b;
//  b = a;
//  b.scramble();
//  cout << a;
//  cout << b;

  cout << a.scramble() << endl;
  genetic_algorithm ga(a);
  cout << ga.solve();

  return 0;
}