#include "queue.hpp"
#include <iostream>
using namespace std;

template <class x> Queue<x>::Queue(int length) {
  size = length;
  rear = -1;
  front = 0;
  count = 0;
  list = new x[size];
}
template <class x> Queue<x>::~Queue() { delete[] list; }
template <class x> bool Queue<x>::isEmpty() { return count == 0; }
template <class x> bool Queue<x>::isFull() { return count == size; }
template <class x> void Queue<x>::enQueue(x item) {
  if (isFull()) {
    cout << "List is Full" << endl;
  } else {
    rear = (rear + 1) % size;
    list[rear] = item;
    count++;
  }
}
template <class x> void Queue<x>::deQueue() {
  if (isEmpty()) {
    cout << "List is Empty" << endl;
  } else {
    front = (front + 1) % size;
    count--;
  }
}
template <class x> x Queue<x>::top() { return list[front]; }
template <class x> bool Queue<x>::searchItem(x item) {
  int loop = 1;
  int temp = front;
  bool found = false;
  while (loop <= count && !found) {
    if (list[temp] == item)
      found = true;
    loop++;
    temp = (temp + 1) % size;
  }
  return found;
}
