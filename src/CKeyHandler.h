#ifndef __CKEYHANDLER_H__
#define __CKEYHANDLER_H__


#include "CKeyboard.h"
#include "CTaskMgr.h"
#include "CTempController.h"


class CKeyHandler : public IKeyHandler, public ITask
{
public:
   CKeyHandler(CTempController* pTempCtrl);

   virtual ~CKeyHandler(void) {};

   virtual void onKey(CKeyboard::EKey key);

   virtual void onKeyLong(CKeyboard::EKey key);

   virtual void init(void);

   virtual void onExecute(void);

private:
   void display();

   CTempController* mTempCtrl;
};

#endif // __CKEYHANDLER_H__
