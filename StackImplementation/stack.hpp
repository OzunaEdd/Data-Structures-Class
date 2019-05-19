#ifndef STACK_H
#define STACK_H

template <class x> struct Node {
  x data;
  Node<x> *next;
};

template <class x> class Stack {
private:
  Node<x> *Top;
  int Size;

public:
  Stack();
  Stack(const Stack<x> &);
  ~Stack();
  Stack<x> operator=(const Stack<x> &);
  x top();
  void pop();
  void push(x);
  bool empty();
  int size();
};

#endif
