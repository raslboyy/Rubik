#include <iostream>
#include "Cube/Field.h"
#include "Cube/Cube.h"

using namespace std;

//void print(Field &f) {
//  for (int i = 0; i < f.n(); i++) {
//    for (int j = 0; j < f.n(); j++)
//      cout << f.get(i, j);
//    cout << endl;
//  }
//}

int main() {

  Cube c(4);
  c.scramble("2R1");
  cout << c;

//  print(f);

  return 0;
}

