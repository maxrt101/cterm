#include <cterm/console.h>
#include <cterm/cursor.h>
#include <sys/ioctl.h>
#include <unistd.h>
#include <cstdio>

void cterm::Console::getDimensions(int& rows, int& cols) {
  winsize w;
  ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);

  rows = w.ws_row;
  cols = w.ws_col;
}

cterm::Console::Console() {
  updateDimensions();
}

cterm::Console::~Console() {}

int cterm::Console::getRows() const {
  return m_rows;
}

int cterm::Console::getCols() const {
  return m_cols;
}

cterm::Console& cterm::Console::setFgColor(int fgColor) {
  m_fgColor = fgColor;
  return *this;
}

cterm::Console& cterm::Console::setBgColor(int bgColor) {
  m_bgColor = bgColor;
  return *this;
}

void cterm::Console::updateDimensions() {
  getDimensions(m_rows, m_cols);
}

void cterm::Console::clear() {
  cterm::setFgColor(m_fgColor);
  cterm::setBgColor(m_bgColor);
  printf("\033[2J");
}

void cterm::Console::draw() {
  clear();
  Printer printer(0, 0, m_rows, m_cols);
  for (auto& panel : m_panels) {
    if (panel.active) {
      printer.setOffset(panel.getXOffset(), panel.getYOffset());
      printer.begin();
      printer.moveCursor(0, 0);
      panel.draw(printer);
      printer.end();
    }
  }
}

void cterm::Console::addPanel(const Panel& panel) {
  m_panels.push_back(panel);
}

cterm::Panel& cterm::Console::getPanel(int index) {
  return m_panels[index];
}

cterm::Panel& cterm::Console::getPanelByTag(const std::string& tag) {
  for (auto& panel : m_panels) {
    if (panel.tag == tag) {
      return panel;
    }
  }
  throw "No such panel";
}
