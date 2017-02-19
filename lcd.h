#ifndef LCD_H
#define LCD_H

#include "consts.h"
#include "sensor.h"

int displayLCDMenu(string* optionsP, int length, string prompt);
void waitForPress();
void waitForRelease();
void clearScreen();
void checkBattery();
task flashScreen();
int askRoutine();

#include "lcd.c"

#endif
