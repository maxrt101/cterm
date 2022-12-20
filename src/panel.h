#ifndef _CTERM_PANEL_H_
#define _CTERM_PANEL_H_ 1

#include <cterm/printer.h>
#include <cterm/colors.h>
#include <cterm/value.h>
#include <cterm/widget.h>
#include <cterm/layout.h>
#include <functional>
#include <cstddef>
#include <vector>
#include <string>

namespace cterm {

class Console;

struct Panel {
  // using InputHandler = std::function<bool(char)>;

  std::string tag;
  std::string title;

  int rows = 0;
  int cols = 0;
  IntegerValue xoff = 0;
  IntegerValue yoff = 0;
  std::vector<IntegerValue> vLines;

  int fgColor = BLACK;
  int bgColor = GREY;
  int titleColor = BLACK;
  int borderColor = BLACK;

  bool drawBorder = true;
  bool drawShadow = true;
  bool drawTitle = true;
  bool drawTitleEdges = true;
  bool drawBlackWhiteBorder = true;

  bool active = true;

  // InputHandler inputHandler = nullptr;
  int selectedIndex = 0;

  Layout* layout;
  size_t selectedWidget;

 public:
  void draw(Printer& printer);
  // bool handleInput(char c);

  void cycleSelection(bool backward = false);
  void toggleSelection();

  int getRows() const;
  int getCols() const;
  int getXOffset() const;
  int getYOffset() const;

  Widget* getWidgetByTag(const std::string tag) const;

  static Panel fromConsole(const Console& console);
};

} /* namespace cterm */

#endif /* _CTERM_PANEL_H_ */