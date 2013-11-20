#ifndef __DS18B20_H__
#define __DS18B20_H__

#include <Arduino.h>
#include "OneWire.h"

class DS18B20
{
public:

	static const byte MAX_NUMBER_OF_SENSORS = 8;

	DS18B20(byte pinNumber);

	// Returns number of found sensors
	byte search(void);

	byte getNumberOfSensors(void);

	void startMeasurement(byte sensorIndex);

	void startMeasurementAll(void);

	float getTemperature(byte sensorIndex);

	float startAndWaitForTemperature(byte sensorIndex);


private:
	byte mAddrList[MAX_NUMBER_OF_SENSORS][8];
	byte mNumberOfFoundSensors;
	byte mDataBuff[9];

	OneWire mOW;

};


#endif // __DS18B20_H__
