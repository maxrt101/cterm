#include <cterm/widgets/text.h>
#include <cterm/printer.h>
#include <cmath>

cterm::IntegerValue cterm::widget::Text::getWidth() const {
  if (maxWidth.get() != -1) {
    return maxWidth.get();
  }

  std::vector<int> lineSizes = getLineLengths();

  auto it = std::max_element(lineSizes.begin(), lineSizes.end());
  if (it != lineSizes.end()) {
    return *it;
  }

  return text.size();
}

cterm::IntegerValue cterm::widget::Text::getHeight() const {
  if (maxHeight.get() != -1) {
    return maxHeight.get();
  }

  int newlines = 0;
  for (int i = 0; i < text.size(); i++) {
    if (text[i] == '\n') {
      newlines++;
    }
  }

  return newlines + 1;
}

std::vector<std::string> cterm::widget::Text::getLines() const {
  std::vector<std::string> lines;

  std::string line;
  for (int i = 0; i < text.size(); i++) {
    if (text[i] == '\n') {
      lines.push_back(line);
      line = "";
      i++;
      continue;
    }
    line += text[i];
  }

  return lines;
}

std::vector<int> cterm::widget::Text::getLineLengths() const {
  std::vector<int> lineSizes;

  int lineSize = 0;
  for (int i = 0; i < text.size(); i++) {
    if (text[i] == '\n') {
      lineSizes.push_back(lineSize);
      lineSize = 0;
    }
    lineSize++;
  }

  return lineSizes;
}

void cterm::widget::Text::draw(Printer& printer) {
  printer.setBgColor(bgColor == -1 ? printer.getBgColor() : bgColor);
  printer.setFgColor(fgColor == -1 ? printer.getFgColor() : fgColor);

  int height = getHeight().transformIfPercent(
    [&](int val) { return val / 100.0 * printer.getHeight(); }
  );

  int width = getWidth().transformIfPercent(
    [&](int val) { return val / 100.0 * printer.getWidth(); }
  );

  if (width > printer.getWidth()) {
    height = std::ceil(width / (float)printer.getWidth());
    width = printer.getWidth();
  }

  if (height > printer.getHeight()) {
    height = printer.getHeight();
  }

  // std::vector<std::string> lines = getLines(); // TODO:

  int textIndex = 0;
  bool newline = false;
  for (int y = 0; y < height; y++) {
    for (int x = 0; x < width; x++) {
      printer.moveCursor(x, y);
      if (newline) {
        printer.put(' ');
        continue;
      }
      if (textIndex < text.size()) {
        if (text[textIndex] == '\n') {
          newline = true;
          textIndex++;
          printer.put(' ');
        } else {
          printer.put(text[textIndex++]);
        }
      } else {
        printer.put(' ');
      }
    }
    newline = false;
  }
}

cterm::widget::Text* cterm::widget::Text::create(TextArgs args) {
  Text* textWidget = new Text;
  textWidget->text = args.text;
  textWidget->align = args.align;
  textWidget->textAlign = args.textAlign;
  textWidget->tag = args.tag;
  textWidget->xoff = args.xoff;
  textWidget->yoff = args.yoff;
  textWidget->maxWidth = args.maxWidth;
  textWidget->maxHeight = args.maxHeight;
  textWidget->bgColor = args.bgColor;
  textWidget->fgColor = args.fgColor;
  return textWidget;
}
