#ifndef _CTERM_PRINTER_H_
#define _CTERM_PRINTER_H_ 1

#include <string>

namespace cterm {

class Printer {
 private:
  int m_xoff = 0;
  int m_yoff = 0;
  int m_parentRows = 0;
  int m_parentCols = 0;
  int m_bgColor = 0;
  int m_fgColor = 0;
  int m_lastBgColor = 0;
  int m_lastFgColor = 0;
  int m_isOperating = false;

 public:
  Printer(int xoff, int yoff, int parentRows, int parentCols);

  int getParentRows() const;
  int getParentCols() const;

  void begin();
  void end();

  void setOffset(int x, int y);
  void setParentDimensions(int parentRows, int parentCols);
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