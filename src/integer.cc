#include <cterm/integer.h>

cterm::Integer::Integer(int value) : m_value(value), m_type(IMMEDIATE) {}

cterm::Integer::Integer(int value, IntegerType type) : m_value(value), m_type(type) {}

cterm::Integer& cterm::Integer::operator=(int val) {
  m_value = val;
  return *this;
}

cterm::Integer::operator int() {
  return m_value;
}

cterm::Integer& cterm::Integer::operator++() {
  ++m_value;
  return *this;
}

cterm::Integer& cterm::Integer::operator--() {
  --m_value;
  return *this;
}

cterm::Integer cterm::Integer::operator++(int) {
  Integer val = *this;
  ++m_value;
  return val;
}

cterm::Integer cterm::Integer::operator--(int) {
  Integer val = *this;
  --m_value;
  return val;
}

cterm::IntegerType cterm::Integer::getType() const {
  return m_type;
}

int cterm::Integer::get() const {
  return m_value;
}

cterm::Integer cterm::percent(int val) {
  return Integer(val, PERCENT);
}
