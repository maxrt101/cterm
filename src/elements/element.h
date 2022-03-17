#ifndef _CTERM_ELEMENT_H_
#define _CTERM_ELEMENT_H_ 1

namespace cterm {

class Panel;

struct Element {
  int xoff;
  int yoff;

  virtual void draw(Panel& panel);
};

} /* namespace cterm */

#endif /* _CTERM_ELEMENT_H_ */