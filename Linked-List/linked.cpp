/*
Author Eddie Ozuna
Linked List Class
Included Basic Functions To work with a Linked List
*/

#include "linked.h"
#include <iostream>
using namespace std;

template <class x> list<x>::list() {
  first = nullptr;
  last = nullptr;
  length = 0;
}
/*
template <class x> void list<x>::insertEnd(x item) { insert_end(first, item); }
template <class x> void list<x>::insert_end(Node<x> *&current, x item) {
  if (current != nullptr) {
    insert_end(current->next, item);
  } else {
    current = new Node<x>;
    current->info = item;
    current->next = nullptr;
  }
}
*/
template <class x> list<x>::~list() {
  Node<x> *temp = nullptr;
  while (temp != nullptr && length != 0) {
    length--;
    temp = first;
    first = first->next;
    delete temp;
  }
  length = 0;
}

template <class x> list<x>::list(const list<x> &obj) {
  first = nullptr;
  copy(obj);
}
template <class x> list<x> &list<x>::operator=(const list<x> &obj) {
  if (this != &obj) {
    copy(obj);
  }
  return *this;
}
template <class x> void list<x>::copy(const list<x> &obj) {
  Node<x> *newNode;
  Node<x> *current;
  length = obj.length;
  if (obj.first == nullptr) {
    first = nullptr;
    last = nullptr;
    length = 0;
  } else {
    current = obj.first;

    first = new Node<x>;
    first->info = current->info;
    first->next = nullptr;
    last = first;
    current = current->next;

    while (current != nullptr) {
      newNode = new Node<x>;
      newNode->info = current->info;
      newNode->next = nullptr;
      last->next = newNode;
      last = newNode;
      current = current->next;
    }
  }
}
template <class x> void list<x>::insertItem(x item) {
  Node<x> *temp = new Node<x>;
  Node<x> *trailCurrent;
  Node<x> *current;
  bool found = false;
  temp->info = item;
  temp->next = nullptr;
  if (first == nullptr) {
    first = temp;
    last = temp;
    length++;
  } else {
    current = first;
    while (current != nullptr && !found) {
      if (current->info >= item) {
        found = true;
      } else {
        trailCurrent = current;
        current = current->next;
      }
    }
    if (current == first) {
      temp->next = first;
      first = temp;
      length++;
    } else {
      trailCurrent->next = temp;
      temp->next = current;
      length++;
      if (current == nullptr) {
        last = temp;
      }
    }
  }
}
/*
template <class x> void list<x>::insertItem(x item) {
  Node<x> *newNode = new Node<x>;
  newNode->info = item;
  newNode->next = nullptr;
  if (first == nullptr) {
    first = newNode;
    last = newNode;
  } else {
    last->next = newNode;
    last = newNode;
  }
}
*/
template <class x> int list<x>::getLargest() {
  if (first != nullptr) {
    Node<x> *current = first;
    int largest = current->info;
    while (current->next != nullptr) {
      if (largest < current->next->info) {
        largest = current->next->info;
      }
      current = current->next;
    }
    return largest;
  } else {
    return -1;
  }
}
template <class x> void list<x>::printList() {
  Node<x> *temp = first;
  if (temp == nullptr) {
    cout << "LIST IS EMPTY" << endl;
  } else {
    while (temp != nullptr) {
      cout << temp->info << ' ';
      temp = temp->next;
    }
    cout << endl;
  }
}
template <class x> void list<x>::deleteItem(x item) {
  Node<x> *temp = first;
  Node<x> *current;
  if (temp->info == item) {
    length--;
    first = temp->next;
    delete temp;
  } else {
    length--;
    while (temp->next != nullptr && temp->next->info != item) {
      temp = temp->next;
    }
    if (temp->next->info == item) {
      current = temp->next;
      temp->next = temp->next->next;
      delete current;
    }
  }
}
template <class x> void list<x>::makeEmpty() {
  Node<x> *temp = first;
  Node<x> *current;
  while (temp != nullptr) {
    length--;
    current = temp;
    first = temp->next;
    temp = first;
    delete current;
  }
}
template <class x> int list<x>::getLength() { return length; }
template <class x> bool list<x>::searchItem(x item) {
  Node<x> *temp = first;
  bool found = false;
  while (temp != nullptr) {
    if (temp->info == item) {
      found = true;
    }
    temp = temp->next;
  }
  return found;
}
template <class x> void list<x>::printPosition(x item) {
  Node<x> *current = first;
  int count = 0;
  while (current != nullptr && current->info <= item) {
    count++;
    if (current->info == item) {
      cout << "Position : " << count << endl;
    }
    current = current->next;
  }
  if (current == nullptr) {
    cout << "Item not in the list" << endl;
  }
}
template <class x> void list<x>::deleteSmaller(x item) {
  Node<x> *temp;
  while (first != nullptr && first->info < item) {
    temp = first;
    first = first->next;
    delete temp;
  }
}
template <class x> int list<x>::betweenItems(x start, x end) {
  int count = 0;
  Node<x> *current = first;
  while (current != nullptr && current->info <= end) {
    if (current->info >= start && current->info <= end) {
      count++;
    }
    current = current->next;
  }
  return count;
}

