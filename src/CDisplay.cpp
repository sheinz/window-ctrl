/*
 * CDisplay.cpp
 *
 *  Created on: Nov 20, 2013
 *      Author:
 */

#include "CDisplay.h"
#include "Arduino.h"

#define LCD_BACKLIGHT_PIN  44

// ----------------------------------------------------------------------------

CDisplay* CDisplay::instance()
{
   static CDisplay display;
   return &display;
}

// ----------------------------------------------------------------------------

CDisplay::CDisplay()
   : LiquidCrystal(22, 24, 26, 28, 30, 32, 34)
{
   pinMode(LCD_BACKLIGHT_PIN, OUTPUT);
   digitalWrite(LCD_BACKLIGHT_PIN, HIGH);

   begin(16, 2);
}

// ----------------------------------------------------------------------------

void CDisplay::back_light(bool on)
{
   digitalWrite(LCD_BACKLIGHT_PIN, on);
}
