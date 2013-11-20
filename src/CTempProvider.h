/*
 * CTempProvider.h
 *
 *  Created on: Nov 20, 2013
 *      Author:
 */

#ifndef __CTEMPPROVIDER_H__
#define __CTEMPPROVIDER_H__

#include "CTaskMgr.h"

class ITempHandler
{
public:
   virtual ~ITempHandler() {}

   virtual void onRoughTempUpdate(float in_temp, float out_temp) = 0;
   virtual void onFineTempUpdate(float in_temp, float out_temp) = 0;
};


class CTempProvider : public ITask
{
public:
   CTempProvider(ITempHandler* pTempHandler);
   virtual ~CTempProvider() {};

   void init();

   virtual void onExecute();

private:
   ITempHandler* mTempHandler;

};

#endif // __CTEMPPROVIDER_H__
