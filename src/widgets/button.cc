#include <cterm/widgets/button.h>
#include <cterm/printer.h>

void cterm::widget::Button::draw(Printer& printer) {
  printer.moveCursor(xoff, yoff);
  printer.put(label);
}
