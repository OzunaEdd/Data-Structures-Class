#include "doubleLink.cpp"
#include <iostream>

int main() {
  DoubleLink<int> list;
  list.insert(3);
  list.insert(3);
  list.insert(3);
  list.insert(3);
  list.insert(4);
  list.insert(4);
  list.insert(4);
  cout << endl;
  list.printFoward();

  return 0;
}
