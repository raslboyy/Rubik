#include <iostream>
#include "Cube/Field.h"
#include "Cube/Cube.h"

using namespace std;

int main() {

  Cube c;
  c.scramble("1R1 1U2 1B1 1F3 1L2 1D1 1R2");
//  c.scramble("1R2");
  cout << c;

  return 0;
}