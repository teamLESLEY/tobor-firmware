#include "menu.hpp"
#include <vector>
#include <string>

using std::string;
using std::vector;

    Menu::Menu(char *menuName, vector<string> options, Adafruit_SSD1306 display)
    : menuName(menuName), options(options), display(display) {
    }

    int Menu::select() {
        return selected;

    }
    void Menu::cycle() {
        selected++;

        if (selected >= numOptions){
            selected = 0;
        }

        updateDisplay();
    }

    void Menu::show() {
        updateDisplay();
    }

    void Menu::updateDisplay() {
        display.clearDisplay();
        display.setCursor(0,0);
        display.println(menuName);
        display.drawFastHLine(0,7,SCREEN_WIDTH,SSD1306_WHITE);

        int displayedLines = (SCREEN_HEIGHT / 8) - 1;
        int topLine = 0;
        if(selected >= displayedLines) {
            topLine = selected - displayedLines + 1;
        }

        for (int i = topLine; i < displayedLines && i < options.size(); i++){
            if(i == selected){
                display.setTextColor(SSD1306_BLACK, SSD1306_WHITE);
            } else {
                display.setTextColor(SSD1306_WHITE, SSD1306_BLACK);
            }

            display.println(options[i].c_str());
        }

        display.display();
    }
