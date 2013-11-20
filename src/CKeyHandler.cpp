#include "CKeyHandler.h"
#include "CBeep.h"
#include "CDisplay.h"

// ----------------------------------------------------------------------------

CKeyHandler::CKeyHandler()
   : m_window_state(0)
   , m_step(10)
{
}

// ----------------------------------------------------------------------------

void CKeyHandler::init(void)
{
   CTaskMgr::instance()->Add(this, 1000);
}

// ----------------------------------------------------------------------------

void CKeyHandler::onKey(CKeyboard::EKey key)
{
   CBeep::instance()->beep();

   if (key == CKeyboard::KEY_LEFT)
   {
      if (m_window_state + m_step <= 100)
      {
         m_window_state += m_step;
         CWindow::instance()->set(m_window_state);
      }
      else
      {
         m_window_state = 100;
         CWindow::instance()->set(m_window_state);
      }
   }
   if (key == CKeyboard::KEY_RIGHT)
   {
      if (m_window_state >= m_step)
      {
         m_window_state -= m_step;
         CWindow::instance()->set(m_window_state);
      }
      else
      {
         m_window_state = 0;
         CWindow::instance()->set(m_window_state);
      }
   }
   if (key == CKeyboard::KEY_DOWN)
   {
      CWindow::instance()->calibrate();
   }
}

// ----------------------------------------------------------------------------

void CKeyHandler::onKeyLong(CKeyboard::EKey key)
{
   CBeep::instance()->beep(true);

   if (key == CKeyboard::KEY_LEFT)
   {
      if (m_window_state + 25 <= 100)
      {
         m_window_state += 25;
         CWindow::instance()->set(m_window_state);
      }
      else
      {
         m_window_state = 100;
         CWindow::instance()->set(m_window_state);
      }
   }
   if (key == CKeyboard::KEY_RIGHT)
   {
      if (m_window_state >= 25)
      {
         m_window_state -= 25;
         CWindow::instance()->set(m_window_state);
      }
      else
      {
         m_window_state = 0;
         CWindow::instance()->set(m_window_state);
      }
   }
}

// ----------------------------------------------------------------------------

void CKeyHandler::onExecute(void)
{
   if (!CWindow::instance()->is_idle())
   {
      CDisplay::instance()->setCursor(0, 0);
      CDisplay::instance()->print("Processing...");
   }
   else
   {
      CDisplay::instance()->setCursor(0, 0);
      CDisplay::instance()->print("State: ");
      CDisplay::instance()->print(m_window_state);
      CDisplay::instance()->print(" %    ");
   }
}

