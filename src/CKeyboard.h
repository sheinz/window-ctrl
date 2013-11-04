#ifndef __CKEYBOARD_H__
#define __CKEYBOARD_H__

#include "CTaskMgr.h"
#include <inttypes.h>

class IKeyHandler;

class CKeyboard : public ITask
{
public:
   enum EKey
   {
      KEY_NONE = 0,
      KEY_UP = 40,
      KEY_DOWN = 38,
      KEY_RIGHT = 36,
      KEY_LEFT = 42
   };

   CKeyboard(IKeyHandler *pKeyHandler);

   virtual ~CKeyboard(void) {};

   virtual void init(void);

   virtual void onExecute(void);

private:
   IKeyHandler *mpKeyHandler;
   EKey mLastKeyPressed;
   uint32_t mKeyPressTime;

   void onKeyState(EKey key, bool press);
};

// ----------------------------------------------------------------------------

class IKeyHandler
{
public:
   virtual ~IKeyHandler(void) {};

   virtual void onKey(CKeyboard::EKey key) = 0;

   virtual void onKeyLong(CKeyboard::EKey key) = 0;
};

#endif // __CKEYBOARD_H__
