/**
        Purpose: Use Large Integer Class to peform Arithmetic and Comparison
        using linked list

        @author Eddie Ozuna

*/
#include "largeInt.hpp"
#include <iostream>
using namespace std;

void Arithmetic() {
  int choice;
  LargeInt num, numTwo;
  cout << endl << "Choose the type of Arithmetic: " << endl;
  cout << "1. Add " << endl;
  cout << "2. subtract" << endl;
  cout << "3. Multiply " << endl;
  cout << "4. Division" << endl;
  cout << "5. Module" << endl;
  cin >> choice;
  cout << "Enter Integer 1: ";
  cin >> num;
  cout << "Enter Integer 2: ";
  cin >> numTwo;
  cout << "Result: ";
  switch (choice) {
  case 1:
    cout << num + numTwo;
    break;
  case 2:
    cout << num - numTwo;
    break;
  case 3:
    cout << num * numTwo;
    break;
  case 4:
    cout << num / numTwo;
    break;
  case 5:
    cout << num % numTwo;
    break;
  }
}
void Comparison() {
  int choice;
  LargeInt num, numTwo;
  cout << endl << "Choose the type of comparison: " << endl;
  cout << "1. >" << endl;
  cout << "2. <" << endl;
  cout << "3. >=" << endl;
  cout << "4. <=" << endl;
  cout << "5. ==" << endl;
  cin >> choice;
  cout << "Enter Integer 1: ";
  cin >> num;
  cout << "Enter Integer 2: ";
  cin >> numTwo;
  cout << "Result: ";
  switch (choice) {
  case 1:
    if (num > numTwo) {
      cout << "Greater" << endl;
    } else {
      cout << "Less" << endl;
    }
    break;
  case 2:
    if (num < numTwo) {
      cout << "Less" << endl;
    } else {
      cout << "Greater" << endl;
    }
    break;
  case 3:
    if (num >= numTwo) {
      cout << "Greater or Equal" << endl;
    } else {
      cout << "Less" << endl;
    }
    break;
  case 4:
    if (num <= numTwo) {
      cout << "Less or Equal" << endl;
    } else {
      cout << "Greater" << endl;
    }
    break;
  case 5:
    if (num == numTwo) {
      cout << "Equal" << endl;
    } else {
      cout << "Not Equal" << endl;
    }
    break;
  }
}
int main() {

  try {
    int choice;
    do {
      cout
          << endl
          << "- - - - - - - - L A R G E   I N T E G ER   P R O J E C T - - - - "
             "- - - - "
          << endl
          << endl;
      cout << "Choose: " << endl;
      cout << "1. Arithmetic " << endl;
      cout << "2. Comparison" << endl;
      cout << "3. Exit" << endl;
      cin >> choice;
      switch (choice) {
      case 1:
        Arithmetic();
        break;
      case 2:
        Comparison();
        break;
      }
    } while (choice != 3);
  } catch (std::exception const &exc) {
    std::cerr << "Exception caught " << exc.what() << "\n";
  } catch (...) {
    std::cerr << "Unknown exception caught\n";
  };
  return 0;
}
