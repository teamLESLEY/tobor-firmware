#ifndef MENU_HPP
#define MENU_HPP

#include <string>
#include <Wire.h>
#include <Adafruit_SSD1306.h>
#include <Arduino.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64

using namespace std;

class Menu {

    Adafruit_SSD1306 display;
    char *menuName;
    //char **options; // pointer to first element of an array of options
    int numOptions;
    int selected = 0;

public:
    Menu(char *menuName,/* char **options, */int numOptions, Adafruit_SSD1306 display);
    int select();
    void cycle();
    void show();

private:
    void updateDisplay();

};




#endif