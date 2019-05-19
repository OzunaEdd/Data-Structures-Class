// AVL tree
/*

        @author Eddie Ozuna
        Only Modify the Delete Function

*/
#include <cmath>
#include <deque>
#include <iomanip>
#include <iostream>
using namespace std;

template <class xtype> struct tnode {
  int balance;
  xtype info;
  tnode<xtype> *left;
  tnode<xtype> *right;
};

template <class xtype> class AVLtree {
private:
  tnode<xtype> *root;

public:
  AVLtree();
  ~AVLtree();
  void destroy();
  void destroy(tnode<xtype> *&);
  AVLtree(const AVLtree<xtype> &);
  void copyAVL(tnode<xtype> *&, tnode<xtype> *);
  bool isEmpty();
  void rotateLeft(tnode<xtype> *&);
  void rotateRight(tnode<xtype> *&);
  void balanceLeft(tnode<xtype> *&);
  void balanceRight(tnode<xtype> *&);
  bool printAncestors(tnode<xtype> *p, xtype target);
  void Ancestors(xtype target);
  bool searchItem(xtype item);
  void Descendants(xtype item);
  void helpDescendants(tnode<xtype> *p, xtype item);
  void correctBalance(tnode<xtype> *&p);
  void BalanceDelete(tnode<xtype> *&p);
  void insertNode(tnode<xtype> *&, xtype, bool &);
  void insert(xtype);
  int maxH(tnode<xtype> *);
  void printB(int, int, int, int, const deque<tnode<xtype> *> &);
  void printN(int, int, int, int, const deque<tnode<xtype> *> &);
  void printL(int, const deque<tnode<xtype> *> &);
  void printAVL(tnode<xtype> *);
  void print();
  void Delete(xtype item);
  void Delete(tnode<xtype> *&p, xtype item);
  void DeleteNode(tnode<xtype> *&p);
};

