#include "circularlinked.hpp"
#include <iostream>
using namespace std;
template <class x> Circular<x> Circular<x>::operator=(const Circular<x> &obj) {
  if (this != &obj) {
    first = nullptr;
    copy(obj);
  } else {
    cout << "Self Assignment" << endl;
  }
  return *this;
}
template <class x> Circular<x>::Circular(const Circular<x> &obj) { copy(obj); }
template <class x> void Circular<x>::insertItem(x item) {
  Node<x> *newNode = new Node<x>;
  Node<x> *current = nullptr;
  Node<x> *trail = nullptr;
  newNode->data = item;
  newNode->next = nullptr;
  if (first == nullptr) {
    first = newNode;
    first->next = first;
  }
  current = first;
  trail = current;
  current = current->next;
  while (current != first && item > current->data) {
    trail = current;
    current = current->next;
  }
  if (item > first->data) {
    newNode->next = first->next;
    first->next = newNode;
    first = newNode;
  } else {
    trail->next = newNode;
    newNode->next = current;
  }
}
template <class x> void Circular<x>::print() {
  Node<x> *current = first;
  do {
    current = current->next;
    cout << current->data << ' ';
  } while (current != first);
}
template <class x> Circular<x>::Circular() { first = nullptr; }
template <class x> Circular<x>::~Circular() {
  Node<x> *temp;
  Node<x> *current = first->next;
  first->next = nullptr;
  while (current != nullptr) {
    temp = current;
    current = current->next;
    delete temp;
  }
  first = nullptr;
}
template <class x> int Circular<x>::howMany(x item) {
  int count = 0;
  Node<x> *current = first;
  do {
    if (current->data == item)
      count++;
    current = current->next;
  } while (current != first && current->data <= item);

  return count;
}
template <class x> void Circular<x>::copy(const Circular<x> &obj) {
  Node<x> *newNode;
  Node<x> *current;
  Node<x> *trail;
  if (obj.first == nullptr) {
    first = nullptr;
  } else {
    first = new Node<x>;
    first->data = obj.first->data;
    first->next = first;
    current = obj.first;
    trail = first;
    current = current->next;
    while (current != obj.first) {
      newNode = new Node<x>;
      newNode->data = current->data;
      newNode->next = first;
      trail->next = newNode;
      trail = trail->next;
      current = current->next;
    }
  }
}
