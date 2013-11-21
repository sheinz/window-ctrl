/*
 * CTempProvider.cpp
 *
 *  Created on: Nov 20, 2013
 *      Author: yura
 */

#include "CTempProvider.h"
#include "DS18B20.h"
#include "Arduino.h"

#define INDOOR_TEMP_SENSOR       0
#define OUTDOOR_TEMP_SENSOR      1

#define COARSE_POINTS_NUMBER     10
#define FINE_POINTS_NUMBER       20


CTempProvider::CTempProvider(ITempHandler* pTempHandler)
   : mTempHandler(pTempHandler)
   , mCoarseSum(0)
   , mCoarsePointsNum(0)
   , mFineSum(0)
   , mFinePointsNum(0)
   , mOutTemp(0)
   , mTempSensors(50)
{
}

// ----------------------------------------------------------------------------

void CTempProvider::init()
{
   uint8_t sensors_number = mTempSensors.search();

   if (sensors_number != 2)
   {
      Serial.println("Two DS18B20 sensors not found");
   }
   else
   {
      //CTaskMgr::instance()->Add(this, 60000);
      CTaskMgr::instance()->Add(this, 6000);
      mTempSensors.startMeasurementAll();
   }
}

// ----------------------------------------------------------------------------

void CTempProvider::onCoarsePoint(float temp)
{
   mFineSum += temp;
   mFinePointsNum++;

   if (mFinePointsNum >= FINE_POINTS_NUMBER)
   {
      float fine_temp = mFineSum / mFinePointsNum;
      mFineSum = 0;
      mFinePointsNum = 0;
      mTempHandler->onFineTempUpdate(fine_temp, mOutTemp);
   }
}

// ----------------------------------------------------------------------------

// executes each minute
void CTempProvider::onExecute()
{
   mOutTemp = mTempSensors.getTemperature(OUTDOOR_TEMP_SENSOR);
   float raw_in_temp = mTempSensors.getTemperature(INDOOR_TEMP_SENSOR);

   mCoarseSum += raw_in_temp;
   mCoarsePointsNum++;

   if (mCoarsePointsNum >= COARSE_POINTS_NUMBER)
   {
      float coarse_temp = mCoarseSum / mCoarsePointsNum;
      mCoarseSum = 0;
      mCoarsePointsNum = 0;
      mTempHandler->onCoarseTempUpdate(coarse_temp, mOutTemp);
      onCoarsePoint(coarse_temp);
   }

   mTempSensors.startMeasurementAll();
}
