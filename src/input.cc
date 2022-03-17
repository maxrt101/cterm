#include <cterm/input.h>
#include <cstdio>
#include <errno.h>
#include <fcntl.h>
#include <unistd.h>
#include <termios.h>

static termios g_settings;

void cterm::io::saveTerminalSettings() {
  tcgetattr(STDIN_FILENO, &g_settings);
}

void cterm::io::restoreTerminalSettings() {
  tcsetattr(STDIN_FILENO, TCSANOW, &g_settings);
}

void cterm::io::setOneCharRead(bool flag) {
  termios settings;
  tcgetattr(STDIN_FILENO, &settings);

  if (flag) {
    settings.c_lflag &= ~ICANON;
  } else {
    settings.c_lflag |= ICANON;
  }
  tcsetattr(STDIN_FILENO, TCSANOW, &settings);
}

void cterm::io::setEcho(bool flag) {
  termios settings;
  tcgetattr(STDIN_FILENO, &settings);

  if (flag) {
    settings.c_lflag |= ECHO;
  } else {
    settings.c_lflag &= ~ECHO;
  }
  tcsetattr(STDIN_FILENO, TCSANOW, &settings);
}

void cterm::io::showCursor(bool flag) {
  if (flag) {
    fputs("\e[?25h", stdout);
  } else {
    fputs("\e[?25l", stdout);
  }
}

int cterm::io::getChar() {
  int ch = 0;
  ch = getchar();
  if (ch == ESC) {
    ch = getchar();
    if (ch == '[') {
      ch = getchar();
      switch (ch) {
        case 'A': return UP_ARROW;
        case 'B': return DOWN_ARROW;
        case 'C': return RIGHT_ARROW;
        case 'D': return LEFT_ARROW;
        default:  return ch;
      }
    }
  }
  return ch;
}
