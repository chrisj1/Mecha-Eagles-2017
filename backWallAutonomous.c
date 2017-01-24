#include "backWallAutonomous.h"

void wingsOutDiff() {
		if (isRight) {
			motor[clawL] = -100;
			motor[clawR] = 35;
			wait1Msec(400);
			motor[clawL] = 0;
			motor[clawR] = 0;
		} else {
			motor[clawL] = 30;
			motor[clawR] = 100;
			wait1Msec(400);
			motor[clawL] = 0;
			motor[clawR] = 0;
		}
}

task wingsOutAsync {
	wingsOutDiff();
}

void startBackWallAuton() {
	clawPreLaunch();
	launchStar();
	//goes sideways out of starting area
	if(isRight) {
		drive(0, -110);
	}else{
		drive(0, 110);
	}
	//wait till 30 cm from wall
	clearTimer(T1);
	//30 cm for competition field
	if(isRight) {
		while(SensorValue[sonarLeft] < 37){
			if(time1[T1] > 1700)
				break;
		}
	}else {
		while(SensorValue[sonarRight] < 37){
			if(time1[T1] > 1700)
				break;
		}
	}
	stopDrive();
	//move claw to ctarting pos
	startTask(wingsOutAsync);
	wait1Msec(1000)
	//close right claw while driving
	if(isRight) {
		motor[clawR] = 60;
	} else {
		motor[clawL] = 60;
	}
	//move forwards to collect stars and cubes
	driveRightLeft(-105,90);
	resetMotorEncoder(wheelFR);
	//push wings down
	const int WING_SPEED = 60;
	motor[wingR] = WING_SPEED;
	motor[wingL] = -WING_SPEED;
	motor[wingChain] = WING_SPEED;
	motor[clawL] = -40;
	while(abs(getMotorEncoder(wheelFR)) < 1600) {
	}
	stopDrive();
	wait1Msec(60);
	driveRightLeft(-60,40);
	resetMotorEncoder(wheelBR);
	motor[wingR] = WING_SPEED;
	motor[wingL] = -WING_SPEED;
	motor[wingChain] = WING_SPEED;
	while(abs(getMotorEncoder(wheelFR)) < 1700) {}
	stopDrive();
	motor[clawR] = 127;
	motor[clawL] = -127;
	wait1Msec(1100);

	funcLifterUp();
	if(isRight) {
		turn(-finalTurnAngle - 90, 100);
	} else {
		turn(finalTurnAngle + 90, 100);
	}
	driveRightLeft(-127,120);
	wait1Msec(2000 / cosDegrees(finalTurnAngle));

	wait1Msec(200);

	//release stuff
	motor[clawR] = -120;
	motor[clawL] = 120;
	wait1Msec(500);
	motor[clawR] = 0;
	motor[clawL] = 0;

	stopDrive();

	//stop holding pos
	stopTask(holdLifterPos);

	driveRightLeft(127,-127);
	wait1Msec(1000);
	motor[wingR] = -WING_SPEED;
	motor[wingL] = WING_SPEED;
	motor[wingChain] = WING_SPEED;
	wait1Msec(100);
	driveRightLeft(-127,127);
	wait1Msec(1000);
	driveRightLeft(0,0);
}
