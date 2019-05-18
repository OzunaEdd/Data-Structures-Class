#include "doubleLink.cpp"
#include "largeInt.hpp"
#include <iostream>
#include <string>
using namespace std;

LargeInt::LargeInt(string number) {
  sign = (number[0] == '-') ? true : false;
  for (int i = (sign ? 1 : 0); i < number.length(); i++) {
    digits.insertBack(number[i] - '0');
  }
}
LargeInt::LargeInt() { sign = false; }

std::ostream &operator<<(std::ostream &out, LargeInt obj) {
  Iterator<int> i;
  if (obj.sign) {
    cout << '-';
  }
  for (i = obj.digits.begin(); (i != obj.digits.end()); i++) {

    out << *i;
  }
  return out;
}
bool LargeInt::getSign() { return sign; }
void LargeInt::setSign(bool s) { sign = s; }

std::istream &operator>>(std::istream &in, LargeInt &obj) {
  std::string number;
  in >> number;
  obj.sign = (number[0] == '-') ? true : false;
  for (int i = (obj.sign ? 1 : 0); i < number.length(); i++) {

    obj.digits.insertBack(number[i] - '0');
  }
  return in;
}

LargeInt LargeInt::operator+(LargeInt &obj) {
  Iterator<int> i = digits.lastt();
  Iterator<int> j = obj.digits.lastt();
  LargeInt result;
  int carry = 0;
  if (sign && !obj.sign) {
    sign = false;
    result = *this - obj;
    result.sign = (*this > obj) ? true : false;
    sign = true;
  } else if (!sign && obj.sign) {
    obj.sign = false;
    result = *this - obj;
    obj.sign = true;
  } else {
    while (i != digits.end() || j != obj.digits.end()) {
      if (j == obj.digits.end()) {
        result.digits.insertFront((*i + carry) % 10);
        carry = (*i + carry) / 10;
        i--;
      } else if (i == digits.end()) {
        result.digits.insertFront((*j + carry) % 10);
        carry = (*j + carry) / 10;
        j--;
      } else {
        result.digits.insertFront((*i + *j + carry) % 10);
        carry = (*i + *j + carry) / 10;
        j--;
        i--;
      }
    }
  }
  if (carry != 0) {
    result.digits.insertFront(carry);
  }
  result.sign = (sign && obj.sign) ? true : false;
  if (result.digits.isZero()) {
    result.digits.destroyList();
    result.digits.insertBack(0);
    result.sign = false;
  }
  return result;
}

