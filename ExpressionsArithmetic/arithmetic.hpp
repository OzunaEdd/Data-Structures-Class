#ifndef ARITHMETIC_H
#define ARITHMETIC_H
#include "stack.hpp"
#include <iostream>
#include <string>
using namespace std;

class Arithmetic {
private:
  double result;
  string exp;

public:
  friend istream &operator>>(istream &in, Arithmetic &input);
  friend ostream &operator<<(ostream &out, Arithmetic &output);
  void solveExp();
  double evaluate(double, char, double);
  void solve(Stack<double> &, Stack<char> &, char);
  int checkPrecedence(char);
  Arithmetic operator=(string);
  bool operator!=(string);
  int stoi(char);
  bool isValid(string);
  bool isOperator(char);
  Arithmetic();
  double get();
};

#endif
