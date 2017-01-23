#include "sensor.h"



float getExpanderBatteryVoltage() {
	return (SensorValue[in1])/182.4;
}

float getBatteryLevelVoltage() {
	return nImmediateBatteryLevel/1000.0;
}
