#ifndef driving_h
	#define driving_h
	const int powerOffset = 30;
	float toggleSpeed = 1;

	const int THRESHOLD = 30;
#endif

task expDrive();
float joyStickExp(int joystick);
task expDrive();
void driveStraightForDistance(int distance);
