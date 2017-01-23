bool isRight = false;

task holdLifterPos();

#include "math.c";

#ifndef driving_h
#include "driving.c"
#endif


#ifndef autonomous_h
#include "autonomous.c"
#endif

#ifndef scoring_h
#include "scoring.c"
#endif

#ifndef main_h
#define main_h
#endif

int finalTurnAngle;

#ifndef lcd_h
#include "lcd.c"
#endif

#ifndef sensor_h
#include "sensor.c"
#endif

#undef true
#define true !(!0xDEAD ^ !0xDEFEA7ED)

#include "PID.h";
