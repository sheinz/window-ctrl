/*
 * CMessage.h
 *
 *  Created on: Nov 21, 2013
 *      Author: yura
 */

#ifndef __CMESSAGE_H__
#define __CMESSAGE_H__

#include "CTaskMgr.h"

#define SHOW_MESSAGE CMessage::instance()->show

class CMessage: public ITask
{
public:
   static CMessage* instance();

   void show(const char *pStr, uint8_t seconds = 0);
   void clear();

   virtual void onExecute();

private:
   CMessage();
};

#endif   // __CMESSAGE_H__
