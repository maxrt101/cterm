#include <cterm/panel.h>
#include <cterm/console.h>
#include <cterm/cursor.h>
#include <cterm/chars.h>
#include <cstdio>

cterm::Panel cterm::Panel::fromConsole(const Console& console) {
  return Panel {
    .rows = console.getRows(),
    .cols = console.getCols(),
    .xoff = 0,
    .yoff = 0,
    .drawBorder = false,
    .drawShadow = false,
    .drawTitle = false
  };
}

int cterm::Panel::getXOffset() const {
  if (xoff.getType() == PERCENT) {
    return xoff.get() / 100.0 * cols;
  }
  return xoff.get();
}

int cterm::Panel::getYOffset() const {
  if (yoff.getType() == PERCENT) {
    return yoff.get() / 100.0 * rows;
  }
  return yoff.get();
}

void cterm::Panel::draw(Printer& printer) {
  // panel
  printer.setBgColor(bgColor);
  if (drawBorder) {
    printer.moveCursor(0, 0);
    printer.setFgColor(WHITE);
    printer.put(BOX_LEFT_UPPER_CORNER);
    if (drawTitle) {
      if (cols >= title.size()) { /* Error */ }
      int end = cols/2 - title.size() - (drawTitleEdges ? 1 : 0);
      for (int i = 0; i < end; i++) {
        printer.put(BOX_HLINE);
      }
      if (drawTitleEdges) {
        printer.putf("%s", BOX_VLEFT_CROSSING, BOX_VRIGHT_CROSSING);
      }
      printer.setFgColor(titleColor);
      printer.putf(" %s ", title.c_str());
      printer.setFgColor(WHITE);
      if (drawTitleEdges) {
        printer.putf("%s", BOX_VRIGHT_CROSSING);
      }
      int start = cols/2 + (title.size() % 2 == 0 ? title.size() : title.size() - 1) + (drawTitleEdges ? 1 : 0);
      for (int i = start; i < cols; i++) {
        printer.put(BOX_HLINE);
      }
    } else {
      for (int i = 1; i < cols-1; i++) {
        printer.put(BOX_HLINE);
      }
    }
    printer.setFgColor(BLACK);
    printer.put(BOX_RIGHT_UPPER_CORNER);
    // moveCursor(xoff, yoff+1);
    printer.moveCursor(0, 1);
    for (int i = 1; i < rows-1; i++) {
      printer.setFgColor(WHITE);
      printer.put(BOX_VLINE);
      for (int j = 1; j < cols-1; j++) {
        printer.put(" ");
      }
      printer.setFgColor(BLACK);
      printer.put(BOX_VLINE);
      printer.moveCursor(0, i);
    }
    printer.setFgColor(WHITE);
    printer.put(BOX_LEFT_BOTTOM_CORNER);
    printer.setFgColor(BLACK);
    for (int i = 1; i < cols-1; i++) {
      printer.put(BOX_HLINE);
    }
    printer.put(BOX_RIGHT_BOTTOM_CORNER);
  } else {
    for (int i = 0; i < rows; i++) {
      for (int j = 0; j < cols; j++) {
        printer.put(" ");
      }
      printer.moveCursor(0, i);
    }
  }
  // shadow
  if (drawShadow) {
    // TODO: Check bounds
    printer.setBgColor(BLACK);
    for (int i = 1; i < rows; i++) {
      printer.moveCursor(cols, i);
      printer.put("  ");
    }
    for (int i = 1; i < cols; i++) {
      printer.moveCursor(i, rows - 1);
      printer.put("  ");
    }
  }
  /*cterm::setBgColor(bgColor);
  if (drawBorder) {
    moveCursor(xoff, yoff);
    cterm::setFgColor(WHITE);
    printf("%s", BOX_LEFT_UPPER_CORNER);
    if (drawTitle) {
      if (cols >= title.size()) {
        // Error
      }
      for (int i = 0; i < cols/2 - title.size(); i++) {
        printf("%s", BOX_HLINE);
      }
      cterm::setFgColor(titleColor);
      printf(" %s ", title.c_str());
      cterm::setFgColor(WHITE);
      for (int i = cols/2 + title.size(); i < cols; i++) {
        printf("%s", BOX_HLINE);
      }
    } else {
      for (int i = 1; i < cols-1; i++) {
        printf("%s", BOX_HLINE);
      }
    }
    cterm::setFgColor(BLACK);
    printf("%s", BOX_RIGHT_UPPER_CORNER);
    moveCursor(xoff, yoff+1);
    for (int i = 1; i < rows-1; i++) {
      cterm::setFgColor(WHITE);
      printf("%s", BOX_VLINE);
      for (int j = 1; j < cols-1; j++) {
        printf(" ");
      }
      cterm::setFgColor(BLACK);
      printf("%s", BOX_VLINE);
      moveCursor(xoff, yoff+i);
    }
    cterm::setFgColor(WHITE);
    printf("%s", BOX_LEFT_BOTTOM_CORNER);
    cterm::setFgColor(BLACK);
    for (int i = 1; i < cols-1; i++) {
      printf("%s", BOX_HLINE);
    }
    printf("%s", BOX_RIGHT_BOTTOM_CORNER);
  } else {
    for (int i = 0; i < rows; i++) {
      for (int j = 0; j < cols; j++) {
        printf(" ");
      }
      moveCursor(xoff, yoff+i);
    }
  }
  // shadow
  if (drawShadow) {
    // TODO: Check bounds
    cterm::setBgColor(BLACK);
    for (int i = 1; i < rows; i++) {
      moveCursor(xoff + cols, yoff + i);
      printf("  ");
    }
    for (int i = 1; i < cols; i++) {
      moveCursor(xoff + i, yoff + rows - 1);
      printf("  ");
    }
  }*/
}
