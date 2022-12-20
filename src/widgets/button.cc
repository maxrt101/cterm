#include <cterm/widgets/button.h>
#include <cterm/printer.h>

void cterm::widget::Button::draw(Printer& printer) {
  if (selected) {
    printer.setBgColor(selectBgColor);
    printer.setFgColor(selectFgColor);
  } else {
    printer.setBgColor(bgColor);
    printer.setFgColor(fgColor);
  }
  printer.moveCursor(xoff, yoff);
  printer.put(label);
}

void cterm::widget::Button::click() {
  if (onClick) {
    onClick();
  }
}

cterm::widget::Button* cterm::widget::Button::create(ButtonArgs args) {
  Button* buttonWidget = new Button;
  buttonWidget->tag = args.tag;
  buttonWidget->xoff = args.xoff;
  buttonWidget->yoff = args.yoff;
  buttonWidget->xabs = args.xabs;
  buttonWidget->yabs = args.yabs;
  buttonWidget->label = args.label;
  buttonWidget->selectable = true;
  buttonWidget->bgColor = args.bgColor;
  buttonWidget->fgColor = args.fgColor;
  buttonWidget->selectBgColor = args.selectBgColor;
  buttonWidget->selectFgColor = args.selectFgColor;
  buttonWidget->onClick = args.onClick;
  return buttonWidget;
}
