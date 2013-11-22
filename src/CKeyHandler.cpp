#include "CKeyHandler.h"
#include "CBeep.h"
#include "CDisplay.h"
#include "CWindow.h"
#include "CMessage.h"


#define TEMP_SET_STEP      0.5

#define WINDOW_CTRL_STEP   20

// ----------------------------------------------------------------------------

CKeyHandler::CKeyHandler(CTempController* pTempCtrl)
   : mTempCtrl(pTempCtrl)
   , mIRreceiver(this)
   , mCalibration(false)
{
}

// ----------------------------------------------------------------------------

void CKeyHandler::init(void)
{
   mIRreceiver.init();

   CTaskMgr::instance()->Add(this, 5000);

   display();
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
      SHOW_MESSAGE("Refreshing room", 2);
      mTempCtrl->refreshRoom();
   }
   if (key == CKeyboard::KEY_RIGHT)
   {
      SHOW_MESSAGE("Warming up room", 2);
      mTempCtrl->warmUpRoom();
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
      mCalibration = true;
      SHOW_MESSAGE("Calibration");
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
      SHOW_MESSAGE("Opening", 2);
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
      SHOW_MESSAGE("Closing", 2);
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

   if (mCalibration && !CWindow::instance()->is_calibrating())
   {
      mCalibration = false;
      SHOW_MESSAGE("Done ", 10);
      CDisplay::instance()->print(CWindow::instance()->get_calib());
   }
}

// ----------------------------------------------------------------------------

void CKeyHandler::onExecute(void)
{
   display();
}

// ----------------------------------------------------------------------------

void CKeyHandler::onIrCmd(uint16_t cmd)
{
   switch (cmd)
   {
   case 0xE21D:
      onKey(CKeyboard::KEY_LEFT);
      break;
   case 0x609F:
      onKey(CKeyboard::KEY_RIGHT);
      break;
   case 0xA05F:
      onKey(CKeyboard::KEY_UP);
      break;
   case 0x926D:
      onKey(CKeyboard::KEY_DOWN);
      break;
   case 0x7887:
      onKeyLong(CKeyboard::KEY_LEFT);
      break;
   case 0x906F:
      onKeyLong(CKeyboard::KEY_RIGHT);
      break;
   }
}
