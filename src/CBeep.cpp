
#include "CBeep.h"
#include "Arduino.h"

#define BEEPER_PIN      46

// ----------------------------------------------------------------------------

CBeep* CBeep::instance()
{
   static CBeep obj;
   return &obj;
}

// ---------------------------------------------------------------------------

void CBeep::init(void)
{
   pinMode(BEEPER_PIN, OUTPUT);

   digitalWrite(BEEPER_PIN, LOW);

   mBeepTimeOut = 0;

   CTaskMgr::instance()->Add(this, 50);
}

// ---------------------------------------------------------------------------

void CBeep::onExecute(void)
{
   if (mBeepTimeOut)
   {
      if (millis() >= mBeepTimeOut)
      {
         mBeepTimeOut = 0;
         digitalWrite(BEEPER_PIN, LOW);
      }
   }
}

// ---------------------------------------------------------------------------

void CBeep::beep(bool long_beep)
{
   mBeepTimeOut = millis() + (long_beep ? 500 : 50);
   digitalWrite(BEEPER_PIN, HIGH);
}

// ---------------------------------------------------------------------------
