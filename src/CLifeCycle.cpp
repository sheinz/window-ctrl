/*
 * CLifeCycle.cpp
 *
 *  Created on: Nov 20, 2013
 *      Author: yura
 */

#include "CLifeCycle.h"
#include "CTaskMgr.h"
#include "CBeep.h"

CLifeCycle::CLifeCycle()
   : mKeyHandler()
   , mKeyboard(&mKeyHandler)
   , mTempController()
   , mTempProvider(&mTempController)
{
}

// ----------------------------------------------------------------------------

void CLifeCycle::init()
{
   CTaskMgr::instance()->init();

   mKeyboard.init();
   mKeyHandler.init();
   mTempController.init();
   mTempProvider.init();

   CWindow::instance()->init();
   CBeep::instance()->init();
}

// ----------------------------------------------------------------------------

void CLifeCycle::process()
{
   CTaskMgr::instance()->processTasks();
}
