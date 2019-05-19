#include "circularlinked.cpp"
#include "circularlinked.hpp"
#include <iostream>
using namespace std;

int main() {
  Circular<int> list;
  list.insertItem(5);
  list.insertItem(5);
  list.insertItem(3);
  list.insertItem(3);
  list.insertItem(4);
  Circular<int> list2;
  list2 = list;
  cout << list.howMany(5) << endl;
  cout << list.howMany(3) << endl;
  list2.print();
  cout << endl;
  list.print();
  return 0;
}
