#include "menu.hpp"

    Menu::Menu(char *menuName, /*char **options,*/ int numOptions, Adafruit_SSD1306 display)
    : menuName(menuName),/* options(options),*/ numOptions(numOptions), display(display){
    }

    int Menu::select(){
        return selected;
    }
    void Menu::cycle(){
        selected++;
        if (selected >= numOptions){
            selected = 0;
        }
        updateDisplay();
    }

    void Menu::show(){
        updateDisplay();
    }

    void Menu::updateDisplay(){
        display.clearDisplay();
        display.setCursor(0,0);
        display.println(menuName);
        display.drawFastHLine(0,7,SCREEN_WIDTH,SSD1306_WHITE);

        int displayedLines = (SCREEN_HEIGHT / 8) - 1;
        int topLine = 0;
        if(selected >= displayedLines) {
            topLine = selected - displayedLines + 1;
        }

        for (int i = topLine; i < displayedLines && i < numOptions; i++){
            if(i == selected){
                display.setTextColor(SSD1306_BLACK, SSD1306_WHITE);
                display.println(i);
            } else {
                display.setTextColor(SSD1306_WHITE, SSD1306_BLACK);
                display.println(i);
            }
        }
        display.display();
    }