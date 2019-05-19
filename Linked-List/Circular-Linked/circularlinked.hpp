#ifndef CIRCULARLINKED_H
#define CIRCULARLINKED_H

template <class x> struct Node {
  x data;
  Node<x> *next;
};
template <class x> class Circular {
private:
  Node<x> *first;
  int length;

public:
  Circular();
  Circular(const Circular<x> &);
  ~Circular();
  void copy(const Circular<x> &);
  Circular<x> operator=(const Circular<x> &);
  void insertItem(x);
  void deleteItem(x);
  bool searchItem(x);
  void print();
  int howMany(x);
  x get();
  int getLength();
};

#endif
