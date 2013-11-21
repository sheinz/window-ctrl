/*
 * CTempController.h
 *
 *  Created on: Nov 20, 2013
 *      Author: yura
 */

#ifndef __CTEMPCONTROLLER_H__
#define __CTEMPCONTROLLER_H__

#include "CTaskMgr.h"
#include "CTempProvider.h"

class CTempController: public ITask, public ITempHandler
{
public:
   CTempController();
   virtual ~CTempController() {};

   virtual void init();
   virtual void onExecute();

   virtual void onCoarseTempUpdate(float in_temp, float out_temp);
   virtual void onFineTempUpdate(float in_temp, float out_temp);

   void sleep();
   void resume();

   void setTemp(float temperature);
   float getTemp();

   float getInTemp();
   float getOutTemp();

private:
   void changeWindow(bool open, uint8_t value);

   float mSetTemp;
   float mOutTemp;
   float mInTemp;
   bool mSkipNextFineUpdate;
};

#endif   // __CTEMPCONTROLLER_H__
