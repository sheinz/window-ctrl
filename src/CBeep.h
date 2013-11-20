#ifndef __CBEEP_H__
#define __CBEEP_H__

#include "CTaskMgr.h"

class CBeep : public ITask
{
public:
   static CBeep* instance();

   virtual void init(void);

   virtual void onExecute(void);

   void beep(bool long_beep = false);

private:
   // not destructor due to interesting error message
   // "undefined reference to `atexit'"

   uint32_t mBeepTimeOut;
};


#endif // __CBEEP_H__
