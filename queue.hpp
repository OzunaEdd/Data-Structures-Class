#ifndef QUEUE_H
#define QUEUE_H
template <class x> class Queue {
private:
  int rear;
  int front;
  int size;
  int count;
  x *list;

public:
  Queue(int);
  ~Queue();
  void enQueue(x);
  void deQueue();
  bool isFull();
  bool isEmpty();
  bool searchItem(x);
  x top();
};

#endif
