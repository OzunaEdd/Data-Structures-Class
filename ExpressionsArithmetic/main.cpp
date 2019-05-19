#include "arithmetic.hpp"
#include <iostream>
#include <string>
using namespace std;

int main() {
  Arithmetic expression;
  do {
    cout << "Enter a expression or q to quit: ";
    cin >> expression;
    if (expression != "q")
      cout << "Result: " << expression << endl;
  } while (expression != "q");
  return 0;
}
