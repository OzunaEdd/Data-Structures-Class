/**

        @author Eddie Ozuna

*/
#ifndef DOUBLELINK_H
#define DOUBLELINK_H
// Forward Declaration of all struct and class
template <class x> class DoubleLink;
template <class x> struct Node;
template <class x> class Iterator;

// Iterator Class to keep track of the position of the linked list and also
// retrieve the data
template <class x> class Iterator {

private:
  friend class DoubleLink<x>;
  Node<x> *position;
  DoubleLink<x> *container;

public:
  Iterator();
  bool operator==(const Iterator &);
  bool operator!=(const Iterator &);
  Iterator operator=(const DoubleLink<x> &);
  Iterator operator++(int);
  Iterator operator++();
  Iterator operator--();
  Iterator operator--(int);
  x operator*();
  void next();
  void insert(x);
  x get();
};
// Nodes that hold the data & also the next and previous node address;
template <class x> struct Node {
  x data;
  Node<x> *next;
  Node<x> *prev;
};
// Class that has all functionalities of the linked list
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
  bool isEmpty();
  bool isZero();
  bool searchItem(x);
  Iterator<x> begin();
  Iterator<x> lastt();
  Iterator<x> end();
  int getLength();
  void copy(const DoubleLink<x> &);
};

#endif
