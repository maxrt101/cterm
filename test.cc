#include <cterm/console.h>
#include <cterm/colors.h>
#include <cterm/panel.h>
#include <cterm/input.h>
#include <cterm/cursor.h>
#include <cterm/layout.h>
#include <cterm/widgets/text.h>
#include <cterm/widgets/button.h>
#include <cstdio>


int main() {
  system("echo start >> log");
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
          .tag = "fill_text",
          .text = "Test 123\nTEST 567 test 789",
          .maxWidth = cterm::percent(100),
          .maxHeight = 2,
          .bgColor = cterm::GREY,
          .fgColor = cterm::BLACK
        }),
        cterm::widget::Button::create({
          .label = "show alert",
          .bgColor = cterm::BLACK,
          .fgColor = cterm::WHITE,
          .selectBgColor = cterm::WHITE,
          .selectFgColor = cterm::BLACK,
          .onClick = [&console]() {
            console.getPanelByTag("alert").active = !console.getPanelByTag("alert").active;
          }
        }),
        cterm::widget::Button::create({
          .label = "test",
          .bgColor = cterm::RED,
          .fgColor = cterm::GREEN,
          .selectBgColor = cterm::GREEN,
          .selectFgColor = cterm::RED,
          .onClick = [&console]() {
            int& color = dynamic_cast<cterm::widget::Text*>(console.getPanelByTag("test_panel").getWidgetByTag("fill_text"))->fgColor;
            color = color == cterm::BLACK ? cterm::PURPLE : cterm::BLACK;
          }
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
      case 'n': // next button
        console.getPanelByTag("test_panel").cycleSelection();
        break;
      case 's': // button select
        console.getPanelByTag("test_panel").toggleSelection();
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
