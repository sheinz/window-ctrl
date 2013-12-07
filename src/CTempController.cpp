/*
 * CTempController.cpp
 *
 *  Created on: Nov 20, 2013
 *      Author: yura
 */

#include "CTempController.h"
#include "Arduino.h"
#include "CWindow.h"
#include "CMessage.h"
#include <avr/eeprom.h>
#include <math.h>

#define WINDOW_DEFAULT_STATE     10     // percent open
#define WINDOW_FINE_STEP         5
#define WINDOW_COARSE_STEP       20

// The temperature difference that triggers action
#define TEMP_FINE_DIFFERENCE     0.5
#define TEMP_COARSE_DIFFERENCE   2.0

#define REFRESH_ROOM_TIME        (1000UL * 60 * 15)
#define WARM_UP_ROOM_TIME        (1000UL * 60 * 30)


// ----------------------------------------------------------------------------

EEMEM float eeprom_set_temp = 25.0;

// ----------------------------------------------------------------------------

CTempController::CTempController()
   : mSetTemp(25)
   , mInTemp(0)
   , mOutTemp(0)
   , mSkipNextFineUpdate(false)
   , mEnable(true)
   , mWindowState(0)
{
}

// ----------------------------------------------------------------------------

void CTempController::init()
{
   mSetTemp = eeprom_read_float(&eeprom_set_temp);

   if (isnanf(mSetTemp) ||
       isinff(mSetTemp) ||
       mSetTemp < 10.0 ||
       mSetTemp > 40.0)
   {
      mSetTemp = 25;
   }

   CWindow::instance()->set(WINDOW_DEFAULT_STATE);
}

// ----------------------------------------------------------------------------

void CTempController::onExecute()
{
   CTaskMgr::instance()->Remove(this);
   CWindow::instance()->set(mWindowState);
   mEnable = true;

   SHOW_MESSAGE("Finished", 5);
}

// ----------------------------------------------------------------------------

void CTempController::changeWindow(bool open, uint8_t value)
{
   uint8_t state = CWindow::instance()->get();

   SHOW_MESSAGE(open ? "Opening " : "Closing ", 5);

   if (open)
   {
      state += value;
      if (state > 100)
      {
         state = 100;
      }
   }
   else
   {
      if (state < value)
      {
         state = 0;
      }
      else
      {
         state -= value;
      }
   }

   CWindow::instance()->set(state);
}
// ----------------------------------------------------------------------------

void CTempController::onCoarseTempUpdate(float in_temp, float out_temp)
{
   mInTemp = in_temp;
   mOutTemp = out_temp;
   float difference;

   if (!mEnable)
      return;

   if (mInTemp > mSetTemp)
   {
      difference = mInTemp - mSetTemp;
      if (difference > TEMP_COARSE_DIFFERENCE)
      {
         changeWindow(true, WINDOW_COARSE_STEP);
         // window has just changed no point in fine tuning
         mSkipNextFineUpdate = true;
      }
   }
   else
   {
      difference = mSetTemp - mInTemp;
      if (difference > TEMP_COARSE_DIFFERENCE)
      {
         changeWindow(false, WINDOW_COARSE_STEP);
         mSkipNextFineUpdate = true;
      }
   }
}

// ----------------------------------------------------------------------------

void CTempController::onFineTempUpdate(float in_temp, float out_temp)
{
   if (!mEnable)
      return;

   if (mSkipNextFineUpdate)
   {
      mSkipNextFineUpdate = false;
      return;
   }

   float difference;

   if (in_temp > mSetTemp)
   {
      difference = in_temp - mSetTemp;
      if (difference > TEMP_FINE_DIFFERENCE)
      {
         changeWindow(true, WINDOW_FINE_STEP);
      }
   }
   else
   {
      difference = mSetTemp - in_temp;
      if (difference > TEMP_FINE_DIFFERENCE)
      {
         changeWindow(false, WINDOW_FINE_STEP);
      }
   }
}

// ----------------------------------------------------------------------------

void CTempController::refreshRoom()
{
   if (!mEnable)
      return;

   mWindowState = CWindow::instance()->get();

   mEnable = false;
   CTaskMgr::instance()->Add(this, REFRESH_ROOM_TIME);
   CWindow::instance()->set(100);
}

// ----------------------------------------------------------------------------

void CTempController::warmUpRoom()
{
   if (!mEnable)
      return;

   mWindowState = CWindow::instance()->get();

   mEnable = false;
   CTaskMgr::instance()->Add(this, WARM_UP_ROOM_TIME);
   CWindow::instance()->set(0);
}

// ----------------------------------------------------------------------------

void CTempController::setTemp(float temperature)
{
   mSetTemp = temperature;

   // it will not actually write unless the value is changed
   eeprom_update_float(&eeprom_set_temp, mSetTemp);
}

// ----------------------------------------------------------------------------

float CTempController::getTemp()
{
   return mSetTemp;
}

// ----------------------------------------------------------------------------

float CTempController::getInTemp()
{
   return mInTemp;
}

// ----------------------------------------------------------------------------

float CTempController::getOutTemp()
{
   return mOutTemp;
}
