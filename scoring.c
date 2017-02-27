bool holdingPos;
task wings(){
	holdingPos = false;
	while(1){
  	if(vexRT[Btn8R]) {
				if(!holdingPos) {
					startTask(holdLifterPos);
					holdingPos = true;
				}
		}
		else if(vexRT(Btn8U)) {
			//if(holdingPos) {
				stopTask(holdLifterPos);
				holdingPos = false;
			//}
			motor[wingL] = 127;
			motor[wingR] = -127;
		} else if(vexRT(Btn8D)) {
			//if(holdingPos) {
				stopTask(holdLifterPos);
				holdingPos = false;
			//}
			motor[wingL] = -60;
			motor[wingR] = 60;
		} else {
			if(!holdingPos) {
				motor[wingL] = 0;
				motor[wingR] = 0;
			}
		}
	}
}

//claw operations
task grabber(){
	while(1){
		//opening and closing
		if(vexRT(Btn5U)){
			motor[clawL] = -127;
		} else if(vexRT(Btn5D)) {
			motor[clawL] = 127;
		} else {
			motor[clawL] = 0;
		}
		if(vexRT(Btn6U)) {
			motor[clawR] = 127;
		} else if(vexRT(Btn6D)) {
			motor[clawR] = -127;
		} else {
			motor[clawR] = 0;
		}
		//throttling: try to launch objects that the robot is holding into
		//the far zone
		if(vexRT(Btn7R)) {
			stopTask(expDrive);
			setDriveMotorSpeeds(127);
			wait1Msec(600);
			motor[clawL] = 127;
			motor[clawR] = -127;
			wait1Msec(100);
			motor[clawL] = 0;
			motor[clawR] = 0;
			setDriveMotorSpeeds(0);
			startTask(expDrive);
		}

	}
}

void setLifterMotorValue(int s) {
		motor[wingL] = s;
		motor[wingR] = -s;
}

task partnerRobotLifter() {
	//controls the robot lifter with partner's controller
	while (true) {
		//make sure stage 1 is activated before stage 2
		bool stageOneActivated = false;

		//first stage of launching the robot lifter
		if ( vexRT(Btn7UXmtr2) && vexRT(Btn7U) ) {
			motor[robotLifterArm] = 100;
			wait1Msec(0);
			stageOneActivated = true;
			//motor[robotLifterL] = 100;
		} else if(vexRT(Btn7DXmtr2) && vexRT(Btn7D)) {
			motor[robotLifterArm] = -100;
			wait1Msec(0);
			stageOneActivated = true;
		}

		//second stage of launching the robot lifter
		if (vexRT(Btn7LXmtr2) && vexRT(Btn7L) && stageOneActivated) {
			motor[takeAStepBack] = 100;
		} else {
			motor[takeAStepBack] = 0;
		}
	}
}
