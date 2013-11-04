#ifndef __CKEYHANDLER_H__
#define __CKEYHANDLER_H__


#include "CKeyboard.h"
#include "CWindow.h"
#include "CTaskMgr.h"
#include "LiquidCrystal.h"


class CKeyHandler : public IKeyHandler, public ITask
{
public:
   CKeyHandler(CWindow *pWindow, LiquidCrystal *pLcd);

   virtual ~CKeyHandler(void) {};

   virtual void onKey(CKeyboard::EKey key);

   virtual void onKeyLong(CKeyboard::EKey key);

   virtual void onExecute(void);

private:

   CWindow *mpWindow;
   LiquidCrystal *mpLcd;


   // just for test
   uint8_t m_window_state;
   uint8_t m_step;
};

#endif // __CKEYHANDLER_H__
