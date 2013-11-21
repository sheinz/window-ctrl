/*
 * CMessage.cpp
 *
 *  Created on: Nov 21, 2013
 *      Author: yura
 */

#include "CMessage.h"
#include "CDisplay.h"

#define MESSAGE_LINE    1

CMessage* CMessage::instance()
{
   static CMessage msg;
   return &msg;
}

// ----------------------------------------------------------------------------

void CMessage::show(const char* pStr, uint8_t seconds)
{
   clear();
   CDisplay::instance()->setCursor(0, MESSAGE_LINE);
   CDisplay::instance()->print(pStr);

   if (seconds)
   {
      CTaskMgr::instance()->Add(this, (uint32_t)seconds * 1000);
   }
}

// ----------------------------------------------------------------------------

void CMessage::clear()
{
   CTaskMgr::instance()->Remove(this);

   CDisplay::instance()->setCursor(0, MESSAGE_LINE);
   for (uint8_t i = 0; i < 16; i++)
   {
      CDisplay::instance()->print(' ');
   }
}

// ----------------------------------------------------------------------------

void CMessage::onExecute()
{
   CTaskMgr::instance()->Remove(this);
   clear();
}

// ----------------------------------------------------------------------------

CMessage::CMessage()
{

}
