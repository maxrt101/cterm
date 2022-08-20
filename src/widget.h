#ifndef _CTERM_WIDGET_H_
#define _CTERM_WIDGET_H_ 1

#include <cterm/value.h>
#include <string>

namespace cterm {

class Printer;

struct Widget {
  enum Align {
    LEFT, RIGHT, CENTER
  };

  std::string tag = "";
  int xoff = 0;
  int yoff = 0;
  Align align = LEFT;

  virtual IntegerValue getWidth() const;
  virtual IntegerValue getHeight() const;

  virtual void draw(Printer& printer);
};

} /* namespace cterm */

#endif /* _CTERM_WIDGET_H_ */