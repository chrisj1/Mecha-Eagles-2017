#ifndef DRIVING_H
#define DRIVING_H
const int powerOffset = 30;
float toggleSpeed = 1;

const int THRESHOLD = 30;

task expDrive();
float joyStickExp(int joystick);
task expDrive();
void driveRightLeft(int r, int l);
void setDriveMotorSpeeds(int speed);

#include "driving.c"
#endif //DRIVING_H
