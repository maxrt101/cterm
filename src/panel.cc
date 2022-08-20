#include <cterm/panel.h>
#include <cterm/console.h>
#include <cterm/cursor.h>
#include <cterm/input.h>
#include <cterm/chars.h>
#include <algorithm>
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
  return xoff.transformIfPercent(
    [this](int val) { return val / 100.0 * cols; }
  );
}

int cterm::Panel::getYOffset() const {
  return yoff.transformIfPercent(
    [this](int val) { return val / 100.0 * rows; }
  );
}

cterm::Widget* cterm::Panel::getWidgetByTag(const std::string tag) const {
  if (layout) {
    for (auto& widget : layout->widgets) {
      if (widget && widget->tag == tag) {
        return widget;
      }
    }
  }

  return nullptr;
}

bool cterm::Panel::handleInput(char c) {
  if (inputHandler) {
    return inputHandler(c);
  }

  switch (c) {
    case io::UP_ARROW:
      break;
    case io::DOWN_ARROW:
      break;
    case io::LEFT_ARROW:
      break;
    case io::RIGHT_ARROW:
      break;
    case ' ':
      break;
  }

  return true;
}

void cterm::Panel::draw(Printer& printer) {
  printer.setBgColor(bgColor);
  if (drawBorder) {
    printer.moveCursor(0, 0);
    if (drawBlackWhiteBorder) {
      printer.setFgColor(WHITE);
    } else {
      printer.setFgColor(borderColor);
    }
    printer.put(BOX_LEFT_UPPER_CORNER);
    if (drawTitle) {
      if (cols >= title.size()) { /* Error */ }
      if (!drawBlackWhiteBorder) printer.setFgColor(titleColor);
      int end = cols/2 - title.size() - (drawTitleEdges ? 1 : 0);
      for (int i = 0; i < end; i++) {
        printer.put(BOX_HLINE);
      }
      if (drawTitleEdges) {
        printer.putf("%s", BOX_VLEFT_CROSSING);
      }
      printer.setFgColor(titleColor);
      printer.putf(" %s ", title.c_str());
      if (drawBlackWhiteBorder) {
        printer.setFgColor(WHITE);
      } else {
        printer.setFgColor(borderColor);
      }
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
    if (drawBlackWhiteBorder) printer.setFgColor(BLACK);
    printer.put(BOX_RIGHT_UPPER_CORNER);
    printer.moveCursor(0, 1);
    for (int i = 1; i < rows-1; i++) {
      bool isVLine = vLines.end() != std::find_if(
        vLines.begin(),
        vLines.end(),
        [&](auto vline) { return i == vline.transformIfPercent([&](int val) { return val / 100.0 * rows; }); }
      );
      if (drawBlackWhiteBorder) printer.setFgColor(WHITE);
      if (isVLine) {
        printer.put(BOX_VRIGHT_CROSSING);
      } else {
        printer.put(BOX_VLINE);
      }
      for (int j = 1; j < cols-1; j++) {
        if (isVLine) {
          printer.put(BOX_HLINE);
        } else {
          printer.put(" ");
        }
      }
      if (drawBlackWhiteBorder) printer.setFgColor(BLACK);
      if (isVLine) {
        printer.put(BOX_VLEFT_CROSSING);
      } else {
        printer.put(BOX_VLINE);
      }
      printer.moveCursor(0, i);
    }
    if (drawBlackWhiteBorder) printer.setFgColor(WHITE);
    printer.put(BOX_LEFT_BOTTOM_CORNER);
    if (drawBlackWhiteBorder) printer.setFgColor(BLACK);
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

  printer.setBgColor(bgColor);
  printer.setFgColor(fgColor);
  if (layout) {
    printer.begin(1, 1, cols, rows);
    layout->draw(printer);
  }
}
