/*
 * CTempController.cpp
 *
 *  Created on: Nov 20, 2013
 *      Author: yura
 */

#include "CTempController.h"
#include "Arduino.h"
#include "CWindow.h"

#define WINDOW_DEFAULT_STATE     10     // percent open
#define WINDOW_FINE_STEP         5
#define WINDOW_COARSE_STEP       20

// The temperature difference that triggers action
#define TEMP_FINE_DIFFERENCE     0.5
#define TEMP_COARSE_DIFFERENCE   3.0


CTempController::CTempController()
   : mSetTemp(25)
   , mInTemp(0)
   , mOutTemp(0)
   , mSkipNextFineUpdate(false)
{
}

// ----------------------------------------------------------------------------

void CTempController::init()
{
   CWindow::instance()->set(WINDOW_DEFAULT_STATE);
}

// ----------------------------------------------------------------------------

void CTempController::onExecute()
{
}

// ----------------------------------------------------------------------------

void CTempController::changeWindow(bool open, uint8_t value)
{
   uint8_t state = CWindow::instance()->get();

   Serial.print("Updating window ");
   Serial.print(open ? "opening " : "closing ");
   Serial.println(value);

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

void CTempController::sleep()
{
}

// ----------------------------------------------------------------------------

void CTempController::resume()
{
}

// ----------------------------------------------------------------------------

void CTempController::setTemp(float temperature)
{
   mSetTemp = temperature;
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
