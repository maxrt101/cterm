#ifndef _CTERM_WIDGETS_BUTTON_H_
#define _CTERM_WIDGETS_BUTTON_H_ 1

#include <cterm/widget.h>
#include <functional>
#include <string>

namespace cterm {
namespace widget {

struct Button : public Widget {
  using CallbackT = std::function<void()>;

  std::string label = "Button";
  CallbackT onClick = nullptr;

  void draw(Printer& printer) override;

  static Button* create(const std::string& label, CallbackT clickHandler);
};

} /* namespace widget */
} /* namespace cterm */

#endif /* _CTERM_WIDGETS_BUTTON_H_ */