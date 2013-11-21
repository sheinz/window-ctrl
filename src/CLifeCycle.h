/*
 * CLifeCycle.h
 *
 *  Created on: Nov 20, 2013
 *      Author: yura
 */

#ifndef __CLIFECYCLE_H__
#define __CLIFECYCLE_H__

#include "CKeyboard.h"
#include "CKeyHandler.h"
#include "CTempController.h"
#include "CTempProvider.h"


class CLifeCycle
{
public:
   CLifeCycle();
   virtual ~CLifeCycle() {};

   void init();

   void process();

private:

   CTempController mTempController;
   CTempProvider mTempProvider;
   CKeyHandler mKeyHandler;
   CKeyboard mKeyboard;

};

#endif   // __CLIFECYCLE_H__
