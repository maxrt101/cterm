#ifndef _CTERM_WIDGETS_TEXT_H_
#define _CTERM_WIDGETS_TEXT_H_ 1

#include <cterm/widget.h>
#include <cterm/colors.h>
#include <cterm/value.h>
#include <vector>
#include <string>

namespace cterm {
namespace widget {

struct Text : public Widget {
  struct TextArgs {
    std::string tag = "";
    int xoff = 0;
    int yoff = 0;
    int xabs = 0;
    int yabs = 0;
    int bgColor = -1;
    int fgColor = -1;
    IntegerValue maxWidth = -1;
    IntegerValue maxHeight = -1;
    std::string text = "";
    Align align = Widget::LEFT;
    Align textAlign = LEFT;
  };

  int bgColor = -1;
  int fgColor = -1;
  IntegerValue maxWidth = -1;
  IntegerValue maxHeight = -1;
  std::string text = "";
  Align textAlign = Align::LEFT;

  IntegerValue getWidth() const override;
  IntegerValue getHeight() const override;
  
  std::vector<std::string> getLines() const;
  std::vector<int> getLineLengths() const;

  void draw(Printer& printer) override;

  static Text* create(TextArgs args);
};

} /* namespace widget */
} /* namespace cterm */

#endif /* _CTERM_WIDGETS_TEXT_H_ */