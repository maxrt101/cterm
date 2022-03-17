#ifndef _CTERM_ELEMENT_H_
#define _CTERM_ELEMENT_H_ 1

#include <functional>

namespace cterm {

enum IntegerType {
  IMMEDIATE,
  PERCENT
};

class Integer {
 private:
  IntegerType m_type;
  int m_value;

 public:
  Integer(int value);
  Integer(int value, IntegerType type);

  Integer& operator=(int val);
  operator int();
  Integer& operator++();
  Integer& operator--();
  Integer operator++(int);
  Integer operator--(int);

  IntegerType getType() const;
  int get() const;
};

Integer percent(int val);

} /* namespace cterm */

#endif /* _CTERM_ELEMENT_H_ */