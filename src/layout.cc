#include <cterm/layout.h>

void cterm::Layout::draw(cterm::Printer& printer) {
  if (type == LayoutType::VERTICAL) {
    int offset = yoff;
    for (auto& widget : widgets) {
      if (widget->align == Widget::LEFT) {
        printer.begin(
          widget->xabs ? widget->xabs : xoff,
          widget->yabs ? widget->yabs : offset,
          printer.getWidth() - 2 - xoff * 2,
          printer.getHeight() - 2 - yoff * 2
        );
      } else if (widget->align == Widget::CENTER) {
        printer.begin(
          (printer.getWidth() - widget->getWidth()) / 2,
          widget->yabs ? widget->yabs : offset,
          printer.getWidth() - 2 - xoff * 2,
          printer.getHeight() - 2 - yoff * 2
        );
      } else if (widget->align == Widget::RIGHT) {
        printer.begin(
          xoff * 2 + printer.getWidth() - widget->getWidth(),
          widget->yabs ? widget->yabs : offset,
          printer.getWidth() - 2 - xoff * 2,
          printer.getHeight() - 2 - yoff * 2
        );
      }
      widget->draw(printer);
      printer.end();
      if (widget->yoff == 0) {
        offset += widget->getHeight() + yinterval;
      }
    }
  } else if (type == LayoutType::HORIZONTAL) { // TODO: Check
    int offset = xoff;
    for (auto& widget : widgets) {
      printer.begin(
        offset, yoff,
        printer.getWidth() - 2 - xoff * 2,
        printer.getHeight() - 2 - yoff * 2
      );
      widget->draw(printer);
      printer.end();
      offset += widget->getWidth() + xinterval;
    }
  }
}

cterm::Layout* cterm::Layout::vertical(LayoutArgs args) {
  Layout* layout = new Layout;
  layout->type = LayoutType::VERTICAL;
  layout->xoff = args.xoff;
  layout->yoff = args.yoff;
  layout->xinterval = args.xinterval;
  layout->yinterval = args.yinterval;
  layout->widgets = args.widgets;
  return layout;
}

cterm::Layout* cterm::Layout::horizontal(LayoutArgs args) {
  Layout* layout = new Layout;
  layout->type = LayoutType::HORIZONTAL;
  layout->xoff = args.xoff;
  layout->yoff = args.yoff;
  layout->xinterval = args.xinterval;
  layout->yinterval = args.yinterval;
  layout->widgets = args.widgets;
  return layout;
}
