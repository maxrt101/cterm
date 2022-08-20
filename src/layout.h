#ifndef _CTERM_LAYOUT_H_
#define _CTERM_LAYOUT_H_ 1

#include <cterm/printer.h>
#include <cterm/widget.h>
#include <vector>

namespace cterm {

enum class LayoutType {
  VERTICAL,
  HORIZONTAL,
};

class Layout {
 private:
  LayoutType type;

 public:
  struct LayoutArgs {
    int xoff = 1;
    int yoff = 1;
    int xinterval = 1;
    int yinterval = 1;
    std::vector<Widget*> widgets;
  };

  int xoff = 1;
  int yoff = 1;
  int xinterval = 1;
  int yinterval = 1;
  std::vector<Widget*> widgets;

  void draw(Printer& printer);

  static Layout* vertical(LayoutArgs args);
  static Layout* horizontal(LayoutArgs args);
};

} /* namespace cterm */

#endif /* _CTERM_LAYOUT_H_ */