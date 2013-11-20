/*
 * CDisplay.h
 *
 *  Created on: Nov 20, 2013
 *      Author: yura
 */

#ifndef __CDISPLAY_H__
#define __CDISPLAY_H__

#include "LiquidCrystal.h"


class CDisplay: public LiquidCrystal
{
public:
   static CDisplay* instance();

   void back_light(bool on);

private:
   CDisplay();
   //virtual ~CDisplay() {};
   // no destructor due to interesting error
   // "undefined reference to `atexit'"
};

#endif   // __CDISPLAY_H__
