#include "backWallAutonomous.h"

void initArm();

void wingsOutDiff() {
		if (isRight) {
			motor[clawL] = -60;
			motor[clawR] = 60;
			wait1Msec(500);
			motor[clawL] = 0;
			motor[clawR] = 0;
		} else {
			motor[clawL] = -60;
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
	wait1Msec(400);
	//lowser the lifter and extend the claws
	stopDrive();
	motor[clawR] = -50;
	motor[clawL] = 50;
	wait1Msec(600);
	motor[clawR] = 0;
	motor[clawL] = 0;
	stopTask(holdLifterPos);
	//stop holding pos
	while(SensorValue[lifterPot] < 2300) {
		motor[wingR] = (60);
		motor[wingL] = (-60);
	}

	startTask(holdLifterPos);
	//drive forward
	driveRightLeft(-127,127);
	wait1Msec(600);
	motor[clawL] = 0;
	motor[clawR] = 0;
	stopDrive();
}

task wingsOutAsync {
	wingsOutDiff();
}

//****deprecated****
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
	wait1Msec(1000);
	//close right claw while driving
	if(isRight) {
		motor[clawR] = 30;
	} else {
		motor[clawL] = 30;
	}
	//move forwards to collect stars and cubes
	driveRightLeft(-120, 90);
	resetMotorEncoder(wheelFR);
	//push wings down
	const int WING_SPEED = 60;
	motor[wingR] = WING_SPEED;
	motor[wingL] = -WING_SPEED;
	if(isRight){
		motor[clawL] = -20;
	} else {
		motor[clawR] = -20;
	}
	while(abs(getMotorEncoder(wheelFR)) < 1700) {
	}
	stopDrive();
	wait1Msec(60);
	driveRightLeft(-100,60);
	resetMotorEncoder(wheelBR);
	motor[wingR] = WING_SPEED;
	motor[wingL] = -WING_SPEED;
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
	}

	motor[wingR] = (-20);
	motor[wingL] = (20);

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
	//inital preparation - extends claws
	clawPreLaunch();
	launchStar();
	turn(-35, 50);


	driveRightLeft(-70, 70);
	resetMotorEncoder(wheelBL);
	while(abs(getMotorEncoder(wheelBL)) < 190){}
	stopDrive();
	motor[clawL] = -120;
	while(SensorValue[leftClaw] > 1600){}
	motor[clawL] = 0;
	turn(15, 40);


	//drive until we get all three stars
	motor[clawR] = -20;
	driveRightLeft(-80,80);
	while(abs(getMotorEncoder(wheelBL)) < 1260){}
	stopDrive();

	//gets the cube and turns towards the fence
	motor[clawR] = 0;
	motor[clawL] = -100;
	turn(-90, 100);
	motor[clawR] = 120;
	wait1Msec(2000);

	//brings up the cube
	funcLifterUp(true);
	wait1Msec(200);

	turn(finalTurnAngle, 60);

	//goes towards the fence with increasing speed
	for(int speed = 0; speed < 120; speed++) {
			driveRightLeft(-speed, speed);
			wait1Msec(20);
	}
	wait1Msec(750/cosDegrees(finalTurnAngle));
	stopDrive();

	//releases the claws
	motor[clawL] = 50;
	motor[clawR] = -50;
	wait1Msec(700);

	//stops
	motor[clawL] = 0;
	motor[clawR] = 0;
	//knocks off the rest of the stars on the fence
	knockRemainingStars();
}

void initArm() {

	while(SensorValue[lifterPot] < 900)	{
		motor[wingR] = -100;
		motor[wingL] = 100;
	}
	motor[wingR] = -0;
	motor[wingL] = 0;
	startTask(holdLifterPos);

	if(isRight) {
		motor[clawL] = -120;
		while(SensorValue[leftClaw] > 2200) {}
		motor[clawL] = 0;
	} else {
		motor[clawR] = 70;
		while(SensorValue[rightClaw] > 1200) {}
		motor[clawR] = 0;
	}

	stopTask(holdLifterPos);

	motor[wingR] = 100;
	motor[wingL] = -100;

	wait1Msec(350);
	motor[wingR] = 0;
	motor[wingL] = 0;
}

void backStarsAuton() {
	clawPreLaunch();
	launchStar();

	driveRightLeft(-70,70);

	resetMotorEncoder(wheelBL);
	while(abs(getMotorEncoder(wheelBL)) < 150){}
	stopDrive();

	turn(15, 50);
	motor[clawR] = 120;
	while(SensorValue[rightClaw] > 100) {}

	wait1Msec(500);
	//Hold lifter down
	//motor[wingL] = -50;
	motor[wingR] = 50;

	turn (67, 50);

	motor[clawR] = 0;

	driveRightLeft(80, -80);
	wait1Msec(200);
	driveRightLeft(0,0);
	motor[clawL] = -120;
	while(SensorValue[leftClaw] > 2300) {}
	motor[clawL] = 0;

	turn(24, 60);

	motor[clawL] = -120;
	while(SensorValue[leftClaw] > 2300) {}
	motor[clawL] = 0;
	driveRightLeft(-80,80);

	resetMotorEncoder(wheelBL);
	while(abs(getMotorEncoder(wheelBL)) < 1700){}
	stopDrive();

	driveRightLeft(-100,-100);
	wait1Msec(400);
	driveRightLeft(0,0);

	motor[clawR] = -80;
	wait1Msec(200);

	motor[clawL] = -100;

	driveRightLeft(-100,100);
	resetMotorEncoder(wheelBL);
	while(abs(getMotorEncoder(wheelBL)) < 650){}
	stopDrive();

	motor[clawR] = 80;
	motor[clawL] = -80;

	wait1Msec(1000);

	driveRightLeft(100,-100);

	resetMotorEncoder(wheelBL);
	while(abs(getMotorEncoder(wheelBL)) < 200){}
	stopDrive();

	funcLifterUp(true, 1900);
	turn(-100, 70);

	driveRightLeft(-110,110);

	clearTimer(T1);
	while(SensorValue[sonarFence] > 20 || timer1 > 2000){}
	motor[clawR] = -80;
	motor[clawL] = 80;
	stopDrive();

	wait1Msec(1000);

	motor[clawR] = 0;
	motor[clawL] = 0;
}
