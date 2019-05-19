#include "stack.hpp"
#include <iostream>
#include <string>
using namespace std;
template <class x> Stack<x>::Stack() {
  Top = nullptr;
  Size = 0;
}
template <class x> Stack<x>::~Stack() {
  Node<x> *temp;
  while (Top != nullptr) {
    temp = Top;
    Top = Top->next;
    delete temp;
  }
  Top = nullptr;
  Size = 0;
}
template <class x> Stack<x>::Stack(const Stack<x> &obj) {
  Node<x> *current;
  Node<x> *newNode;
  Node<x> *trailCurrent;
  if (obj.Top == nullptr) {
    Top = nullptr;
    Size = 0;
  } else {
    current = obj.Top;
    Top = new Node<x>;
    Top->data = current->data;
    Top->next = nullptr;
    Size = obj.Size;
    trailCurrent = Top;
    current = current->next;
    while (current != nullptr) {
      newNode = new Node<x>;
      newNode->data = current->data;
      newNode->next = nullptr;
      trailCurrent->next = newNode;
      trailCurrent = newNode;
      current = current->next;
    }
  }
}
template <class x> Stack<x> Stack<x>::operator=(const Stack<x> &obj) {
  Node<x> *current;
  Node<x> *newNode;
  Node<x> *trailCurrent;
  if (this != &obj) {
    if (obj.Top == nullptr) {
      Top = nullptr;
      Size = 0;
    } else {
      current = obj.Top;
      Top = new Node<x>;
      Top->data = current->data;
      Top->next = nullptr;
      Size = obj.Size;
      trailCurrent = Top;
      current = current->next;
      while (current != nullptr) {
        newNode = new Node<x>;
        newNode->data = current->data;
        newNode->next = nullptr;
        trailCurrent->next = newNode;
        trailCurrent = newNode;
        current = current->next;
      }
    }
  } else {
    cout << "SELF ASSIGMENT" << endl;
  }
  return *this;
}
template <class x> void Stack<x>::push(x item) {
  Node<x> *newNode = new Node<x>;
  newNode->data = item;
  newNode->next = Top;
  Top = newNode;
  Size++;
}
template <class x> void Stack<x>::pop() {
  Node<x> *temp;
  temp = Top;
  Top = Top->next;
  delete temp;
}
template <class x> int Stack<x>::size() { return Size; }
template <class x> bool Stack<x>::empty() { return Top == nullptr; }
template <class x> x Stack<x>::top() { return Top->data; }
