#ifndef __CKEYHANDLER_H__
#define __CKEYHANDLER_H__


#include "CKeyboard.h"
#include "CTaskMgr.h"
#include "CTempController.h"
#include "CIRreceiver.h"


class CKeyHandler : public IKeyHandler, public ITask, public IIrCmdHandler
{
public:
   CKeyHandler(CTempController* pTempCtrl);

   virtual ~CKeyHandler(void) {};

   virtual void onKey(CKeyboard::EKey key);

   virtual void onKeyLong(CKeyboard::EKey key);

   virtual void init(void);

   virtual void onExecute(void);

   virtual void onIrCmd(uint16_t cmd);

private:
   void display();

   bool checkWindowUnlocked();

   CTempController* mTempCtrl;
   CIRreceiver mIRreceiver;

   bool mCalibration;
   bool mLocked;
};

#endif // __CKEYHANDLER_H__
