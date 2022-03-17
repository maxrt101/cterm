#ifndef _CTERM_PANEL_H_
#define _CTERM_PANEL_H_ 1

#include <cterm/printer.h>
#include <cterm/colors.h>
#include <cterm/integer.h>
#include <cstddef>
#include <string>

namespace cterm {

class Console;

struct Panel {
  std::string tag;
  std::string title;
  int rows = 0;
  int cols = 0;
  Integer xoff = 0;
  Integer yoff = 0;
  int fgColor = BLACK;
  int bgColor = GREY;
  int titleColor = BLACK;

  bool drawBorder = true;
  bool drawShadow = true;
  bool drawTitle = true;
  bool drawTitleEdges = true;

  bool active = true;

  // contents

 public:
  void draw(Printer& printer);

  int getXOffset() const;
  int getYOffset() const;

  static Panel fromConsole(const Console& console);
};

} /* namespace cterm */

#endif /* _CTERM_PANEL_H_ */