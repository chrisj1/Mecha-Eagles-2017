#ifndef lcd_h
#define lcd_h
#endif

#ifndef sensor_h
#include "sensor.c"
#endif

#ifndef consts_h
#include "consts.h"
#endif

int displayLCDMenu(string* optionsP, int length, string prompt);
void waitForPress();
void waitForRelease();
bool askCube();
void clearScreen();
void checkBattery();
task flashScreen();
int askRoutine();
