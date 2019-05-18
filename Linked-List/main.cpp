#include "linked.cpp"
#include "linked.h"
#include <iostream>
using namespace std;

int main() {
  list<int> other;
  other.insertItem(6);
  other.insertItem(7);
  other.insertItem(9);
  other.insertItem(14);
  other.insertItem(21);
  other.insertItem(45);
  other.printList();
  cout << endl;
  cout << other.betweenItems(8, 21);
  return 0;
}
