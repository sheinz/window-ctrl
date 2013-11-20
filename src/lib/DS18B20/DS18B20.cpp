#include "DS18B20.h"


#define DS18B20_CMD_START_CONVERSION  	0x44
#define DS18B20_CMD_READ_SCRATCHPAD		0xBE
#define DS18B20_CMD_SKIP_ADDR			0xCC


DS18B20::DS18B20(byte pinNumber)
	: mNumberOfFoundSensors(0)
	, mOW(pinNumber)
{
}

// ----------------------------------------------------------------------------

byte DS18B20::search(void)
{
	mNumberOfFoundSensors = 0;
	mOW.reset_search();

	while (mOW.search(mAddrList[mNumberOfFoundSensors]) &&
			mNumberOfFoundSensors < MAX_NUMBER_OF_SENSORS)
	{
		mNumberOfFoundSensors++;
	}

	return mNumberOfFoundSensors;
}

// ----------------------------------------------------------------------------

void DS18B20::startMeasurement(byte sensorIndex)
{
	if (sensorIndex >= mNumberOfFoundSensors)
		return;

	mOW.reset();
	mOW.select(mAddrList[sensorIndex]);
	mOW.write(DS18B20_CMD_START_CONVERSION);
}

// ----------------------------------------------------------------------------

void DS18B20::startMeasurementAll(void)
{
	mOW.reset();
	mOW.skip();
	mOW.write(DS18B20_CMD_START_CONVERSION);
}

// ----------------------------------------------------------------------------

float DS18B20::getTemperature(byte sensorIndex)
{
	float temp;

	if (sensorIndex >= mNumberOfFoundSensors)
		return -200;

	mOW.reset();
	mOW.select(mAddrList[sensorIndex]);
	mOW.write(DS18B20_CMD_READ_SCRATCHPAD);

	for (byte i = 0; i < 9; i++)
	{
		mDataBuff[i] = mOW.read();
	}

	if (OneWire::crc8(mDataBuff, 8) != mDataBuff[8])
		return -200;		// crc is not valid

	int raw = mDataBuff[0];
	raw |= ((word)mDataBuff[1] << 8);

	temp = (float)raw / 16;

	return temp;
}

// ----------------------------------------------------------------------------

byte DS18B20::getNumberOfSensors(void)
{
	return mNumberOfFoundSensors;
}

// ----------------------------------------------------------------------------

float DS18B20::startAndWaitForTemperature(byte sensorIndex)
{
	startMeasurement(sensorIndex);
	delay(750);
	return getTemperature(sensorIndex);
}

