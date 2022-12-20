#ifndef _CTERM_WIDGETS_BUTTON_H_
#define _CTERM_WIDGETS_BUTTON_H_ 1

#include <cterm/widget.h>
#include <functional>
#include <string>

namespace cterm {
namespace widget {

struct Button : public Widget {
  using CallbackT = std::function<void()>;

  struct ButtonArgs {
    std::string tag = "";
    int xoff = 0;
    int yoff = 0;
    int bgColor = -1;
    int fgColor = -1;
    int selectBgColor = -1;
    int selectFgColor = -1;
    std::string label = "";
    CallbackT onClick = nullptr;
  };

  int bgColor = -1;
  int fgColor = -1;
  int selectBgColor = -1;
  int selectFgColor = -1;
  std::string label = "";
  CallbackT onClick = nullptr;

  void draw(Printer& printer) override;
  void click() override;

  static Button* create(ButtonArgs args);
};

} /* namespace widget */
} /* namespace cterm */

#endif /* _CTERM_WIDGETS_BUTTON_H_ */