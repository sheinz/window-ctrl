/*
 * CIRrecever.cpp
 *
 *  Created on: Nov 22, 2013
 *      Author: yura
 */

#include "CIRreceiver.h"
#include "CMessage.h"
#include "CDisplay.h"
#include "Arduino.h"



CIRreceiver::CIRreceiver(IIrCmdHandler* pCmdHandler)
   : mCmdHandler(pCmdHandler)
   , mIR(48)
{
}

// ----------------------------------------------------------------------------

void CIRreceiver::init()
{
   mIR.blink13(1);
   mIR.enableIRIn();

   CTaskMgr::instance()->Add(this, 100);
}

// ----------------------------------------------------------------------------

void CIRreceiver::onExecute()
{
   if (mIR.decode(&mResult))
   {
      Serial.println(mResult.value, HEX);
      Serial.println(mResult.value>>16, HEX);

      if (mResult.value & 0xFF0000 == 0xFF0000)
      {
         uint16_t cmd = (uint16_t)(mResult.value & 0xFFFF);
         mCmdHandler->onIrCmd(cmd);
      }

      mIR.resume(); // Receive the next value
   }
}
