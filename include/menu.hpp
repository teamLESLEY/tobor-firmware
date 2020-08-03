#ifndef MENU_HPP
#define MENU_HPP

#include <string>
#include <vector>
#include <Adafruit_SSD1306.h>
#include <Arduino.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64

struct MenuLine {
  std::string name;
  callback_function_t callback;
};

typedef std::vector<struct MenuLine> MenuOptions;

class Menu {

public:

    std::string menuName;
  MenuOptions options;
    unsigned int selected;

  Menu(std::string menuName, MenuOptions options);
    unsigned int select();
    void cycle();
    void show(Adafruit_SSD1306 display);

private:
    void updateDisplay(Adafruit_SSD1306 display);
};

#endif
