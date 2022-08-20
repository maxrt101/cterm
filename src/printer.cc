#include <cterm/printer.h>
#include <cterm/cursor.h>
#include <cterm/colors.h>

cterm::Printer::Printer(int width, int height)
  : m_width(width), m_height(height) {}

int cterm::Printer::getXOffset() const {
  return m_states.empty() ? 0 : m_states.back().xoff;
}

int cterm::Printer::getYOffset() const {
  return m_states.empty() ? 0 : m_states.back().yoff;
}

int cterm::Printer::getWidth() const {
  return m_states.empty() ? m_width : m_states.back().width;
}

int cterm::Printer::getHeight() const {
  return m_states.empty() ? m_height : m_states.back().height;
}

int cterm::Printer::getBgColor() const {
  return m_states.empty() ? GREY : m_states.back().bgColor;
}

int cterm::Printer::getFgColor() const {
  return m_states.empty() ? BLACK : m_states.back().fgColor;
}

int cterm::Printer::getRootWidth() const {
  return m_height;
}

int cterm::Printer::getRootHeight() const {
  return m_height;
}

void cterm::Printer::begin(int xoff, int yoff, int width, int height) {
  m_states.push_back({xoff, yoff, width, height, getBgColor(), getFgColor()});
  m_xoffAbsolute += xoff;
  m_yoffAbsolute += yoff;
}

void cterm::Printer::end() {
  setBgColor(m_states.back().bgColor);
  setFgColor(m_states.back().fgColor);
  m_xoffAbsolute -= m_states.back().xoff;
  m_yoffAbsolute -= m_states.back().yoff;
  m_states.pop_back();
}

void cterm::Printer::setBgColor(int color) {
  m_states.back().bgColor = color;
  cterm::setBgColor(color);
}

void cterm::Printer::setFgColor(int color) {
  m_states.back().fgColor = color;
  cterm::setFgColor(color);
}

void cterm::Printer::moveCursor(int x, int y) {
  cterm::moveCursor(m_xoffAbsolute + x, m_yoffAbsolute + y);
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
