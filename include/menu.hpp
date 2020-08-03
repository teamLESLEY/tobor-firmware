#ifndef MENU_HPP
#define MENU_HPP

#include <string>
#include <vector>
#include <Adafruit_SSD1306.h>
#include <Arduino.h>

struct MenuLine {
  std::string name;
  callback_function_t callback;
};

typedef std::vector<struct MenuLine> MenuOptions;

class Menu {
  std::string menuName;
  MenuOptions options;
  unsigned int selected;

  void updateDisplay(Adafruit_SSD1306 display);

public:
  Menu(std::string menuName, MenuOptions options);
  void select();
  void cycle();
  void show(Adafruit_SSD1306 display);
};

#endif
