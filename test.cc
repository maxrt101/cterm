
#include <cterm/cterm.h>
#include <cterm/input.h>
#include <cterm/cursor.h>
#include <cstdio>

int main() {
  cterm::io::saveTerminalSettings();

  cterm::Console console;
  console.addPanel({
    .tag = "test_panel",
    .title = "Test",
    .rows = console.getRows()/2,
    .cols = console.getCols()/2,
    .xoff = console.getCols()/4,
    .yoff = console.getRows()/4,
    .bgColor = cterm::GREY,
    .fgColor = cterm::BLACK,
  });

  console.addPanel({
    .tag = "alert",
    .title = "Alert",
    .rows = console.getRows()/4,
    .cols = console.getCols()/4,
    .xoff = console.getCols()/8*3,
    .yoff = console.getRows()/8*3,
    .bgColor = cterm::RED,
    .titleColor = cterm::WHITE,
  });

  cterm::io::setOneCharRead(true);
  cterm::io::setEcho(false);
  cterm::moveCursor(0, console.getRows());

  bool running = true;
  while (running) {
    console.draw();
    int c = cterm::io::getChar();
    switch (c) {
      case cterm::io::UP_ARROW:
        console.getPanelByTag("alert").yoff--;
        break;
      case cterm::io::DOWN_ARROW:
        console.getPanelByTag("alert").yoff++;
        break;
      case cterm::io::LEFT_ARROW:
        console.getPanelByTag("alert").xoff--;
        break;
      case cterm::io::RIGHT_ARROW:
        console.getPanelByTag("alert").xoff++;
        break;
      case ' ':
        console.getPanelByTag("alert").active = !console.getPanelByTag("alert").active;
        break;
      case 'q':
        running = false;
    }
  }

  cterm::moveCursor(0, console.getRows());
  cterm::io::restoreTerminalSettings();
  printf("\n");
}
