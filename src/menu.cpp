#include "menu.hpp"

Menu::Menu(std::string menuName, MenuOptions options)
  : menuName(menuName), options(options) {
  selected = 0;
}

void Menu::select() {
  options[selected].callback();
}

void Menu::cycle() {
  selected++;
  if (selected >= options.size()){
    selected = 0;
  }
}

void Menu::show(Adafruit_SSD1306 display) {
  updateDisplay(display);
}

void Menu::updateDisplay(Adafruit_SSD1306 display) {
  display.clearDisplay();
  display.setCursor(0, 0);
  display.println(menuName.c_str());
  display.drawFastHLine(0, 7, display.width(), SSD1306_WHITE);

  unsigned int displayedLines = (display.height() / 8) - 1;
  unsigned int topLine = 0;
  if (selected >= displayedLines - 1) {
    topLine = selected - displayedLines + 2;
  }

  for (unsigned int i = topLine; i < min(topLine + displayedLines, options.size()); i++) {
    if (i == selected) {
      display.setTextColor(SSD1306_BLACK, SSD1306_WHITE);
      display.println(options[i].name.c_str());
      display.setTextColor(SSD1306_WHITE, SSD1306_BLACK);
    } else {
      display.println(options[i].name.c_str());
    }
  }
  display.display();
}
