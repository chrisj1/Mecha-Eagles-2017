void forwardsTillLine();

//for some reason, we need to reverse x and y
static int yVelocity = 70;
static int xVelocity = 15;
static const int WHITE_THRESHOLD = 1800;

bool touchingLine() {
	 return SensorValue(frontLine) <= WHITE_THRESHOLD;
}

void drive(int y, int x) {
	motor[wheelFL] = (y - x);
	motor[wheelBL] = (y + x);
	//fixes error: Now doesn't turn to left
	motor[wheelBR] = -(y - x)-20;
	motor[wheelFR] = -(y + x);
}

task increaseY() {
	while (1) {
		xVelocity--;
		wait1Msec(64);
	}
}

void followWall(int distance) {
	startTask(increaseY);
	while (1) {
			if (touchingLine()) {
					xVelocity = 20;
			}
			drive(yVelocity < 0 ? 0 : xVelocity, yVelocity);
	}
}

const int LIFTER_DOWN = 3100;
const int LIFTER_UP = 1960;
void lifterDown() {
	while(SensorValue[lifterPot] < LIFTER_DOWN)	{
		motor[wingR] = -64;
		motor[wingL] = 64;
	}
	motor[wingR] = 0;
	motor[wingL] = 0;
}

task lifterUp() {
	while(SensorValue[lifterPot] > LIFTER_UP)	{
		motor[wingR] = 120;
		motor[wingL] = -120;
	}
	motor[wingR] = 0;
	motor[wingL] = 0;
}

task intitializeGyro() {
	SensorValue(gyro);
	wait10Msec(2000);
}

task gyroscopicStraightening() {
	while(SensorValue(gyro) > 0) {
		motor[wheelFL] = 120;
		motor[wheelBL] = 120;
		motor[wheelBR] = 120;
		motor[wheelFR] = 120;
	}
}

void forwardsTillLine() {
		while(!touchingLine()) {
			motor[wheelFL] = -30;
			motor[wheelBL] = -30;
			motor[wheelBR] = 40;
			motor[wheelFR] = 40;
		}
		motor[wheelFL] = 0;
		motor[wheelBL] = 0;
		motor[wheelBR] = 0;
		motor[wheelFR] = 0;
}

task wingsOut() {
	motor[clawL] = -40;
	motor[clawR] = -120;
	wait1Msec(1000);
	motor[clawL] = 0;
	motor[clawR] = 0;
}

void getCubeAutonomous() {
	//startTask(intitializeGyro);
	startTask(wingsOut);
	motor[wheelFL] = -127;
	motor[wheelBL] = 127;
	motor[wheelBR] = 127;
	motor[wheelFR] = -127;
	wait10Msec(700);
	motor[wheelFL] = -127;
	motor[wheelBL] = -127;
	motor[wheelBR] = 127;
	motor[wheelFR] = 127;
	wait10Msec(700);
	motor[wheelFL] = 0;
	motor[wheelBL] = 0;
	motor[wheelBR] = 0;
	motor[wheelFR] = 0;
	//closes on cube
	motor[clawR] = -127;
	wait10Msec(1200);
	startTask(lifterUp);
}


void getCube() {
	startTask(gyroscopicStraightening);
}

void startAutonomous() {
		startTask(wingsOut);
		startTask(lifterUp);
		motor[wheelFL] = -120;
		motor[wheelBL] = -120;
		motor[wheelBR] = 120;
		motor[wheelFR] = 120;
		wait1Msec(1400);
		forwardsTillLine();
		motor[wheelFL] = 100;
		motor[wheelBL] = 100;
		motor[wheelBR] = -100;
		motor[wheelFR] = -100;
		wait1Msec(400);
		motor[wheelFL] = 0;
		motor[wheelBL] = 0;
		motor[wheelBR] = 0;
		motor[wheelFR] = 0;
}
