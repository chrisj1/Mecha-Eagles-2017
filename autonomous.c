void forwardsTillLine();

const int START_Y_SPEED = 10;
static int xVelocity = 120;
static int yVelocity = START_Y_SPEED;
static const int WHITE_THRESHOLD = 1300;

void resetEncoders() {
	resetMotorEncoder(wheelBL);
	resetMotorEncoder(wheelBR);
	resetMotorEncoder(wheelFL);
	resetMotorEncoder(wheelFR);
}

bool isTurnNegative(float angle) {
	return angle < 0;
}

void stopDrive() {
	setDriveMotorSpeeds(0);
}

void straighten(int speed) {
	int angle = SensorValue[gyro]/10.0;
	int negate = isTurnNegative(angle) ? -1 : 1;
	do {
		driveRightLeft(-speed * negate, speed * negate);
	}while(abs(angle) <= 5);
	driveRightLeft(0,0);
}

void turn(float angle, int speed) {
	turn(angle, speed, 40);
}

void turn(float angle, int speed, int min_value) {
	if(angle == 0) return;
	int startAngle = SensorValue[gyro]/10.0;
	int negate = isTurnNegative(angle) ? -1 : 1;
	double delta;
	do {
		motor[wheelBR] = -speed;
		motor[wheelFR] = -speed;
		motor[wheelFL] = speed;
		motor[wheelBL] = speed;
		driveRightLeft(-speed * negate, -speed * negate);
		wait1Msec(30);
		delta = startAngle - SensorValue[gyro]/10.0;
		if(abs(delta - angle) < 10) {
			speed = max(min_value, speed * .998);
		}
	}while(abs(delta) < abs(angle + 15));
	driveRightLeft(0,0);
}


bool touchingLine() {
	return 1;//SensorValue(frontLine) <= WHITE_THRESHOLD;
}

void drive(int y, int x) {
	if(x == 0) {
		y = y * 60;
	}
	motor[wheelFL] = (y - x);
	motor[wheelBL] = (y + x);
	motor[wheelBR] = -(y - x);
	motor[wheelFR] = -(y + x);
}

task increaseY() {
	while (1) {
		yVelocity--;
		wait1Msec(20);
	}
}

void followWall(int distance) {
	startTask(increaseY);
	while (1) {
		//back up when touching the line
		if (touchingLine()) {
			writeDebugStreamLine("White");
			yVelocity = START_Y_SPEED;
		}
		drive(-yVelocity, (xVelocity * (isRight ? 1 : -1) * (yVelocity < 0)));
	}
}

const int LIFTER_DOWN = 3000;
const int LIFTER_UP = 1900;

void lifterDown() {
	while(SensorValue[lifterPot] < LIFTER_DOWN)	{
		motor[wingR] = -64;
		motor[wingL] = 64;
		motor[wingChain] = -64;
	}
	motor[wingR] = 0;
	motor[wingL] = 0;
}

task lifterUp() {
	while(SensorValue[lifterPot] > LIFTER_UP)	{
		motor[wingL] = 127;
		motor[wingR] = -127;
		motor[wingChain] = 127;
	}
	motor[wingR] = 0;
	motor[wingL] = 0;
	motor[wingChain] = 0;
}

void funcLifterUp(bool hold) {
	while(SensorValue[lifterPot] > LIFTER_UP)	{
		motor[wingL] = 127;
		motor[wingR] = -127;
		motor[wingChain] = 127;
	}
	if(hold)
		startTask(holdLifterPos);
}

void funcLifterUp(bool hold, int height) {
	while(SensorValue[lifterPot] < height)	{
		motor[wingL] = 127;
		motor[wingR] = -127;
		motor[wingChain] = 127;
	}
	if(hold)
		startTask(holdLifterPos);
}

void forwardsTillLine() {
	while(!touchingLine()) {
		motor[wheelFL] = -80;
		motor[wheelBL] = -80;
		motor[wheelBR] = 70;
		motor[wheelFR] = 70;
	}
	stopDrive();
}

void clawsOut() {
	if(isRight) {
		motor[clawL] = -65;
		motor[clawR] = 45;
		wait1Msec(1050);
		motor[clawL] = 0;
		motor[clawR] = 0;
		} else {
		motor[clawL] = -55;
		motor[clawR] = 45;
		wait1Msec(1050);
		motor[clawL] = 0;
		motor[clawR] = 0;
	}
}

