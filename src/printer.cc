#include <cterm/printer.h>
#include <cterm/cursor.h>
#include <cterm/colors.h>

cterm::Printer::Printer(int xoff, int yoff, int parentRows, int parentCols)
  : m_xoff(xoff), m_yoff(yoff), m_parentRows(parentRows), m_parentCols(parentCols) {}

int cterm::Printer::getParentRows() const {
  return m_parentRows;
}

int cterm::Printer::getParentCols() const {
  return m_parentCols;
}

void cterm::Printer::begin() {
  m_isOperating = true;
  m_lastBgColor = getBgColor();
  m_lastFgColor = getFgColor();
}

void cterm::Printer::end() {
  m_isOperating = false;
  cterm::setBgColor(m_lastBgColor);
  cterm::setFgColor(m_lastFgColor);
}

void cterm::Printer::setOffset(int x, int y) {
  m_xoff = x;
  m_yoff = y;
}

void cterm::Printer::setParentDimensions(int parentRows, int parentCols) {
  m_parentRows = parentRows;
  m_parentCols = parentCols;
}

void cterm::Printer::setBgColor(int color) {
  m_bgColor = color;
  cterm::setBgColor(color);
}

void cterm::Printer::setFgColor(int color) {
  m_fgColor = color;
  cterm::setFgColor(color);
}

void cterm::Printer::moveCursor(int x, int y) {
  cterm::moveCursor(m_xoff + x, m_yoff + y);
}

void cterm::Printer::put(char c) {
  printf("%c", c);
}

void cterm::Printer::put(const char* s) {
  printf("%s", s);
}

void cterm::Printer::put(const std::string& s) {
  printf("%s", s.c_str());
}

void cterm::Printer::putf(const char* fmt, ...) {
  va_list args;
  va_start(args, fmt);
  vprintf(fmt, args);
  va_end(args);
}
