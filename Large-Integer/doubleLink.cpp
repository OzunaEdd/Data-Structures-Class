/**

        @author Eddie Ozuna

*/
#include "doubleLink.hpp"
#include <iostream>
#include <string>
using namespace std;

template <class x> bool DoubleLink<x>::searchItem(x item) {
  Node<x> *current = first;
  bool found = false;
  while (current != nullptr && !found) {
    if (current->data == item) {
      found = true;
    }
    current = current->next;
  }
  return found;
}
template <class x> void DoubleLink<x>::deleteItem(x item) {
  Node<x> *current = first;
  Node<x> *temp;
  if (current == nullptr) {
    cout << "empty list" << endl;
  } else {
    if (current->data == item) {
      temp = current;
      if (current->next != nullptr) {
        first = current->next;
        first->prev = nullptr;
      } else {
        first = nullptr;
        last = nullptr;
      }
      length--;
      delete temp;
    } else {
      while (current->next != nullptr && current->next->data != item) {
        current = current->next;
      }
      if (current->next->data == item) {
        length--;
        temp = current->next;
        if (current->next->next == nullptr) {
          current->next = nullptr;
          last = current;
          delete temp;
        } else {
          current->next->next->prev = current;
          current->next = current->next->next;
          delete temp;
        }
      }
    }
  }
}
template <class x> void DoubleLink<x>::destroyList() {
  Node<x> *temp;

  while (first != nullptr) {
    temp = first;
    first = first->next;
    delete temp;
  }
  first = nullptr;
  last = nullptr;
  length = 0;
}

// Function that Copy one object to another
template <class x> void DoubleLink<x>::copy(const DoubleLink<x> &obj) {
  Node<x> *newNode;
  Node<x> *current;
  if (first != nullptr) {
    destroyList();
  }
  if (obj.first == nullptr) {
    first = nullptr;
    last = nullptr;
    length = 0;
  } else {
    current = obj.first;
    first = new Node<x>;
    first->data = current->data;
    first->next = nullptr;
    last = first;
    current = current->next;
    length = obj.length;
    while (current != nullptr) {
      newNode = new Node<x>;
      newNode->data = current->data;
      newNode->next = nullptr;
      last->next = newNode;
      last = newNode;
      current = current->next;
    }
  }
}
// Default Contructor that inialize the list to empty
template <class x> DoubleLink<x>::DoubleLink() {
  first = nullptr;
  last = nullptr;
  length = 0;
}
// Copy Contructor that copy one object to another
template <class x> DoubleLink<x>::DoubleLink(const DoubleLink<x> &obj) {
  first = nullptr;
  copy(obj);
}
template <class x> bool DoubleLink<x>::isEmpty() { return (first == nullptr); }
// Assigment Operator being overload to be able to assign one object to another
template <class x>
DoubleLink<x> DoubleLink<x>::operator=(const DoubleLink<x> &obj) {
  if (this != &obj) {
    length = obj.length;
    copy(obj);
  } else {
    cout << "SELF ASSIGMENT" << endl;
  }
  return *this;
}
template <class x> bool DoubleLink<x>::isZero() {
  Node<x> *current = first;
  bool zero = false;
  while (current != nullptr && current->data == 0) {
    current = current->next;
  }
  if (current == nullptr) {
    zero = true;
  }
  return zero;
}
// Detructor it make sure that it destroy all node within the list
template <class x> DoubleLink<x>::~DoubleLink() { destroyList(); }
// Function to insert a item to the front of the list
template <class x> void DoubleLink<x>::insertFront(x item) {
  Node<x> *newNode = new Node<x>;
  newNode->data = item;
  newNode->next = nullptr;
  newNode->prev = nullptr;
  if (first == nullptr) {
    length++;
    first = newNode;
    last = newNode;
  } else {
    length++;
    newNode->next = first;
    first->prev = newNode;
    first = newNode;
  }
}
// Function to insert an item to the back of list
template <class x> void DoubleLink<x>::insertBack(x item) {
  Node<x> *newNode = new Node<x>;
  newNode->data = item;
  newNode->next = nullptr;
  newNode->prev = nullptr;
  if (last == nullptr) {
    length++;
    last = newNode;
    first = newNode;
  } else {
    length++;
    last->next = newNode;
    newNode->prev = last;
    last = newNode;
  }
}
// Function to print all items of the list foward
template <class x> void DoubleLink<x>::printFoward() {
  Node<x> *front = first;
  while (front != nullptr) {
    cout << front->data;
    front = front->next;
  }
  cout << endl;
}
// Function to print all items of the list backward
template <class x> void DoubleLink<x>::printBackward() {
  Node<x> *back = last;
  while (back != nullptr) {
    cout << back->data;
    back = back->prev;
  }
  cout << endl;
}
// Function that return how many node are in the list
template <class x> int DoubleLink<x>::getLength() { return length; }
// Function that return the address of the first node to the iterator
template <class x> Iterator<x> DoubleLink<x>::begin() {
  Iterator<x> i;
  i.position = first;
  i.container = this;
  return i;
}
// Function that return the address of the last node to the iterator
template <class x> Iterator<x> DoubleLink<x>::lastt() {
  Iterator<x> i;
  i.position = last;
  i.container = this;
  return i;
}
// Function that return null to the iterator indicating the end of the list
template <class x> Iterator<x> DoubleLink<x>::end() {
  Iterator<x> i;
  i.position = nullptr;
  i.container = this;
  return i;
}

// Function check if object are equal
template <class x> bool Iterator<x>::operator==(const Iterator &i) {
  return position == i.position;
}
// Function check if object are not equal
template <class x> bool Iterator<x>::operator!=(const Iterator &i) {
  return position != i.position;
}
// Function that increment through the list
template <class x> Iterator<x> Iterator<x>::operator++(int) {
  position = position->next;
  return *this;
}
// Function that increment through the list
template <class x> Iterator<x> Iterator<x>::operator++() {
  position = position->next;
  return *this;
}
// Function that decrement through the list
template <class x> Iterator<x> Iterator<x>::operator--() {
  position = position->prev;
  return *this;
}
// Function that decrement through the list
template <class x> Iterator<x> Iterator<x>::operator--(int) {
  position = position->prev;
  return *this;
}
template <class x>
Iterator<x> Iterator<x>::operator=(const DoubleLink<x> &obj) {
  position = obj.first;
  return *this;
}

template <class x> x Iterator<x>::operator*() { return position->data; }
template <class x> void Iterator<x>::next() { position = position->next; }
template <class x> x Iterator<x>::get() { return position->data; }
template <class x> void Iterator<x>::insert(x item) { position->data = item; }
template <class x> Iterator<x>::Iterator() {}