void startAutonomous() {
	startTask(lifterUp);
	clawsOut();
	setDriveMotorSpeeds(120);
	wait1Msec(2500);
	forwardsTillLine();
	setDriveMotorSpeeds(-100);
	wait1Msec(400);
	stopDrive();
}

void startWallDrive() {
	resetMotorEncoder(wheelFL);
	int multiplier = 1;
	if (!isRight) {
		multiplier = -1;
	}
	startTask(lifterUp);
	clawsOut();
	//drive up to the fence
	while(getMotorEncoder(wheelFL) <= 2540) {
		driveRightLeft(-120,120);
	}

	//backup
	driveRightLeft(0,0);
	resetMotorEncoder(wheelFL);
	while(getMotorEncoder(wheelFL) >= -345) {
		driveRightLeft(80, -80);
	}
	driveRightLeft(0,0);
	//rotate
	turn(89.0 * multiplier, 80);
	resetMotorEncoder(wheelFL);
	//sweep across the fence
	driveRightLeft(-45,45);
	while(getMotorEncoder(wheelFL) <= 700) { //wait till we go past the middle part of the fence.
		//lower claws when in the middle part of the fence
		if (getMotorEncoder(wheelFL) >= 140 && getMotorEncoder(wheelFL) <= 165) {
			motor[wingR] = 64;
			motor[wingL] = -64;
			motor[wingChain] = 64;
			} else {
			motor[wingR] = 0;
			motor[wingL] = 0;
			motor[wingChain] = 0;
		}
	}
	//startTask(lifterUp);
	while(getMotorEncoder(wheelFL) <= 4500) {
		//driveRightLeft(-45,45);
		if (getMotorEncoder(wheelFL) >= 1800 && getMotorEncoder(wheelFL) <= 1815) {
			motor[wingR] = -50;
			motor[wingL] = 50;
		} else {
			motor[wingR] = 0;
			motor[wingL] = 0;
		}
	}
	driveRightLeft(0,0);
}

void launchStar(){
	motor[wingR] = 120;
	motor[wingL] = -120;
	motor[wingChain] = 120;
	wait1Msec(200);
	motor[wingR] = 120;
	motor[wingL] = -120;
	motor[wingChain] = -120;
	wait1Msec(200);
	motor[wingR] = 40;
	motor[wingL] = -40;
	motor[wingChain] = -40;
}

void turnTowardsStars(bool isOnRight) {
	turn(-90.0, 100);
}

void collectStars(bool isOnRight, bool endOnRightSide) {
	turnTowardsStars(isOnRight);
}

void setClawPos(int arm, int pos) {
	if(arm == CLAW_RIGHT) {
		bool increaseValue = pos < SensorValue[rightClaw];
		while(abs(SensorValue[rightClaw] - pos) > 1) {
			if(increaseValue) {
				motor[clawR] = 127;
				}else {
				motor[clawR] = -127;
			}
		}
	}

	if(arm == CLAW_LEFT) {
		bool increaseValue = pos < SensorValue[leftClaw];
		while(abs(SensorValue[leftClaw] - pos) > 1) {
			if(increaseValue) {
				motor[clawL] = -127;
				}else {
				motor[clawL] = 127;
			}
		}
	}

	if(arm == CLAW_BOTH) {
		while(abs(SensorValue[leftClaw] - pos) > 1 || abs(SensorValue[rightClaw] - pos) > 1) {
			bool increaseValueLeft = pos < SensorValue[leftClaw];
			if(increaseValueLeft) {
				motor[clawL] = -127;
				}else {
				motor[clawL] = 127;
			}
		}
		bool increaseValueRight = pos < SensorValue[rightClaw];
		if(increaseValueRight) {
			motor[clawR] = -127;
			}else {
			motor[clawR] = 127;
		}
	}

	motor[clawL] = 0;
	motor[clawR] = 0;
}

void clawPreLaunch() {
	motor[clawL] = -127;
	motor[clawR] = 70;
	wait1Msec(400);
	motor[clawL] = 0;
	motor[clawR] = 0;
}
