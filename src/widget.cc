#include <cterm/widget.h>
#include <cterm/printer.h>

cterm::IntegerValue cterm::Widget::getWidth() const {
  return 0;
}

cterm::IntegerValue cterm::Widget::getHeight() const {
  return 0;
}

void cterm::Widget::draw(Printer& printer) {}

void cterm::Widget::click() {}