template <class xtype> void AVLtree<xtype>::Descendants(xtype item) {
  tnode<xtype> *p = root;
  bool found = false;
  while (p != nullptr && !found) {
    if (item > p->info) {
      p = p->right;
    } else if (item < p->info) {
      p = p->left;
    } else {
      found = true;
    }
  }
  if (found) {
    helpDescendants(p, item);
  } else
    cout << "item not in the tree" << endl;
}
template <class xtype>
void AVLtree<xtype>::helpDescendants(tnode<xtype> *p, xtype item) {
  if (p != nullptr) {
    if (p->info != item) {
      cout << p->info << endl;
    }
    helpDescendants(p->left, item);
    helpDescendants(p->right, item);
  }
}
template <class xtype> void AVLtree<xtype>::Ancestors(xtype target) {
  printAncestors(root, target);
}
template <class xtype>
bool AVLtree<xtype>::printAncestors(tnode<xtype> *p, xtype target) {
  /* base cases */
  if (p == NULL)
    return false;

  if (p->info == target)
    return true;

  if (printAncestors(p->left, target) || printAncestors(p->right, target)) {
    cout << p->info << " ";
  }

  /* If target is present in either left or right subtree of this node,
     then print this node */
  /* Else return false */
  return false;
}
template <class xtype> bool AVLtree<xtype>::searchItem(xtype item) {
  bool found = false;
  tnode<xtype> *p = root;
  while (p != nullptr && !found) {

    if (item > p->info) {
      p = p->right;
    } else if (item < p->info) {
      p = p->left;
    } else {
      found = true;
    }
  }
  return found;
}
template <class xtype> void AVLtree<xtype>::Delete(xtype item) {
  Delete(root, item);
}
// Helper Function to correct the balance value of a node
template <class xtype> void AVLtree<xtype>::correctBalance(tnode<xtype> *&p) {
  tnode<xtype> *leftChild = p;
  tnode<xtype> *rightChild = p;
  while (leftChild != nullptr) {
    if (maxH(leftChild->left) < maxH(leftChild->right)) {
      leftChild->balance = 1;
    } else if (maxH(leftChild->left) > maxH(leftChild->right)) {
      leftChild->balance = -1;
    } else {
      leftChild->balance = 0;
    }
    leftChild = leftChild->left;
  }
  while (rightChild != nullptr) {
    if (maxH(rightChild->left) < maxH(rightChild->right)) {
      rightChild->balance = 1;
    } else if (maxH(rightChild->left) > maxH(rightChild->right)) {
      rightChild->balance = -1;
    } else {
      rightChild->balance = 0;
    }
    rightChild = rightChild->right;
  }
}
// Helper Function that helps the delete function rotate when needed if a tree
// is unbalance
template <class xtype> void AVLtree<xtype>::BalanceDelete(tnode<xtype> *&p) {
  if (p != nullptr) {
    // Correct the balance of a node after it has deleted
    correctBalance(p);
    // Perfom left rotation, right rotation,left right rotation, right left
    // rotation when needed
    if (maxH(p->left) - maxH(p->right) == 2) {
      if (p->balance == -1 && p->left->balance == 1) {
        rotateLeft(p->left);
        rotateRight(p);
      } else
        rotateRight(p);
    }
    if (maxH(p->right) - maxH(p->left) == 2) {
      if (p->balance == 1 && p->right->balance == -1) {
        rotateRight(p->right);
        rotateLeft(p);
      } else
        rotateLeft(p);
    }
    if (p->left != nullptr) {
      if (maxH(p->left->left) - maxH(p->left->right) == 2) {
        if (p->left->balance == -1 && p->left->left->balance == 1) {
          rotateLeft(p->left->left);
          rotateRight(p->left);
        } else
          rotateRight(p->left);
      }
      if (maxH(p->left->right) - maxH(p->left->left) == 2) {
        if (p->left->balance == 1 && p->left->right->balance == -1) {
          rotateRight(p->left->right);
          rotateLeft(p->left);
        } else
          rotateLeft(p->left);
      }
    }
    if (p->right != nullptr) {
      if (maxH(p->right->left) - maxH(p->right->right) == 2) {
        if (p->right->balance == -1 && p->right->left->balance == 1) {
          rotateLeft(p->right->left);
          rotateRight(p->right);
        } else
          rotateRight(p->right);
      }
      if (maxH(p->right->right) - maxH(p->right->left) == 2) {
        if (p->right->balance == 1 && p->right->right->balance == -1) {
          rotateRight(p->right->right);
          rotateLeft(p->right);
        } else
          rotateLeft(p->right);
      }
    }
    // Correct the balance value of a node after it has rotated
    correctBalance(p);
  }
}
template <class xtype>
void AVLtree<xtype>::Delete(tnode<xtype> *&p, xtype item) {
  if (p == NULL)
    cout << "ITEM NOT IN TREE";
  else {
    if (item < p->info) {
      Delete(p->left, item);
    } else if (item > p->info) {
      Delete(p->right, item);
    } else {
      DeleteNode(p);
    }
    // Correct balance of a node and rotate if it unbalance
    BalanceDelete(p);
  }
}
template <class xtype> void AVLtree<xtype>::DeleteNode(tnode<xtype> *&p) {
  tnode<xtype> *s = p;

  if (p->left == NULL)
    p = p->right;

  else if (p->right == NULL)
    p = p->left;
  else {
    s = p->left;
    tnode<xtype> *r = NULL;

    while (s->right != NULL) {
      r = s;
      s = s->right;
    }
    p->info = s->info;

    if (r != NULL)
      r->right = s->left;
    else
      p->left = s->left;
  }
  delete s;
}

template <class xtype> AVLtree<xtype>::AVLtree() { root = NULL; }

template <class xtype> AVLtree<xtype>::~AVLtree() { destroy(root); }
template <class xtype> void AVLtree<xtype>::destroy() { destroy(root); }

template <class xtype> void AVLtree<xtype>::destroy(tnode<xtype> *&p) {
  if (p != NULL) {
    destroy(p->left);
    destroy(p->right);
    delete p;
    p = NULL;
  }
}

template <class xtype>
void AVLtree<xtype>::copyAVL(tnode<xtype> *&troot, tnode<xtype> *croot) {
  if (croot == NULL)
    troot = NULL;
  else {
    troot = new tnode<xtype>;
    troot->info = croot->info;
    copyAVL(troot->left, croot->left);
    copyAVL(troot->right, croot->right);
  }
}

