#ifndef _CTERM_INPUT_H_
#define _CTERM_INPUT_H_ 1

namespace cterm {
namespace io {

constexpr int ESC = 27;
constexpr int LEFT_ARROW = 512;
constexpr int UP_ARROW = 513;
constexpr int RIGHT_ARROW = 514;
constexpr int DOWN_ARROW = 515;

void saveTerminalSettings();
void restoreTerminalSettings();

void setOneCharRead(bool flag);
void setEcho(bool flag);
void showCursor(bool flag);
int getChar();

} /* namespace io */
} /* namespace cterm */

#endif /* _CTERM_INPUT_H_ */