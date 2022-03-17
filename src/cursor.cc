#include <cterm/cursor.h>
#include <cstdio>

void cterm::moveCursor(int x, int y) {
  printf("\033[%d;%df", y, x);
}

void cterm::moveCursorUp(int n) {
  printf("\033[%iA", n);
}

void cterm::moveCursorDown(int n) {
  printf("\033[%iB", n);
}

void cterm::moveCursorLeft(int n) {
  printf("\033[%iC", n);
}

void cterm::moveCursorRight(int n) {
  printf("\033[%iD", n);
}
