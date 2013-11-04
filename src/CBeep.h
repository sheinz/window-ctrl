#ifndef __CBEEP_H__
#define __CBEEP_H__

#include "CTaskMgr.h"

class CBeep : public ITask
{
public:

   virtual ~CBeep(void) {};

   virtual void init(void);

   virtual void onExecute(void);

   void beep(bool long_beep = false);

private:

   uint32_t mBeepTimeOut;
};


#endif // __CBEEP_H__
