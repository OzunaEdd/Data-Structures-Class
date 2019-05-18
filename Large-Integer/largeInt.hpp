/**

        @author Eddie Ozuna

*/

#ifndef LARGEINT_H
#define LARGEINT_H
#include "doubleLink.hpp"
#include <iostream>
#include <string>

template <class x> class DoubleLink;
template <class x> class Iterator;
class LargeInt;

std::ostream &operator<<(std::ostream &out, LargeInt obj);
std::istream &operator>>(std::istream &in, LargeInt &obj);
class LargeInt {
private:
  bool sign;
  DoubleLink<int> digits;
  void setZero();

public:
  LargeInt();
  LargeInt(std::string);
  friend std::istream &operator>>(std::istream &in, LargeInt &obj);
  friend std::ostream &operator<<(std::ostream &out, LargeInt obj);
  LargeInt operator+(LargeInt &);
  LargeInt operator=(LargeInt);
  LargeInt operator-(LargeInt &);
  LargeInt operator*(LargeInt &);
  LargeInt operator/(LargeInt &);
  LargeInt operator%(LargeInt &);
  bool operator<(LargeInt &);
  bool operator<=(LargeInt &);
  bool operator>=(LargeInt &);
  bool operator>(LargeInt &);
  bool operator==(LargeInt &);
  bool getSign();
  void setSign(bool);
  void print();
};

#endif
