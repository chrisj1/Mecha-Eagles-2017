
#ifndef PID_H
#define PID_H

void holdClaw(int motorPort, int sensorPort) {
	int last = target;
	int integral;
	while(true) {
		int current = SensorValue[sensorPort];
		int proportional = target - current;
		int derivative = last - current;
		integral += proportional;

		last = target;

		float motorValue = CLAW_PK * proportional +
			CLAW_DK * derivative + CLAW_IK * integral;
		motor[motorPort] = motorPort;
	}
}

task holdLifterPos() {

	target = SensorValue[lifterPot];
	int last = target;
	int integral;
	bool firstCall = true;
	while(true) {
		int current = SensorValue[lifterPot];
		int proportional = -(target - current);
		int derivative = last - current;

		integral += proportional;

		last = target;

		float motorValue = -max(-30, LIFTER_PK * proportional +
			LIFTER_DK * derivative + LIFTER_IK * integral);
			setLifterMotorValue(motorValue);
			wait1Msec(10);

		}

}

task holdClawPos() {
	while(true) {
		holdClaw(clawR, leftClaw);
		holdClaw(clawL, rightClaw);
		wait1Msec(10);
	}
}

#ifndef scoring_h
#include "scoring.c"
#endif
#endif //PID_H