template <class xtype> AVLtree<xtype>::AVLtree(const AVLtree<xtype> &other) {
  if (other.root == NULL)
    root = NULL;
  else
    copyAVL(root, other.root);
}

template <class xtype> bool AVLtree<xtype>::isEmpty() { return root == NULL; }

template <class xtype> void AVLtree<xtype>::rotateLeft(tnode<xtype> *&p) {
  // holds  right of p
  tnode<xtype> *q;

  if (p == NULL || p->right == NULL)
    cout << "ERROR – TREE EMPTY OR NO RIGHT CHILD";
  else {
    q = p->right;
    // make left become right
    p->right = q->left;
    q->left = p;
    // p is new root
    p = q;
  }
}

template <class xtype> void AVLtree<xtype>::rotateRight(tnode<xtype> *&p) {
  // holds left of p
  tnode<xtype> *q;

  if (p == NULL || p->left == NULL)
    cout << "ERROR – TREE EMPTY OR NO LEFT CHILD";
  else {
    q = p->left;
    // make left become right
    p->left = q->right;
    q->right = p;
    // p is new root
    p = q;
  }
}

template <class xtype> void AVLtree<xtype>::balanceLeft(tnode<xtype> *&p) {
  tnode<xtype> *l;
  tnode<xtype> *r;

  l = p->left;

  if (l->balance == -1) {
    p->balance = 0;
    l->balance = 0;
    rotateRight(p);
  } else if (l->balance == 1) {
    r = l->right;
    if (r->balance == -1) {
      p->balance = 1;
      l->balance = 0;
    } else if (r->balance == 1) {
      p->balance = 0;
      l->balance = -1;
    } else if (r->balance == 0) {
      p->balance = 0;
      l->balance = 0;
    }
    r->balance = 0;
    rotateLeft(l);
    p->left = l;
    rotateRight(p);
  } else
    cout << "ERROR";
}

template <class xtype> void AVLtree<xtype>::balanceRight(tnode<xtype> *&p) {
  tnode<xtype> *l;
  tnode<xtype> *r;

  r = p->right;

  if (r->balance == -1) {
    l = r->left;
    if (l->balance == -1) {
      p->balance = 0;
      r->balance = 1;
    } else if (l->balance == 1) {
      p->balance = -1;
      r->balance = 0;
    } else if (l->balance == 0) {
      p->balance = 0;
      r->balance = 0;
    }
    l->balance = 0;
    rotateRight(r);
    p->right = r;
    rotateLeft(p);
  } else if (r->balance == 1) {
    p->balance = 0;
    r->balance = 0;
    rotateLeft(p);
  } else
    cout << "ERROR";
}

template <class xtype>
void AVLtree<xtype>::insertNode(tnode<xtype> *&p, xtype item, bool &taller) {
  if (p == NULL) {
    p = new tnode<xtype>;
    p->info = item;
    p->left = NULL;
    p->right = NULL;
    p->balance = 0;
    taller = true;
  } else if (p->info == item)
    cout << "ERROR NO DUPLICATES";
  else if (p->info > item) {
    insertNode(p->left, item, taller);

    if (taller) {
      if (p->balance == -1) {
        balanceLeft(p);
        taller = false;
      } else if (p->balance == 1) {
        p->balance = 0;
        taller = false;
      } else
        p->balance = -1;
    }
  } else {
    insertNode(p->right, item, taller);

    if (taller) {
      if (p->balance == -1) {
        p->balance = 0;
        taller = false;
      } else if (p->balance == 1) {
        balanceRight(p);
        taller = false;
      } else
        p->balance = 1;
    }
  }
}

template <class xtype> void AVLtree<xtype>::insert(xtype item) {
  bool taller = false;
  insertNode(root, item, taller);
}

template <class xtype> int AVLtree<xtype>::maxH(tnode<xtype> *p) {

  if (p == NULL)
    return 0;

  int leftH = maxH(p->left);
  int rightH = maxH(p->right);

  return (leftH > rightH) ? leftH + 1 : rightH + 1;
}

