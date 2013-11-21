#include "CKeyHandler.h"
#include "CBeep.h"
#include "CDisplay.h"
#include "CWindow.h"


#define TEMP_SET_STEP      0.5

#define WINDOW_CTRL_STEP   10

// ----------------------------------------------------------------------------

CKeyHandler::CKeyHandler(CTempController* pTempCtrl)
   : mTempCtrl(pTempCtrl)
{
}

// ----------------------------------------------------------------------------

void CKeyHandler::init(void)
{
   CTaskMgr::instance()->Add(this, 5000);
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
   if (key == CKeyboard::KEY_LEFT)
   {
      uint8_t state = CWindow::instance()->get();

      state += WINDOW_CTRL_STEP;
      if (state < 100)
      {
         CWindow::instance()->set(state);
      }
      else
      {
         CWindow::instance()->set(100);
      }
   }
   if (key == CKeyboard::KEY_RIGHT)
   {
      uint8_t state = CWindow::instance()->get();

      if (state < WINDOW_CTRL_STEP)
      {
         CWindow::instance()->set(0);
      }
      else
      {
         CWindow::instance()->set(state - WINDOW_CTRL_STEP);
      }
   }

   display();
}

// ----------------------------------------------------------------------------

void CKeyHandler::onKeyLong(CKeyboard::EKey key)
{
   BEEP(true);

   if (key == CKeyboard::KEY_DOWN)
   {
      CWindow::instance()->calibrate();
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

   CDisplay::instance()->setCursor(0, 1);
   CDisplay::instance()->print(CWindow::instance()->is_idle() ?
         "             " : "Processing...");

}

// ----------------------------------------------------------------------------

void CKeyHandler::onExecute(void)
{
   display();
}

