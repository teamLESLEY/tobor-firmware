#include "menu.hpp"

using std::string;
using std::vector;

    Menu::Menu(string menuName, vector<string> options, vector<callback_function_t> callbacks)
    : menuName(menuName), options(options), callbacks(callbacks){
        selected = 0;
    }

    unsigned int Menu::select() {
        return selected;
    }
    
    void Menu::cycle(){
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
        display.setCursor(0,0);
        display.println(menuName.c_str());
        display.drawFastHLine(0,7,SCREEN_WIDTH,SSD1306_WHITE);
        
        unsigned int displayedLines = (SCREEN_HEIGHT / 8) - 1;
        unsigned int topLine = 0;
        if(selected >= displayedLines) {
            topLine = selected - displayedLines + 1;
        }

        for (unsigned int i = topLine; i < topLine + displayedLines && i < options.size(); i++){
            if(i == selected){
                display.setTextColor(SSD1306_BLACK, SSD1306_WHITE);
                display.println(options[i].c_str());
                display.setTextColor(SSD1306_WHITE, SSD1306_BLACK);
            } else {
                display.println(options[i].c_str());
            }
        }
        display.display();
    }