template <class xtype>
void AVLtree<xtype>::printB(int bLen, int nSpLen, int sLen, int nLevel,
                            const deque<tnode<xtype> *> &nQ) {

  typename deque<tnode<xtype> *>::const_iterator it = nQ.begin();

  for (int i = 0; i < nLevel / 2; i++) {
    cout << ((i == 0) ? setw(sLen - 1) : setw(nSpLen - 2)) << ""
         << ((*it++) ? "/" : " ");
    cout << setw(2 * bLen + 2) << "" << ((*it++) ? "\\" : " ");
  }
  cout << endl;
}

template <class xtype>
void AVLtree<xtype>::printN(int bLen, int nSpLen, int sLen, int nLevel,
                            const deque<tnode<xtype> *> &nQ) {

  typename deque<tnode<xtype> *>::const_iterator it = nQ.begin();

  for (int i = 0; i < nLevel; i++, it++) {
    cout << ((i == 0) ? setw(sLen) : setw(nSpLen)) << ""
         << ((*it && (*it)->left) ? setfill('_') : setfill(' '));

    cout << setw(bLen + 2);
    if ((*it) != NULL) {
      cout << (*it)->info;
      // cout << ' ' << (*it)->balance;
    } else
      cout << "";

    cout << ((*it && (*it)->right) ? setfill('_') : setfill(' ')) << setw(bLen)
         << "" << setfill(' ');
  }
  cout << endl;
}

template <class xtype>
void AVLtree<xtype>::printL(int nLevel, const deque<tnode<xtype> *> &nQ) {

  typename deque<tnode<xtype> *>::const_iterator it = nQ.begin();

  for (int i = 0; i < nLevel; i++, it++) {
    cout << ((i == 0) ? setw(2) : setw(4));
    if ((*it) != NULL) {
      cout << (*it)->info;
      // cout << ' ' << (*it)->balance;
    } else
      cout << "";
  }
  cout << endl;
}

template <class xtype> void AVLtree<xtype>::printAVL(tnode<xtype> *p) {
  int h = maxH(p);
  int nLevel = 1;

  int bLen = 2 * ((int)pow(2.0, h) - 1) - 2 * (int)pow(2.0, h - 1);

  int nSpaceLen = 2 + 2 * (int)pow(2.0, h);

  int sLen = bLen + 2;

  deque<tnode<xtype> *> nQ;
  nQ.push_back(p);

  for (int r = 1; r < h; r++) {
    printB(bLen, nSpaceLen, sLen, nLevel, nQ);
    bLen = bLen / 2 - 1;
    nSpaceLen = nSpaceLen / 2 + 1;
    sLen = bLen + 2;
    printN(bLen, nSpaceLen, sLen, nLevel, nQ);

    for (int i = 0; i < nLevel; i++) {
      tnode<xtype> *q = nQ.front();
      nQ.pop_front();

      if (q != NULL) {
        nQ.push_back(q->left);
        nQ.push_back(q->right);
      } else {
        nQ.push_back(NULL);
        nQ.push_back(NULL);
      }
    }
    nLevel *= 2;
  }
  printB(bLen, nSpaceLen, sLen, nLevel, nQ);
  printL(nLevel, nQ);
}

template <class xtype> void AVLtree<xtype>::print() {
  cout << "\n\n\n   ";
  printAVL(root);
}

int main() {
  AVLtree<int> T;
  int i;
  T.insert(14);
  T.insert(20);
  T.insert(10);
  T.insert(50);
  T.insert(5);
  T.insert(30);
  T.insert(60);
  T.insert(13);
  T.insert(12);
  T.insert(2);
  T.insert(4);
  T.insert(11);
  T.insert(22);
  T.insert(40);
  T.insert(65);
  T.insert(55);
  T.Delete(20);
  T.print();
  T.Delete(11);
  T.print();
  T.Delete(12);
  T.print();
  T.Delete(2);
  T.print();
  T.Delete(13);
  T.print();
  T.Delete(60);
  T.print();
  T.Descendants(14);
  cin >> i;
  return 0;
}
