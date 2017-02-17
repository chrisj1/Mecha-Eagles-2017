#define autonomous_h

#ifndef sensor_h
#include "sensor.c"
#endif

#ifndef driving_h
#include "driving.c"
#endif

#define CLAW_LEFT 0
#define CLAW_BOTH 1
#define CLAW_RIGHT 2

void turnTowardsStars(bool isOnRight);
bool determineTurnNegative(double angle);
void turn(double angle, int speed);
void straighten(int speed);
void collectStars(bool isOnRight, bool endOnRightSide);
void startWallDrive();