LargeInt LargeInt::operator=(LargeInt obj) {
  Iterator<int> i = obj.digits.begin();
  digits.destroyList();
  for (; i != obj.digits.end(); i++) {
    digits.insertBack(*i);
  }
  sign = obj.sign;
  return *this;
}
LargeInt LargeInt::operator-(LargeInt &obj) {
  Iterator<int> i = digits.lastt();
  Iterator<int> j = obj.digits.lastt();
  LargeInt result;
  int borrow = 0;
  if (!sign && obj.sign) {
    obj.sign = false;
    result = *this + obj;
    obj.sign = true;
  } else if (sign && !obj.sign) {
    sign = false;
    result = *this + obj;
    sign = true;
    result.sign = true;
  } else if (sign && obj.sign) {
    sign = false;
    obj.sign = false;
    result = *this - obj;
    sign = true;
    obj.sign = true;
    result.sign = true;
  } else {
    if (obj <= *this) {
      i = digits.lastt();
      j = obj.digits.lastt();
    } else {
      j = digits.lastt();
      i = obj.digits.lastt();
      result.sign = true;
    }
    while (i != digits.end() || j != obj.digits.end()) {
      if (j == obj.digits.end()) {
        result.digits.insertFront((*i + 10 - borrow) % 10);
        borrow = ((*i == 0) && borrow) ? 1 : 0;
        i--;
      } else if (i == digits.end()) {
        result.digits.insertFront((*j + 10 - borrow) % 10);
        borrow = (*j == 0 && borrow) ? 1 : 0;
        j--;
      } else {
        if (*i < *j) {
          result.digits.insertFront((*i + 10) - borrow - *j);
          borrow = 1;
        } else {
          result.digits.insertFront(((*i + 10 - borrow) % 10) - *j);
          borrow = 0;
        }
        j--;
        i--;
      }
    }
  }
  if (result.digits.isZero()) {
    result.digits.destroyList();
    result.digits.insertBack(0);
    result.sign = false;
  }
  return result;
}
LargeInt LargeInt::operator*(LargeInt &obj) {
  Iterator<int> i = digits.lastt();
  Iterator<int> j = obj.digits.lastt();
  int size = obj.digits.getLength();
  LargeInt *add = new LargeInt[size];
  LargeInt result;
  int remainder = 0;
  int l = 0;
  if ((sign && !obj.sign) || (!sign && obj.sign)) {
    result.sign = true;
  }
  for (int p = 0; j != obj.digits.end(); j--, p++) {
    if (p > 0) {
      l = p;
      while (l > 0) {
        add[p].digits.insertBack(0);
        l--;
      }
    }
    while (i != digits.end()) {
      add[p].digits.insertFront(((*i * *j) + remainder) % 10);
      remainder = ((*i * *j) + remainder) / 10;
      i--;
    }
    i = digits.lastt();
    if (remainder > 0) {
      add[p].digits.insertFront(remainder);
    }
    remainder = 0;
  }
  for (int a = 0; a < size; a++) {
    result = result + add[a];
  }
  delete[] add;
  return result;
}
LargeInt LargeInt::operator/(LargeInt &obj) {
  LargeInt remainder = *this;
  LargeInt quotient;
  LargeInt one;
  one.digits.insertBack(1);
  quotient.digits.insertBack(0);
  remainder.sign = false;
  obj.sign = false;
  if (*this < obj) {
    quotient.digits.insertBack(0);
  } else if (remainder == obj) {
    quotient.digits.insertBack(1);
  } else {
    while (*this >= obj) {
      *this = *this - obj;
      quotient = quotient + one;
    }
  }
  cout << *this << endl;
  *this = remainder;
  return quotient;
}
bool LargeInt::operator<=(LargeInt &obj) {
  bool less_equal = false;
  Iterator<int> i = digits.begin();
  Iterator<int> j = obj.digits.begin();
  if ((digits.getLength() < obj.digits.getLength()) &&
      ((!sign && !obj.sign) || (sign && !obj.sign))) {
    less_equal = true;
  }
  if ((digits.getLength() > obj.digits.getLength()) &&
      ((sign && obj.sign) || (sign && !obj.sign))) {
    less_equal = true;
  }
  if (digits.getLength() == obj.digits.getLength()) {
    if (sign && !obj.sign) {
      less_equal = true;
    } else if ((!sign && !obj.sign) || (sign && obj.sign)) {
      while (i != digits.end() && !less_equal) {
        if (*i == *j) {
          i++;
          j++;
        } else {
          if (*i < *j && (!sign && !obj.sign)) {
            less_equal = true;
          }
          if (*i > *j && (sign && obj.sign)) {
            less_equal = true;
          }
          break;
        }
      }
      if (i == digits.end()) {
        less_equal = true;
      }
    }
  }
  return less_equal;
}
LargeInt LargeInt::operator%(LargeInt &obj) {
  Iterator<int> i = digits.begin();
  Iterator<int> j;
  LargeInt sub;
  LargeInt dividend;
  LargeInt quotient;
  LargeInt result;
  int number = 0;
  dividend.digits.insertBack(*i);
  quotient.digits.insertBack(number);
  if (obj.digits.isZero()) {
    cout << "ERROR! Division by zero is not possible!" << endl;
  } else if (*this < obj) {
    result = *this;
  } else {
    while (i != digits.end()) {
      if (obj > dividend) {
        j = dividend.digits.begin();
        result.digits.insertBack(0);
        i++;
        if (i != digits.end()) {
          if (*j != 0) {
            dividend.digits.insertBack(*i);
          }
        }
      } else {
        number = 0;
        quotient.digits.destroyList();
        quotient.digits.insertBack(number);
        while ((obj * quotient) <= dividend) {
          number++;
          quotient.digits.destroyList();
          quotient.digits.insertBack(number);
        }
        quotient.digits.destroyList();
        quotient.digits.insertBack(--number);
        sub = (obj * quotient);
        dividend = dividend - sub;
        j = dividend.digits.begin();
        while (j != dividend.digits.end()) {
          if (*j == 0) {
            dividend.digits.deleteItem(0);
          } else {
            break;
          }
          j++;
        }
        if (j == dividend.digits.end())
          dividend.digits.destroyList();
        result.digits.insertBack(number);

        i++;
        if (i != digits.end())
          dividend.digits.insertBack(*i);
      }
      result = dividend;
      if (result.digits.isZero()) {
        result.digits.destroyList();
        result.digits.insertFront(0);
      }
    }
  }
  return result;
}
bool LargeInt::operator<(LargeInt &obj) {
  bool less = false;
  Iterator<int> i = digits.begin();
  Iterator<int> j = obj.digits.begin();
  if ((digits.getLength() < obj.digits.getLength()) &&
      ((!sign && !obj.sign) || (sign && !obj.sign))) {
    less = true;
  }
  if ((digits.getLength() > obj.digits.getLength()) &&
      ((sign && obj.sign) || (sign && !obj.sign))) {
    less = true;
  }
  if (digits.getLength() == obj.digits.getLength()) {
    if (sign && !obj.sign) {
      less = true;
    } else if ((!sign && !obj.sign) || (sign && obj.sign)) {
      while (i != digits.end() && !less) {
        if (*i == *j) {
          i++;
          j++;
        } else {
          if (*i < *j && (!sign && !obj.sign)) {
            less = true;
          }
          if (*i > *j && (sign && obj.sign)) {
            less = true;
          }
          break;
        }
      }
    }
  }
  return less;
}
bool LargeInt::operator>=(LargeInt &obj) {
  bool greater = false;
  Iterator<int> i = digits.begin();
  Iterator<int> j = obj.digits.begin();
  if ((digits.getLength() > obj.digits.getLength()) &&
      ((!sign && !obj.sign) || (!sign && obj.sign))) {
    greater = true;
  }
  if ((digits.getLength() < obj.digits.getLength()) &&
      ((sign && obj.sign) || (!sign && obj.sign))) {
    greater = true;
  }
  if (digits.getLength() == obj.digits.getLength()) {
    if (!sign && obj.sign) {
      greater = true;
    } else if ((!sign && !obj.sign) || (sign && obj.sign)) {
      while (i != digits.end() && !greater) {
        if (*i == *j) {
          i++;
          j++;
        } else {
          if (*i > *j && (!sign && !obj.sign)) {
            greater = true;
          }
          if (*i < *j && (sign && obj.sign)) {
            greater = true;
          }
          break;
        }
      }
      if (i == digits.end()) {
        greater = true;
      }
    }
  }
  return greater;
}
bool LargeInt::operator>(LargeInt &obj) {
  bool greater_equal = false;
  Iterator<int> i = digits.begin();
  Iterator<int> j = obj.digits.begin();
  if ((digits.getLength() > obj.digits.getLength()) &&
      ((!sign && !obj.sign) || (!sign && obj.sign))) {
    greater_equal = true;
  }
  if ((digits.getLength() < obj.digits.getLength()) &&
      ((sign && obj.sign) || (!sign && obj.sign))) {
    greater_equal = true;
  }
  if (digits.getLength() == obj.digits.getLength()) {
    if (!sign && obj.sign) {
      greater_equal = true;
    } else if ((!sign && !obj.sign) || (sign && obj.sign)) {
      while (i != digits.end() && !greater_equal) {
        if (*i == *j) {
          i++;
          j++;
        } else {
          if (*i > *j && (!sign && !obj.sign)) {
            greater_equal = true;
          }
          if (*i < *j && (sign && obj.sign)) {
            greater_equal = true;
          }
          break;
        }
      }
    }
  }
  return greater_equal;
}
bool LargeInt::operator==(LargeInt &obj) {
  bool equal = false;
  Iterator<int> i = digits.begin();
  Iterator<int> j = obj.digits.begin();
  int thisSize = digits.getLength();
  int objSize = obj.digits.getLength();
  if ((thisSize == objSize) && ((sign && obj.sign) || (!sign && !obj.sign))) {
    while (i != digits.end() && (*i == *j)) {
      i++;
      j++;
    }
    if (i == digits.end()) {
      equal = true;
    }
  }
  return equal;
}
