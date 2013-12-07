#include "CKeyHandler.h"
#include "CBeep.h"
#include "CDisplay.h"
#include "CWindow.h"
#include "CMessage.h"

#include "Servo.h"


#define TEMP_SET_STEP      0.5

#define WINDOW_CTRL_STEP   20

// ----------------------------------------------------------------------------

static Servo blinds_servo;

// ----------------------------------------------------------------------------

CKeyHandler::CKeyHandler(CTempController* pTempCtrl)
   : mTempCtrl(pTempCtrl)
   , mIRreceiver(this)
   , mCalibration(false)
   , mLocked(false)
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
      if (checkWindowUnlocked())
      {
         SHOW_MESSAGE("Refreshing room", 2);
         mTempCtrl->refreshRoom();
      }
   }
   if (key == CKeyboard::KEY_RIGHT)
   {
      if (checkWindowUnlocked())
      {
         SHOW_MESSAGE("Warming up room", 2);
         mTempCtrl->warmUpRoom();
      }
   }

   display();
}

// ----------------------------------------------------------------------------

void CKeyHandler::onKeyLong(CKeyboard::EKey key)
{
   BEEP(true);

   if (!checkWindowUnlocked())
      return;  // Window is locked do nothing

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

   if (CWindow::instance()->is_locked())
   {
      mLocked = true;
      SHOW_MESSAGE("Locked");
   }
   else
   {
      if (mLocked)
      {
         mLocked = false;
         SHOW_MESSAGE("Unlocked", 2);
      }
   }

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
   blinds_servo.detach();
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
   case 0xC03F:
      SHOW_MESSAGE("Opening blinds", 2);
      blinds_servo.attach(9, 690, 2600);
      blinds_servo.write(180);
      break;
   case 0x40BF:
      SHOW_MESSAGE("Closing blinds", 2);
      blinds_servo.attach(9, 690, 2600);
      blinds_servo.write(0);
      break;
   }
}

// ----------------------------------------------------------------------------

bool CKeyHandler::checkWindowUnlocked()
{
   if (CWindow::instance()->is_locked())
   {
      SHOW_MESSAGE("Window is locked!", 2);
      return false;
   }
   return true;
}
