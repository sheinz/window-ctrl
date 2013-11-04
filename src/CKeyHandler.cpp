#include "CKeyHandler.h"


CKeyHandler::CKeyHandler(CWindow* pWindow, LiquidCrystal *pLcd)
   : mpWindow(pWindow)
   , mpLcd(pLcd)
   , m_window_state(0)
   , m_step(10)
{
}

// ----------------------------------------------------------------------------

void CKeyHandler::onKey(CKeyboard::EKey key)
{
   if (key == CKeyboard::KEY_LEFT)
   {
      if (m_window_state + m_step <= 100)
      {
         m_window_state += m_step;
         mpWindow->set(m_window_state);
      }
      else
      {
         m_window_state = 100;
         mpWindow->set(m_window_state);
      }
   }
   if (key == CKeyboard::KEY_RIGHT)
   {
      if (m_window_state >= m_step)
      {
         m_window_state -= m_step;
         mpWindow->set(m_window_state);
      }
      else
      {
         m_window_state = 0;
         mpWindow->set(m_window_state);
      }
   }
}

// ----------------------------------------------------------------------------

void CKeyHandler::onKeyLong(CKeyboard::EKey key)
{
   if (key == CKeyboard::KEY_LEFT)
   {
      if (m_window_state + 25 <= 100)
      {
         m_window_state += 25;
         mpWindow->set(m_window_state);
      }
      else
      {
         m_window_state = 100;
         mpWindow->set(m_window_state);
      }
   }
   if (key == CKeyboard::KEY_RIGHT)
   {
      if (m_window_state >= 25)
      {
         m_window_state -= 25;
         mpWindow->set(m_window_state);
      }
      else
      {
         m_window_state = 0;
         mpWindow->set(m_window_state);
      }
   }
}

// ----------------------------------------------------------------------------

void CKeyHandler::onExecute(void)
{
   if (!mpWindow->is_idle())
   {
      mpLcd->setCursor(0, 0);
      mpLcd->print("Processing...");
   }
   else
   {
      mpLcd->setCursor(0, 0);
      mpLcd->print("State: ");
      mpLcd->print(m_window_state);
      mpLcd->print(" %    ");
   }
}
