#include <iostream>
#include "Cube/Field.h"
#include <typeinfo>

using namespace std;

void print(Field &f) {
  for (int i = 0; i < f.n(); i++) {
    for (int j = 0; j < f.n(); j++)
      cout << f.get(i, j);
    cout << endl;
  }
}

int main() {

  std::vector<std::vector<char>> array = {{'g', 'b', 'o'},
                                          {'g', 'r', 'o'},
                                          {'o', 'o', 'b'}};


  swap(array[0], array[1]);

  Field f(array);

  print(f);

  return 0;
}
