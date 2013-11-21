#include "CKeyHandler.h"
#include "CBeep.h"
#include "CDisplay.h"


#define TEMP_SET_STEP      0.5

// ----------------------------------------------------------------------------

CKeyHandler::CKeyHandler(CTempController* pTempCtrl)
   : mTempCtrl(pTempCtrl)
{
}

// ----------------------------------------------------------------------------

void CKeyHandler::init(void)
{
   CTaskMgr::instance()->Add(this, 1000);
}

// ----------------------------------------------------------------------------

void CKeyHandler::onKey(CKeyboard::EKey key)
{
   BEEP();

   if (key == CKeyboard::KEY_UP)
   {
      mTempCtrl->setTemp(mTempCtrl->getTemp() + TEMP_SET_STEP);
   }
   if (key == CKeyboard::KEY_DOWN)
   {
      mTempCtrl->setTemp(mTempCtrl->getTemp() - TEMP_SET_STEP);
   }

   display();
}

// ----------------------------------------------------------------------------

void CKeyHandler::onKeyLong(CKeyboard::EKey key)
{
   BEEP(true);

   if (key == CKeyboard::KEY_LEFT)
   {

   }
   if (key == CKeyboard::KEY_RIGHT)
   {

   }
}

// ----------------------------------------------------------------------------

void CKeyHandler::display()
{
   CDisplay::instance()->setCursor(0, 0);
   CDisplay::instance()->print(mTempCtrl->getInTemp(), 1);

   CDisplay::instance()->setCursor(6, 0);
   CDisplay::instance()->print(mTempCtrl->getTemp(), 1);

   CDisplay::instance()->setCursor(11, 0);
   CDisplay::instance()->print(mTempCtrl->getOutTemp(), 1);
}

// ----------------------------------------------------------------------------

void CKeyHandler::onExecute(void)
{
   display();
}

