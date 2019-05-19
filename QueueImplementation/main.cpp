#include "queue.cpp"
#include "queue.hpp"
#include <iostream>
using namespace std;

int main() {
  Queue<int> list(4);
  for (int i = 1; i <= 4; i++) {
    list.enQueue(i);
  }
  list.deQueue();
  list.deQueue();
  list.deQueue();
  list.enQueue(5);
  list.deQueue();
  list.deQueue();
  list.enQueue(3);
  list.top();
  if (list.searchItem(3)) {
    cout << "found";
  } else {
    cout << "not found";
  }

  return 0;
}
