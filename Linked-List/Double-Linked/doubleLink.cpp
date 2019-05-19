#include "doubleLink.hpp"
#include <iostream>
#include <string>
using namespace std;

template <class x> class DoubleLink;
template <class x> struct Node;
template <class x> void DoubleLink<x>::printBoth() {
  if (first != nullptr) {
    Node<x> *forward = first;
    Node<x> *backward = last;
    while (forward != nullptr) {
      cout << forward->data << ' ';
      forward = forward->next;
    }
    cout << endl;
    while (backward != nullptr) {
      cout << backward->data << ' ';
      backward = backward->prev;
    }
  } else
    cout << "Empty List";
}
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
template <class x> int DoubleLink<x>::replate_item(x olditem, x newitem) {
  Node<x> *current = first;
  int count = 0;
  while (current != nullptr && searchItem(olditem)) {
    if (current->data == olditem) {
      current->data = newitem;
      count++;
    }
    current = current->next;
  }
  return count;
}
template <class x> void DoubleLink<x>::deleteItem(x item) {
  Node<x> *current = first;
  Node<x> *temp;
  if (current == nullptr) {
    cout << "Empty list" << endl;
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
      if (current->next == nullptr) {
        cout << "Not found " << endl;
      } else {
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
}
template <class x> void DoubleLink<x>::destroyList() {
  Node<x> *temp;
  if (first == nullptr) {
    cout << "Empty linked list" << endl;
  } else {
    while (first != nullptr) {
      temp = first;
      first = first->next;
      delete temp;
    }
    first = nullptr;
    last = nullptr;
    length = 0;
  }
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
// Detructor it make sure that it destroy all node within the list
template <class x> DoubleLink<x>::~DoubleLink() { destroyList(); }
// Function to insert a item to the front of the list
template <class x> void DoubleLink<x>::insertFront(x item) {
  Node<x> *newNode = new Node<x>;
  newNode->data = item;
  newNode->next = nullptr;
  newNode->prev = nullptr;
  if (first == nullptr) {
    first = newNode;
    last = newNode;
  } else {
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
    newNode->prev = newNode;
    last = newNode;
  }
}
// Function to print all items of the list foward
template <class x> void DoubleLink<x>::printFoward() {
  Node<x> *front = first;
  if (first == nullptr) {
    cout << "Empty linked list" << endl;
  } else {
    while (front != nullptr) {
      cout << front->data << ' ';
      front = front->next;
    }
  }
  cout << endl;
}
// Function to print all items of the list backward
template <class x> void DoubleLink<x>::printBackward() {
  Node<x> *back = last;
  if (back == nullptr) {
    cout << "Empty linked list" << endl;
  } else {
    while (back != nullptr) {
      cout << back->data << ' ';
      back = back->prev;
    }
  }
  cout << endl;
}
// Function that return how many node are in the list
template <class x> int DoubleLink<x>::getLength() { return length; }

template <class x> void DoubleLink<x>::deleteLast() {
  Node<x> *temp = last;
  if (last == first) {
    first = nullptr;
    last = nullptr;
  } else {
    last = last->prev;
    last->next = nullptr;
  }
  delete temp;
}
template <class x> int DoubleLink<x>::howMany(x start, x end) {
  Node<x> *current = first;
  int count = 0;
  while (current != nullptr && current->data <= end) {
    if (current->data >= start && current->data <= end) {
      count++;
    }
    current = current->next;
  }
  return count;
}
template <class x> void DoubleLink<x>::insert(x item) {
  Node<x> *newNode = new Node<x>;
  newNode->data = item;
  newNode->next = nullptr;
  newNode->prev = nullptr;
  if (first == nullptr) {
    first = newNode;
    last = newNode;
  } else {
    last->next = newNode;
    newNode->prev = last;
    last = newNode;
  }
}
template <class x> void DoubleLink<x>::insertAtPosition(int position, x item) {
  if (position <= 0) {
    cout << "error";
  } else {
    Node<x> *current = first;
    Node<x> *newNode = new Node<x>;
    newNode->data = item;
    newNode->next = nullptr;
    newNode->prev = nullptr;
    int n = 1;
    while (current != nullptr && n != position) {
      current = current->next;
      n++;
    }
    if (current == nullptr) {
      last->next = newNode;
      newNode->prev = last;
      last = newNode;
    } else {
      if (current == first) {
        first->prev = newNode;
        newNode->next = first;
        first = newNode;
      } else {
        current->prev->next = newNode;
        newNode->prev = current->prev;
        newNode->next = current;
        current->prev = newNode;
      }
    }
  }
}
template <class x> void DoubleLink<x>::greater(x item) { great(first, item); }
template <class x> void DoubleLink<x>::great(Node<x> *current, x item) {
  if (current != nullptr) {
    if (current->data > item) {
      cout << current->data << ' ';
    }
    great(current->next, item);
  }
}
