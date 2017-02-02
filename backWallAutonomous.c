#include "backWallAutonomous.h"

void initLeftArm();

void wingsOutDiff() {
		if (isRight) {
			motor[clawL] = -60;
			motor[clawR] = 60;
			wait1Msec(500);
			motor[clawL] = 0;
			motor[clawR] = 0;
		} else {
			motor[clawL] = 60;
			motor[clawR] = 60;
			wait1Msec(500);
			motor[clawL] = 0;
			motor[clawR] = 0;
		}
}

void knockRemainingStars() {
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
	while(SensorValue[lifterPot] < 2400) {
		motor[wingR] = (60);
		motor[wingL] = (-60);
		motor[wingChain] = 60;
	}

	//motor[wingR] = (-20);
	//motor[wingL] = (20);
	//motor[wingChain] = -20;

	startTask(holdLifterPos);
	//drive forward
	driveRightLeft(-127,127);
	wait1Msec(1500);
	motor[clawL] = 0;
	motor[clawR] = 0;
	stopDrive();
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
		while(SensorValue[sonarLeft] < 41){
			if(time1[T1] > 1700)
				break;
		}
	}else {
		while(SensorValue[sonarRight] < 41){
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
	driveRightLeft(-120, 90)
	resetMotorEncoder(wheelFR);
	//push wings down
	const int WING_SPEED = 60;
	motor[wingR] = WING_SPEED;
	motor[wingL] = -WING_SPEED;
	motor[wingChain] = WING_SPEED;
	if(isRight){
		motor[clawL] = -20;
	} else {
		motor[clawR] = -40;
	}
	while(abs(getMotorEncoder(wheelFR)) < 1700) {
	}
	stopDrive();
	wait1Msec(60);
	driveRightLeft(-100,60);
	resetMotorEncoder(wheelBR);
	motor[wingR] = WING_SPEED;
	motor[wingL] = -WING_SPEED;
	motor[wingChain] = WING_SPEED;
	while(abs(getMotorEncoder(wheelFR)) < 2200) {}
	stopDrive();
	motor[clawR] = 127;
	motor[clawL] = -127;
	wait1Msec(1100);

	funcLifterUp(true);
	if(isRight) {
		turn(-finalTurnAngle - 90, 40);
	} else {
		turn(finalTurnAngle + 90, 40);
	}
	driveRightLeft(-127,120);
	wait1Msec(2000 / cosDegrees(finalTurnAngle));

	wait1Msec(200);

	//release stuff
	motor[clawR] = -120;
	motor[clawL] = 120;
	wait1Msec(500);
	motor[clawR] = 0;
	motor[clawL] = 0;	//go backward, lower lifter, and go forward
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

	startTask(holdLifterPos);
	//drive forward
	driveRightLeft(-127,127);
	wait1Msec(1500);
	motor[clawL] = 0;
	motor[clawR] = 0;
	stopDrive();


	stopDrive();
	stopTask(holdLifterPos);
	knockRemainingStars();
}


void backAutonomous2() {
	resetMotorEncoder(wheelFR);
	driveRightLeft(50, -50)
	while(abs(getMotorEncoder(wheelFR)) < 200) {}
	stopDrive();
	clawPreLaunch();
	launchStar();
	drive(0, -110);

	//wait till 30 cm from wall
	clearTimer(T1);
	//30 cm for competition field
	if(isRight) {
		while(SensorValue[sonarLeft] < 30){
			if(time1[T1] > 1700)
				break;
		}
	}
	stopDrive();
	initLeftArm();

	//if(isRight) {
		drive(0,110);
		while(SensorValue[sonarLeft] > 25){
			if(time1[T1] > 1700)
				break;
		}
	//}
	stopDrive();

	driveRightLeft(-100, 100);
	//while(abs(SensorValue(sonarRight)) > 30) {}
	resetMotorEncoder(wheelFL);
	while(abs(getMotorEncoder(wheelFL)) < 3000){}
	stopDrive();

	motor[clawL] = -120;
	if(isRight) {
		drive(0,110);
		int speed = 0;
		while(SensorValue[sonarLeft] > 22){
			if(time1[T1] > 1700)
				break;
		}
	}
	turn(-110, 80)
	driveRightLeft(-100,100);
	resetMotorEncoder(wheelFL);;
	while(abs(getMotorEncoder(wheelFL)) < 200){}
	stopDrive();
	motor[clawR] = 120;
	wait1Msec(2000);
	funcLifterUp(false);
	resetMotorEncoder(wheelFL);
	int speed = 0;
	while(abs(getMotorEncoder(wheelFL)) < 1650){
		speed = min(120, speed + 5);
		driveRightLeft(-speed, speed);
		wait1Msec(50);
	}
	stopDrive();
	motor[clawR] = -50;
	motor[clawL] = 50;

	wait1Msec(300);

	motor[clawR] = 0;
	motor[clawL] = 0;

	knockRemainingStars();
}

void initLeftArm() {

	while(SensorValue[lifterPot] > 2600)	{
		motor[wingR] = -80;
		motor[wingL] = 80;
		motor[wingChain] = -80;
	}
	motor[wingR] = -0;
	motor[wingL] = 0;
	motor[wingChain] = -0;
	startTask(holdLifterPos);

	motor[clawL] = -120;
	while(SensorValue[leftClaw] > 2300) {}
	motor[clawL] = 0;
	stopTask(holdLifterPos);
	motor[wingR] = 50;
	motor[wingL] = -50;
	motor[wingChain] = 50;

	motor[wingR] = 100;
	motor[wingL] = -100;
	motor[wingChain] = 100;

	wait1Msec(350);
	motor[wingR] = 0;
	motor[wingL] = 0;
	motor[wingChain] = 0;
}
