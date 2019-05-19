#include "arithmetic.hpp"
#include "stack.cpp"
#include <iomanip>
#include <iostream>
#include <string>
using namespace std;
// Convert a character number to a int type
int Arithmetic::stoi(char exp) { return (exp - '0'); }
double Arithmetic::get() {
  solveExp();
  return result;
}
// Overloading the insertion operator to get user input
istream &operator>>(istream &in, Arithmetic &input) {
  getline(in, input.exp);
  return in;
}
// Overloading the extraction operator output the result
ostream &operator<<(ostream &out, Arithmetic &output) {
  if (output.isValid(output.exp)) {
    output.solveExp();
    out << fixed << setprecision(2) << output.result;
  } else {
    out << "Invalid Expression";
  }
  return out;
}
// Function that walk through the expression and solve it with the help of other
// functions
void Arithmetic::solveExp() {
  Stack<double> operands;
  Stack<char> operators;
  double number, num, numTwo, deci;
  bool negative = false;
  bool oprOn = false;
  bool decimal = false;
  bool digit = false;
  char opr;
  for (int i = 0; i < exp.length(); i++) {
    if (exp[i] == ' ')
      continue;
    else if (i == 0 && exp[i] == '-') {
      if (exp[i + 1] == '-') {
        i++;
      } else {
        negative = true;
        continue;
      }
    } else if (exp[i] == '(') {
      if (digit) {
        digit = false;
        oprOn = true;
        operators.push('*');
      }
      operators.push(exp[i]);
    } else if (exp[i] == ')') {
      solve(operands, operators, exp[i]);
    } else if (exp[i] == '-' && exp[i + 1] == '-') {
      if (oprOn) {
        i++;
      } else {
        solve(operands, operators, '+');
        i++;
      }
    } else if (exp[i] == '-' && oprOn) {
      negative = true;
      continue;
    } else if (isdigit(exp[i])) {
      number = 0;
      deci = 1;
      number = (number * 10) + stoi(exp[i]);
      while (i < exp.length() && (isdigit(exp[i + 1]) || exp[i + 1] == '.')) {
        if (exp[i + 1] == '.') {
          decimal = true;
          i++;
        }
        if (decimal) {
          deci *= 10;
          number = number + (stoi(exp[i + 1]) / deci);
        } else {
          number = (number * 10) + stoi(exp[i + 1]);
        };
        i++;
      }
      if (negative) {
        operands.push(number * -1);
        negative = false;
      } else {
        operands.push(number);
      }
      digit = true;
      oprOn = false;
    } else {
      solve(operands, operators, exp[i]);
      oprOn = true;
      decimal = false;
      digit = false;
    }
  }
  while (!operators.empty()) {
    num = operands.top();
    operands.pop();
    numTwo = operands.top();
    operands.pop();
    opr = operators.top();
    operators.pop();
    operands.push(evaluate(numTwo, opr, num));
  }
  result = operands.top();
  operands.pop();
}
// Function that push the operators and solve it if it see closing parenthese or
// high precedence
void Arithmetic::solve(Stack<double> &operands, Stack<char> &operators,
                       char oprTwo) {
  double num = 0, numTwo = 0;
  char opr;
  if (oprTwo == ')') {
    while (operators.top() != '(' && !operators.empty()) {
      num = operands.top();
      operands.pop();
      numTwo = operands.top();
      operands.pop();
      opr = operators.top();
      operators.pop();
      operands.push(evaluate(numTwo, opr, num));
    }
    operators.pop();
  } else {
    while (!operators.empty() &&
           checkPrecedence(operators.top()) >= checkPrecedence(oprTwo)) {
      num = operands.top();
      operands.pop();
      numTwo = operands.top();
      operands.pop();
      opr = operators.top();
      operators.pop();
      operands.push(evaluate(numTwo, opr, num));
    }
    operators.push(oprTwo);
  }
}
// Function that Return the level of precedence
int Arithmetic::checkPrecedence(char opr) {
  int level = 0;
  switch (opr) {
  case '+':
    level = 1;
    break;
  case '-':
    level = 1;
    break;
  case '*':
    level = 2;
    break;
  case '/':
    level = 2;
    break;
  }
  return level;
}
// Function that perform arithmetic
double Arithmetic::evaluate(double num, char opr, double numTwo) {
  double resultTwo = 0;
  switch (opr) {
  case '+':
    resultTwo = num + numTwo;
    break;
  case '-':
    resultTwo = num - numTwo;
    break;
  case '*':
    resultTwo = num * numTwo;
    break;
  case '/':
    resultTwo = num / numTwo;
    break;
  }
  return resultTwo;
}
// Constructor
Arithmetic::Arithmetic() { result = 0; }
Arithmetic Arithmetic::operator=(string expression) {
  exp = expression;
  return *this;
}
// Function that return true if it an operator else it false
bool Arithmetic::isOperator(char opr) {
  return (opr == '*' || opr == '/' || opr == '+' || opr == '\0');
}
// Function that check if the expression is a valid one
bool Arithmetic::isValid(string exp) {
  bool valid = true;
  int parenthese = 0;
  bool open = false;
  bool close = false;
  if (exp[0] == '+' || isalpha(exp[0])) {
    valid = false;
  }
  for (int i = 0; i < exp.length(); i++) {
    if (exp[i] == ' ') {
      continue;
    } else if (isOperator(exp[i]) && isOperator(exp[i + 1])) {
      valid = false;
    } else if (exp[i] == '-' && exp[i + 1] == '-' && exp[i + 2] == '-') {
      valid = false;
    } else if ((exp[i] == '(' && exp[i + 1] != '-') &&
               (isOperator(exp[i + 1]) || !isdigit(exp[i + 1])) &&
               exp[i + 1] != ' ') {
      valid = false;
    } else if ((exp[i] == ')' && !isOperator(exp[i + 1])) &&
               exp[i + 1] != '-' && exp[i + 1] != ' ') {
      valid = false;
    } else if (exp[i] == '(') {
      parenthese++;
      open = true;
      close = false;
    } else if (exp[i] == '/' && exp[i + 1] == '0') {
      cout << "Cant divide by zero ";
      valid = false;
    } else if (exp[i] == ')') {
      parenthese++;
      close = true;
      open = false;
    }
  }
  if ((open && !close)) {
    valid = false;
  }
  if (parenthese % 2 != 0) {
    valid = false;
  }
  return valid;
}
// Overloading the operator !=
bool Arithmetic::operator!=(string expression) { return (exp != expression); }
