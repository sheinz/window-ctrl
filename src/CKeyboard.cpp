
#include "CKeyboard.h"
#include "Arduino.h"

#define LONG_KEY_PRESS_TIME   2000    // 2sec
#define KEY_LONG_PRESS_PROCESSED  0xFFFFFFFF

// ----------------------------------------------------------------------------

CKeyboard::CKeyboard(IKeyHandler *pKeyHandler)
   : mpKeyHandler(pKeyHandler)
   , mLastKeyPressed(KEY_NONE)
   , mKeyPressTime(0)
{
}

// ----------------------------------------------------------------------------

void CKeyboard::init(void)
{
   pinMode(KEY_UP, INPUT_PULLUP);
   pinMode(KEY_DOWN, INPUT_PULLUP);
   pinMode(KEY_LEFT, INPUT_PULLUP);
   pinMode(KEY_RIGHT, INPUT_PULLUP);
}

// ----------------------------------------------------------------------------

void CKeyboard::onExecute(void)
{
   onKeyState(KEY_UP, !digitalRead(KEY_UP));
   onKeyState(KEY_DOWN, !digitalRead(KEY_DOWN));
   onKeyState(KEY_LEFT, !digitalRead(KEY_LEFT));
   onKeyState(KEY_RIGHT, !digitalRead(KEY_RIGHT));
}

// ----------------------------------------------------------------------------

void CKeyboard::onKeyState(EKey key, bool press)
{
   if (press)
   {
      if (key == mLastKeyPressed)
      {
         if (mKeyPressTime != KEY_LONG_PRESS_PROCESSED)
         {
            uint32_t delay = millis() - mKeyPressTime;
            if (delay >= LONG_KEY_PRESS_TIME)
            {
               mKeyPressTime = KEY_LONG_PRESS_PROCESSED;
               mpKeyHandler->onKeyLong(key);
            }
         }
      }
      else
      {
         mLastKeyPressed = key;
         mKeyPressTime = millis();
      }
   }
   else
   {        // key is released
      if (mLastKeyPressed == key)
      {  // this key is released
         if (mKeyPressTime != KEY_LONG_PRESS_PROCESSED)
         {
            uint32_t delay = millis() - mKeyPressTime;
            if (delay < LONG_KEY_PRESS_TIME)
            {  // short key press
               mpKeyHandler->onKey(key);
            }
         }
         mLastKeyPressed = KEY_NONE;
         mKeyPressTime = 0;
      }
   }
}
