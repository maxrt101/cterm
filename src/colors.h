#ifndef _CTERM_COLORS_H_
#define _CTERM_COLORS_H_ 1

namespace cterm {

constexpr int BLACK = 0;
constexpr int RED = 1;
constexpr int GREEN = 2;
constexpr int YELLOW = 3;
constexpr int BLUE = 4;
constexpr int PURPLE = 5;
constexpr int CYAN = 6;
constexpr int GREY = 7;

constexpr int DARK_GREY = 8;
constexpr int BRIGHT_RED = 9;
constexpr int BRIGHT_GREEN = 10;
constexpr int BRIGHT_YELLOW = 11;
constexpr int BRIGHT_BLUE = 12;
constexpr int BRIGHT_PURPLE = 13;
constexpr int BRIGHT_CYAN = 14;
constexpr int WHITE = 15;

void setFgColor(int color);
void setBgColor(int color);

int getFgColor();
int getBgColor();

int invertColor(int color);

} /* namespace cterm */

#endif /* _CTERM_COLORS_H_ */