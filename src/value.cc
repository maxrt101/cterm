#include <cterm/value.h>

cterm::IntegerValue::IntegerValue(int value) : m_value(value), m_type(IMMEDIATE) {}

cterm::IntegerValue::IntegerValue(int value, IntegerValueType type) : m_value(value), m_type(type) {}

cterm::IntegerValue& cterm::IntegerValue::operator=(int val) {
  m_value = val;
  return *this;
}

cterm::IntegerValue::operator int() {
  return m_value;
}

cterm::IntegerValue& cterm::IntegerValue::operator++() {
  ++m_value;
  return *this;
}

cterm::IntegerValue& cterm::IntegerValue::operator--() {
  --m_value;
  return *this;
}

cterm::IntegerValue cterm::IntegerValue::operator++(int) {
  IntegerValue val = *this;
  ++m_value;
  return val;
}

cterm::IntegerValue cterm::IntegerValue::operator--(int) {
  IntegerValue val = *this;
  --m_value;
  return val;
}

cterm::IntegerValueType cterm::IntegerValue::getType() const {
  return m_type;
}

int& cterm::IntegerValue::get() {
  return m_value;
}

int cterm::IntegerValue::get() const {
  return m_value;
}

int cterm::IntegerValue::transform(ValueHandler immHandler, ValueHandler perHandler) const {
  if (getType() == PERCENTAGE) {
    return perHandler(m_value);
  } else {
    return immHandler(m_value);
  }
}

int cterm::IntegerValue::transformIfPercent(ValueHandler handler) const {
  if (getType() == PERCENTAGE) {
    return handler(m_value);
  }

  return m_value;
}

int cterm::IntegerValue::percent(int p) const {
  return m_value / 100.0 * p;
}

cterm::IntegerValue cterm::percent(int val) {
  return IntegerValue(val, PERCENTAGE);
}
