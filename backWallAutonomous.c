#include "backWallAutonomous.h"

void wingsOutDiff() {
		if (isRight) {
			motor[clawL] = -100;
			motor[clawR] = 25;
			wait1Msec(1000);
			motor[clawL] = 0;
			motor[clawR] = 0;
		} else {
			motor[clawL] = 25;
			motor[clawR] = 100;
			wait1Msec(1000);
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
		while(SensorValue[sonarLeft] < 32){
			if(time1[T1] > 1700)
				break;
		}
	}else {
		while(SensorValue[sonarRight] < 32){
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
	driveRightLeft(-90,80);
	resetMotorEncoder(wheelFL);
	//push wings down
	const int WING_SPEED = 60;
	motor[wingR] = WING_SPEED;
	motor[wingL] = -WING_SPEED;
	motor[wingChain] = WING_SPEED;
	while(getMotorEncoder(wheelFR) > -900) {
	}
	stopDrive();
	wait1Msec(60);
	driveRightLeft(-60,40);
	resetMotorEncoder(wheelFR);
	motor[wingR] = WING_SPEED;
	motor[wingL] = -WING_SPEED;
	motor[wingChain] = WING_SPEED;
	while(getMotorEncoder(wheelFR) > -1500) {}
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
	motor[wingR] = 100;
	motor[wingL] = -100;
	motor[wingChain] = 100;

	wait1Msec(200);

	motor[clawR] = -120;
	motor[clawL] = 120;

	stopDrive();

	wait1Msec(900);

	motor[clawR] = 0;
	motor[clawL] = 0;

	motor[wingR] = -100;
	motor[wingL] = 100;
	motor[wingChain] = -100;

	wait1Msec(800);

	driveRightLeft(127,-120);
	wait1Msec(2000);
	stopDrive();

}
