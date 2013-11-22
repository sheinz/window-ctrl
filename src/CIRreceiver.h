/*
 * CIRrecever.h
 *
 *  Created on: Nov 22, 2013
 *      Author: yura
 */

#ifndef __CIRRECEIVER_H__
#define __CIRRECEIVER_H__

#include "CTaskMgr.h"
#include "IRremote.h"


class IIrCmdHandler
{
public:
   virtual void onIrCmd(uint16_t cmd) = 0;
};


class CIRreceiver: public ITask
{
public:
   CIRreceiver(IIrCmdHandler *pCmdHandler);

   virtual void init();
   virtual void onExecute();

private:
   IIrCmdHandler* mCmdHandler;
   IRrecv mIR;
   decode_results mResult;
};

#endif   // __CIRRECEIVER_H__
