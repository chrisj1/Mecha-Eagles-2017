#include "driving.h"

task expDrive() {
	while (true) {

		int x1;
		int x2;
		int y1;
		//Code borrowed from RobotC example code
		//controls the axes of motion for mechanum wheels

		x1 = joyStickExp(vexRT[Ch3]);
		y1 = -joyStickExp(vexRT[Ch4]);
		x2 = joyStickExp(vexRT[Ch1]);

		motor[wheelFL] = (x2 + x1 - y1) * toggleSpeed;
		motor[wheelBL] = (x2 + x1 + y1) * toggleSpeed;
		motor[wheelBR] = (x2 - x1 + y1) * toggleSpeed;
		motor[wheelFR] = (x2 - x1 - y1) * toggleSpeed;
	}
}

float joyStickExp(int joystick) {
	//make the offset negative if moving backwards
	if (abs(joystick) < THRESHOLD) {
			return 0;
	}

	int offset;
	if (joystick < 0) {
		offset = - (powerOffset);
	} else {
		offset = powerOffset;
	}

	//f(x) = (x/10)^3 / 19
	//returns the motor power (HOW IT WORKS on engineering notebook pg.26)
	return pow(joystick/10 , 3) / 18 + offset;
}

void driveRightLeft(int r, int l) {
		motor[wheelFL] = l;
		motor[wheelBL] = l;
		motor[wheelBR] = r;
		motor[wheelFR] = r;
}

void setDriveMotorSpeeds(int speed) {
	motor[wheelFL] = speed;
	motor[wheelBL] = speed;
	motor[wheelBR] = -speed;
	motor[wheelFR] = -speed;
}
