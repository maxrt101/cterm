#ifndef _CTERM_WIDGETS_CHECKBOX_H_
#define _CTERM_WIDGETS_CHECKBOX_H_ 1

#include <cterm/widget.h>
#include <functional>
#include <string>

namespace cterm {
namespace widget {

struct Checkbox : public Widget {
  struct CheckboxArgs {
    std::string tag = "";
    int xoff = 0;
    int yoff = 0;
    int xabs = 0;
    int yabs = 0;
    int bgColor = -1;
    int fgColor = -1;
    int selectBgColor = -1;
    int selectFgColor = -1;
    std::string label = "";
    std::string unchecked_prefix = "[ ]";
    std::string checked_prefix = "[*]";
    bool checked = false;
  };

  int bgColor = -1;
  int fgColor = -1;
  int selectBgColor = -1;
  int selectFgColor = -1;
  std::string unchecked_prefix = "[ ]";
  std::string checked_prefix = "[*]";
  std::string label = "";
  bool checked = false;

  void draw(Printer& printer) override;
  void click() override;

  static Checkbox* create(CheckboxArgs args);
};

} /* namespace widget */
} /* namespace cterm */

#endif /* _CTERM_WIDGETS_CHECKBOX_H_ */