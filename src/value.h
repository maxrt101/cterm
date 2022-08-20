#ifndef _CTERM_VALUE_H_
#define _CTERM_VALUE_H_ 1

#include <functional>

namespace cterm {

enum IntegerValueType {
  IMMEDIATE,
  PERCENTAGE
};

class IntegerValue {
 private:
  IntegerValueType m_type;
  int m_value;

 public:
  using ValueHandler = std::function<int(int)>;

  IntegerValue(int value);
  IntegerValue(int value, IntegerValueType type);

  IntegerValue& operator=(int val);
  operator int();
  IntegerValue& operator++();
  IntegerValue& operator--();
  IntegerValue operator++(int);
  IntegerValue operator--(int);

  IntegerValueType getType() const;
  int& get();
  int get() const;
  int transform(ValueHandler immHandler, ValueHandler perHandler) const;
  int transformIfPercent(ValueHandler handler) const;

  int percent(int p) const;
};

IntegerValue percent(int val);

} /* namespace cterm */

#endif /* _CTERM_VALUE_H_ */