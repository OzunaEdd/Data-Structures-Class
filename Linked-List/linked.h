#ifndef LIST
#define LIST
template <class x> struct Node {
  x info;
  Node<x> *next;
};
template <class x> class list {
private:
  int length;
  Node<x> *first;
  Node<x> *last;

public:
  list();
  ~list();
  list(const list<x> &);
  list &operator=(const list<x> &);
  void copy(const list<x> &);
  void makeEmpty();
  void insertItem(x);
  void deleteItem(x);
  bool searchItem(x);
  void printList();
  void printPosition(x);
  void deleteSmaller(x);
  int getLength();
  int getLargest();
  void insert_end(Node<x> *&, x item);
  void insertEnd(x);
  int betweenItems(x, x);
};

#endif
