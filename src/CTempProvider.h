/*
 * CTempProvider.h
 *
 *  Created on: Nov 20, 2013
 *      Author:
 */

#ifndef __CTEMPPROVIDER_H__
#define __CTEMPPROVIDER_H__

#include "CTaskMgr.h"
#include "DS18B20.h"

class ITempHandler
{
public:
   virtual ~ITempHandler() {}

   virtual void onCoarseTempUpdate(float in_temp, float out_temp) = 0;
   virtual void onFineTempUpdate(float in_temp, float out_temp) = 0;
};


// The main propose of the class is to filter the indoor temperature.
// Provide smooth indoor temperature in two degrees of smoothness (coarse and fine)
// Coarse temperature is updated relatively quick and intended for radical actions.
// Fine temperature is updated seldom and intended for fine tuning.
class CTempProvider : public ITask
{
public:
   CTempProvider(ITempHandler* pTempHandler);
   virtual ~CTempProvider() {};

   void init();

   virtual void onExecute();

private:
   void onCoarsePoint(float temp);

   ITempHandler* mTempHandler;

   // The sum of coarse temperature measures
   float mCoarseSum;
   // The number of points that were added to mCoarseSum
   uint8_t mCoarsePointsNum;

   // The sum of fine temperature measures
   float mFineSum;
   // the number of points that were added to mFineSum
   uint8_t mFinePointsNum;

   // not filtered outdoor temperature
   float mOutTemp;

   DS18B20 mTempSensors;
};

#endif // __CTEMPPROVIDER_H__
