#ifndef DOUBLELINK_H
#define DOUBLELINK_H
// Forward Declaration of all struct and class
template <class x> class DoubleLink;
template <class x> struct Node;

// Nodes that hold the data & also the next and previous node address;
template <class x> struct Node {
  x data;
  Node<x> *next;
  Node<x> *prev;
};
// Class that has all functionaly of the linked list
template <class x> class DoubleLink {
private:
  Node<x> *first;
  Node<x> *last;
  int length;

public:
  DoubleLink<x>();
  DoubleLink<x>(const DoubleLink<x> &);
  ~DoubleLink<x>();
  DoubleLink<x> operator=(const DoubleLink<x> &);
  void insertFront(x);
  void insertBack(x);
  void deleteItem(x);
  void destroyList();
  void printFoward();
  void printBackward();
  void printBoth();
  int replate_item(x, x);
  void deleteLast();
  bool searchItem(x);
  void insert(x);
  int getLength();
  void great(Node<x> *, x);
  void greater(x);
  void copy(const DoubleLink<x> &);
  void insertAtPosition(int, x);
  int howMany(x start, x end);
};

#endif
