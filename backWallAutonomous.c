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
		while(SensorValue[sonarLeft] < 47){
			if(time1[T1] > 1700)
				break;
		}
	}else {
		while(SensorValue[sonarRight] < 47){
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
		motor[clawR] = 30;
	} else {
		motor[clawL] = 30;
	}
	//move forwards to collect stars and cubes
	drive(90, 40);
	resetMotorEncoder(wheelFR);
	//push wings down
	const int WING_SPEED = 60;
	motor[wingR] = WING_SPEED;
	motor[wingL] = -WING_SPEED;
	motor[wingChain] = WING_SPEED;
	if(isRight){
		motor[clawL] = -20;
	} else {
		motor[clawR] = -20;
	}
	while(abs(getMotorEncoder(wheelFR)) < 1850) {
	}
	stopDrive();
	wait1Msec(60);
	driveRightLeft(-60,40);
	resetMotorEncoder(wheelBR);
	motor[wingR] = WING_SPEED;
	motor[wingL] = -WING_SPEED;
	motor[wingChain] = WING_SPEED;
	while(abs(getMotorEncoder(wheelFR)) < 1800) {}
	stopDrive();
	motor[clawR] = 127;
	motor[clawL] = -127;
	wait1Msec(1100);

	funcLifterUp();
	if(isRight) {
		turn(-finalTurnAngle - 90, 60);
	} else {
		turn(finalTurnAngle + 90, 60);
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
	stopTask(holdLifterPos);

	//go backward, lower lifter, and go forward
	//to knock some extra stars off the fence
	driveRightLeft(127,-127);
	wait1Msec(1200);
	//lowser the lifter and extend the claws
	stopDrive();
	motor[clawR] = -50;
	motor[clawL] = 50;
	wait1Msec(600);
	motor[clawR] = 0;
	motor[clawL] = 0;

	//stop holding pos
	while(SensorValue[lifterPot] < 2107) {
		motor[wingR] = (60);
		motor[wingL] = (-60);
		motor[wingChain] = 60;
	}

	motor[wingR] = (-20);
	motor[wingL] = (20);
	motor[wingChain] = -20;

	startTask(holderLifterPos);
	//drive forward
	driveRightLeft(-127,127);
	wait1Msec(1500);
	motor[clawL] = 0;
	motor[clawR] = 0;
	stopDrive();
}
