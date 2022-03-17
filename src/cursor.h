#ifndef _CTERM_CURSOR_H_
#define _CTERM_CURSOR_H_ 1

namespace cterm {

// getCursor
void moveCursor(int x, int y);
void moveCursorUp(int n);
void moveCursorDown(int n);
void moveCursorLeft(int n);
void moveCursorRight(int n);

} /* namespace cterm */

#endif /* _CTERM_CURSOR_H_ */