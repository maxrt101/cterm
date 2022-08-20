#ifndef _CTERM_PRINTER_H_
#define _CTERM_PRINTER_H_ 1

#include <vector>
#include <string>

namespace cterm {

struct PrinterState {
  int xoff = 0;
  int yoff = 0;
  int width = 0;
  int height = 0;
  int bgColor = 0;
  int fgColor = 0;
};

class Printer {
 private:
  int m_width = 0;
  int m_height = 0;
  int m_xoffAbsolute = 0;
  int m_yoffAbsolute = 0;
  std::vector<PrinterState> m_states;

 public:
  Printer(int width, int height);

  int getXOffset() const;
  int getYOffset() const;
  int getWidth() const;
  int getHeight() const;
  int getBgColor() const;
  int getFgColor() const;
  int getRootWidth() const;
  int getRootHeight() const;

  void begin(int xoff, int yoff, int width, int height);
  void end();

  void setBgColor(int color);
  void setFgColor(int color);
  void moveCursor(int x, int y);

  void put(char c);
  void put(const char* s);
  void put(const std::string& s);
  void putf(const char* fmt, ...);
};

} /* namespace cterm */

#endif /* _CTERM_PRINTER_H_ */