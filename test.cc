
#include <cterm/console.h>
#include <cterm/colors.h>
#include <cterm/panel.h>
#include <cterm/input.h>
#include <cterm/cursor.h>
#include <cterm/layout.h>
#include <cterm/widgets/text.h>
#include <cstdio>


int main() {
  cterm::io::saveTerminalSettings();
  cterm::io::showCursor(false);

  cterm::Console console;

  console.addPanel({
    .tag = "test_panel",
    .title = "Test",
    .cols = console.getCols().percent(50),
    .rows = console.getRows().percent(50),
    .xoff = console.getCols().percent(25),
    .yoff = console.getRows().percent(25),
    .bgColor = cterm::GREY,
    .fgColor = cterm::BLACK,
    .drawBlackWhiteBorder = false,
    .vLines = {
      console.getRows().percent(50) - 3
    },
    .layout = cterm::Layout::vertical({
      .xoff = 2,
      .widgets = {
        cterm::widget::Text::create({
          .text = "Test 123\nTEST 567 test 789",
          .maxWidth = cterm::percent(100),
          .maxHeight = 2,
          .bgColor = cterm::GREY,
          .fgColor = cterm::BLACK
        }),
        cterm::widget::Text::create({
          .xoff = 1,
          .yoff = console.getRows().percent(50)-4,
          .text = "Status"
        })
      }
    }),
  });

  console.addPanel({
    .tag = "alert",
    .title = "Alert",
    .rows = console.getRows().percent(25),
    .cols = console.getCols().percent(25),
    .xoff = console.getCols()/8,
    .yoff = console.getRows()/8,
    .bgColor = cterm::RED,
    .titleColor = cterm::WHITE,
    .layout = cterm::Layout::vertical({
      .widgets = {
        cterm::widget::Text::create({
          .text = "Alerting the user that something important happend"
        })
      }
    })
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
  cterm::io::showCursor(true);
  printf("\n");
}
