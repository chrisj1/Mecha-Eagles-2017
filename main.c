#pragma config(I2C_Usage, I2C1, i2cSensors)
#pragma config(Sensor, in1,    ,               sensorPotentiometer)
#pragma config(Sensor, in2,    lifterPot,      sensorPotentiometer)
#pragma config(Sensor, in3,    leftClaw,       sensorPotentiometer)
#pragma config(Sensor, in4,    rightClaw,      sensorPotentiometer)
#pragma config(Sensor, in5,    powerExpander,  sensorAnalog)
#pragma config(Sensor, in7,    gyro,           sensorGyro)
#pragma config(Sensor, in8,    ,               sensorLineFollower)
#pragma config(Sensor, dgtl7,  sonarFence,     sensorSONAR_cm)
#pragma config(Sensor, dgtl9,  sonarRight,     sensorSONAR_cm)
#pragma config(Sensor, dgtl11, sonarLeft,      sensorSONAR_cm)
#pragma config(Sensor, I2C_1,  ,               sensorQuadEncoderOnI2CPort,    , AutoAssign )
#pragma config(Sensor, I2C_2,  ,               sensorQuadEncoderOnI2CPort,    , AutoAssign )
#pragma config(Sensor, I2C_3,  ,               sensorQuadEncoderOnI2CPort,    , AutoAssign )
#pragma config(Sensor, I2C_4,  ,               sensorQuadEncoderOnI2CPort,    , AutoAssign )
#pragma config(Motor,  port1,           clawL,         tmotorVex393_HBridge, openLoop)
#pragma config(Motor,  port2,           wheelFR,       tmotorVex393_MC29, openLoop, encoderPort, I2C_1)
#pragma config(Motor,  port3,           wheelBR,       tmotorVex393_MC29, openLoop, encoderPort, I2C_4)
#pragma config(Motor,  port4,           wheelBL,       tmotorVex393_MC29, openLoop, encoderPort, I2C_3)
#pragma config(Motor,  port5,           wheelFL,       tmotorVex393_MC29, openLoop, encoderPort, I2C_2)
#pragma config(Motor,  port6,           robotLifterArmUp, tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port7,           wingR,         tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port8,           wingChain,     tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port9,           wingL,         tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port10,          clawR,         tmotorVex393_HBridge, openLoop)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

#pragma platform(VEX)
#pragma competitionControl(Competition)
#pragma autonomousDuration(15)
#pragma userControlDuration(120)

int target;
#include "main.h"

#include "Vex_Competition_Includes.c"
int r;
void pre_auton() {
	clearScreen();
	SensorValue[gyro] = 0;
	startTask(flashScreen);
	string prompt = "Final Turn Angle";
	r = askRoutine();
	//r = 4
	wait1Msec(600);
	isRight = askPos();
	wait1Msec(600);
	if(r == 3) {
		finalTurnAngle = promptInt(50, -50, 0, 5, prompt);
	}
	clearScreen();
	stopTask(flashScreen);
	SensorValue[gyro] = 0;
	wait1Msec(2000);
}

task autonomous() {
	resetEncoders();
	clearTimer(T1);
	if(r == 0) {
		startAutonomous();
		while(true) {
			followWall(1);
		}
	}
	else if(r == 1) {
		startAutonomous();
		setDriveMotorSpeeds(100);
		wait1Msec(1100);
		setDriveMotorSpeeds(0);
	}
	else if(r == 2) {
		startWallDrive();
	} else if(r == 3) {
		backAutonomous2();
	} else if(r == 4) {
		backStarsAuton();
	}
	string s;
	sprintf(s, "%f", time1[T1]/1000.0);
	writeDebugStream("autonomous done in: ");
	writeDebugStreamLine(s);
}

task usercontrol() {
	target = SensorValue[lifterPot];
	startTask(holdLifterPos);
	startTask(expDrive);
	startTask(wings);
	startTask(partnerRobotLifter);
	//startTask(lift);
	startTask(grabber);
	while(true) {
		wait1Msec(500);
		string reading;
			//sprintf(reading, "%d", SensorValue[frontLine]);
			writeDebugStreamLine(reading);
	}
}
#ifdef AUTONOMOUS
task main() {
	pre_auton();
	//wait1Msec(3000);
	startTask(autonomous);
	while(true){}
}
#endif
#ifdef TELEOP
task main() {
	//pre_auton();
	startTask(partnerRobotLifter);
	startTask(usercontrol);
	string mainBattery, expanderBattery;
	while(true){
		float mainBatteryLevel = getBatteryLevelVoltage();
		float expanderBatteryLevel = getExpanderBatteryVoltage();
		//Display the Primary Robot battery voltage
		displayLCDString(0, 0, "Primary: ");
		sprintf(mainBattery, "%1.2f%c", mainBatteryLevel,'V'); //Build the value to be displayed
		displayNextLCDString(mainBattery);

		//Display the Backup battery voltage
		displayLCDString(1, 0, "Expander: ");
		sprintf(expanderBattery, "%1.2f%c", getExpanderBatteryVoltage(), 'V');    //Build the value to be displayed
		displayNextLCDString(expanderBattery);

		if(mainBatteryLevel < MIN_BATT_VOLT || expanderBatteryLevel < MIN_BATT_VOLT) {
			startTask(flashScreen);
		}
		wait1Msec(1000);
	}
}
#endif
