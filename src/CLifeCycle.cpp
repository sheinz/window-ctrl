/*
 * CLifeCycle.cpp
 *
 *  Created on: Nov 20, 2013
 *      Author: yura
 */

#include "Arduino.h"
#include "CLifeCycle.h"
#include "CTaskMgr.h"
#include "CBeep.h"
#include "CWindow.h"
#include "CMessage.h"

CLifeCycle::CLifeCycle()
   : mTempController()
   , mTempProvider(&mTempController)
   , mKeyHandler(&mTempController)
   , mKeyboard(&mKeyHandler)
{
}

// ----------------------------------------------------------------------------

void CLifeCycle::init()
{
   Serial.begin(9600);

   CTaskMgr::instance()->init();
   CWindow::instance()->init();
   CBeep::instance()->init();

   mTempController.init();
   mTempProvider.init();
   mKeyboard.init();
   mKeyHandler.init();

   SHOW_MESSAGE("Hello window", 2);
}

// ----------------------------------------------------------------------------

void CLifeCycle::process()
{
   CTaskMgr::instance()->processTasks();
}
