#ifndef AUTONOMOUS_H
#define AUTONOMOUS_H

#define CLAW_LEFT 0
#define CLAW_BOTH 1
#define CLAW_RIGHT 2

void turnTowardsStars(bool isOnRight);
void turn(float angle, int speed);
void straighten(int speed);
void collectStars(bool isOnRight, bool endOnRightSide);
void startWallDrive();
void turn(float angle, int speed, int min_value);


#include "autonomous.c"

#endif
