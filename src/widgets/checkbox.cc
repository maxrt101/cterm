#include <cterm/widgets/checkbox.h>
#include <cterm/printer.h>

void cterm::widget::Checkbox::draw(Printer& printer) {
  if (selected) {
    printer.setBgColor(selectBgColor);
    printer.setFgColor(selectFgColor);
  } else {
    printer.setBgColor(bgColor);
    printer.setFgColor(fgColor);
  }
  printer.moveCursor(xoff, yoff);
  printer.put((checked ? checked_prefix : unchecked_prefix) + " " + label);
}

void cterm::widget::Checkbox::click() {
  checked = !checked;
}

cterm::widget::Checkbox* cterm::widget::Checkbox::create(CheckboxArgs args) {
  Checkbox* checkboxWidget = new Checkbox;
  checkboxWidget->tag = args.tag;
  checkboxWidget->xoff = args.xoff;
  checkboxWidget->yoff = args.yoff;
  checkboxWidget->xabs = args.xabs;
  checkboxWidget->yabs = args.yabs;
  checkboxWidget->label = args.label;
  checkboxWidget->unchecked_prefix = args.unchecked_prefix;
  checkboxWidget->checked_prefix = args.checked_prefix;
  checkboxWidget->checked = args.checked;
  checkboxWidget->selectable = true;
  checkboxWidget->bgColor = args.bgColor;
  checkboxWidget->fgColor = args.fgColor;
  checkboxWidget->selectBgColor = args.selectBgColor;
  checkboxWidget->selectFgColor = args.selectFgColor;
  return checkboxWidget;
}

