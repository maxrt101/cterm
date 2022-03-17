#ifndef _CTERM_CONSOLE_H_
#define _CTERM_CONSOLE_H_ 1

#include <cterm/panel.h>
#include <cterm/colors.h>
#include <cstddef>
#include <vector>

namespace cterm {

class Console {
 private:
  int m_rows = 0;
  int m_cols = 0;
  int m_fgColor = BLACK;
  int m_bgColor = BRIGHT_BLUE;

  std::vector<Panel> m_panels;

 public:
  Console();
  ~Console();

  int getRows() const;
  int getCols() const;

  Console& setFgColor(int fgColor);
  Console& setBgColor(int bgColor);

  void updateDimensions();
  void clear();
  void draw();

  void addPanel(const Panel& panel);
  Panel& getPanel(int index);
  Panel& getPanelByTag(const std::string& tag);

 public:
  static void getDimensions(int& rows, int& cols);
};

} /* namespace cterm */

#endif /* _CTERM_CONSOLE_H_ */