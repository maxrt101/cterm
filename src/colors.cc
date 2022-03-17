#include <cterm/colors.h>
#include <cstdio>

static int g_currentBgColor, g_currentFgColor;

void cterm::setFgColor(int color) {
  g_currentFgColor = color;
  printf("\033[38;5;%dm", color);
}

void cterm::setBgColor(int color) {
  g_currentBgColor = color;
  printf("\033[48;5;%dm", color);
}

int cterm::getFgColor() {
  return g_currentFgColor;
}

int cterm::getBgColor() {
  return g_currentBgColor;
}

int cterm::invertColor(int color) {
  switch (color) {
    case WHITE: return BLACK;
  }
  return BLACK;
}
