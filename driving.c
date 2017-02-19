task expDrive() {
	while (true) {
		//Code borrowed from RobotC example code
		//controls the axes of motion for mechanum wheels

		//int x = joyStickExp(vexRT[Ch3]);
		//int y = -joyStickExp(vexRT[Ch4]);

		int x = joyStickExp(vexRT[Ch3]);
		int y = joyStickExp(-vexRT[Ch4]);

		int r = -(y + x);
		int l = -(y - x);
		motor[wheelFL] = l;
		motor[wheelBL] = l;
		motor[wheelBR] = r;
		motor[wheelFR] = r;
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
