#include "CWindow.h"
#include "Arduino.h"
#include "avr/eeprom.h"

#define OPEN_TERMINAL_SWITCH        53
#define CLOSE_TERMINAL_SWITCH       52

#define NO_TIMEOUT      700000      // still some timeout

#define PERCENCT_UNDEFINED 0xFF

#define DEFAULT_FULL_OP_TIME   190000   // 190sec

// ----------------------------------------------------------------------------

EEMEM uint32_t eeprom_calib_full_ms;

// ----------------------------------------------------------------------------

CWindow::CWindow(void)
   : m_motor(4)
   , m_full_ms(DEFAULT_FULL_OP_TIME)
   , m_op_time_stop(0)
   , m_curr_percentage(PERCENCT_UNDEFINED)
   , m_pending_percentage(PERCENCT_UNDEFINED)
   , m_state(IDLE)
{
}

// ----------------------------------------------------------------------------

void CWindow::init(void)
{
   pinMode(OPEN_TERMINAL_SWITCH, INPUT_PULLUP);
   pinMode(CLOSE_TERMINAL_SWITCH, INPUT_PULLUP);

   m_motor.setSpeed(255);
   m_motor.run(RELEASE);

   m_full_ms = eeprom_read_dword(&eeprom_calib_full_ms);

   if (m_full_ms > NO_TIMEOUT || m_full_ms < 50000)
   {
      m_full_ms = DEFAULT_FULL_OP_TIME;
   }
}

// ----------------------------------------------------------------------------

void CWindow::onExecute(void)
{
   bool timeout = (m_op_time_stop <= millis());

   if (m_state == OPEN)
   {
      if (digitalRead(OPEN_TERMINAL_SWITCH) || timeout)
      {
         m_state = IDLE;
         m_motor.run(RELEASE);
         m_curr_percentage = (timeout) ? m_pending_percentage : 100;
      }
   }
   else if (m_state == CLOSE)
   {
      if (digitalRead(CLOSE_TERMINAL_SWITCH) || timeout)
      {
         m_state = IDLE;
         m_motor.run(RELEASE);
         m_curr_percentage = (timeout) ? m_pending_percentage : 0;
      }
   }
   else if (m_state == CALIB_INIT_CLOSE)
   {
      if (timeout)
      {
         m_motor.run(RELEASE);
         m_state = CALIB_ERROR;
      }
      else if (digitalRead(CLOSE_TERMINAL_SWITCH))
      {
         m_full_ms = millis();
         m_state = CALIB_FULL_OPEN;
         start_open();
      }
   }
   else if (m_state == CALIB_FULL_OPEN)
   {
      if (timeout)
      {
         m_motor.run(RELEASE);
         m_state = CALIB_ERROR;
      }
      else if (digitalRead(OPEN_TERMINAL_SWITCH))
      {
         m_state = CALIB_FULL_CLOSE;
         start_close();
      }
   }
   else if (m_state == CALIB_FULL_CLOSE)
   {
      if (timeout)
      {
         m_motor.run(RELEASE);
         m_state = CALIB_ERROR;
      }
      else if (digitalRead(CLOSE_TERMINAL_SWITCH))
      {
         // Calibration is finished
         m_full_ms = (millis() - m_full_ms) / 2;

         eeprom_update_dword(&eeprom_calib_full_ms, m_full_ms);
         m_state = IDLE;
         m_curr_percentage = 0;
         m_motor.run(RELEASE);
      }
   }
   else if (m_state == INIT_CLOSE)
   {
      if (timeout)
      {
         m_motor.run(RELEASE);
         // ERROR
      }
      else if (digitalRead(CLOSE_TERMINAL_SWITCH))
      {
         m_curr_percentage = 0;
         m_state = IDLE;
         m_motor.run(RELEASE);
         set(m_pending_percentage);
      }
   }
}

// ----------------------------------------------------------------------------

void CWindow::calibrate(void)
{
   m_state = CALIB_INIT_CLOSE;
   m_op_time_stop = millis() + NO_TIMEOUT;
   start_close();
}

// ----------------------------------------------------------------------------

void CWindow::open(void)
{
   m_op_time_stop = millis() + NO_TIMEOUT;
   m_state = OPEN;
   start_open();
}

// ----------------------------------------------------------------------------

void CWindow::close(void)
{
   m_op_time_stop = millis() + NO_TIMEOUT;
   m_state = CLOSE;
   start_close();
}

// ----------------------------------------------------------------------------

void CWindow::set(uint8_t open_percent)
{
   uint8_t diff_percent;

   if (m_state != IDLE)
      return;

   if (m_curr_percentage == PERCENCT_UNDEFINED)
   {
      m_state = INIT_CLOSE;
      start_close();
      m_op_time_stop = millis() + NO_TIMEOUT;
      m_pending_percentage = open_percent;
   }
   else if (open_percent > m_curr_percentage)
   {
      diff_percent = open_percent - m_curr_percentage;

      m_op_time_stop = millis() + (m_full_ms / 100 * diff_percent);
      m_state = OPEN;
      start_open();
      m_pending_percentage = open_percent;
   }
   else if (open_percent < m_curr_percentage)
   {
      diff_percent = m_curr_percentage - open_percent;

      m_op_time_stop = millis() + (m_full_ms / 100 * diff_percent);
      m_state = CLOSE;
      start_close();
      m_pending_percentage = open_percent;
   }
}

// ----------------------------------------------------------------------------

void CWindow::start_open()
{
   if (!digitalRead(OPEN_TERMINAL_SWITCH))
   {
      m_motor.run(BACKWARD);
   }
}

// ----------------------------------------------------------------------------

void CWindow::start_close()
{
   if (!digitalRead(CLOSE_TERMINAL_SWITCH))
   {
      m_motor.run(FORWARD);
   }
}

// ----------------------------------------------------------------------------

bool CWindow::is_calibrating(void)
{
   return (m_state == CALIB_FULL_CLOSE ||
           m_state == CALIB_FULL_OPEN ||
           m_state == CALIB_INIT_CLOSE);
}

// ----------------------------------------------------------------------------

bool CWindow::is_idle(void)
{
   return (m_state == IDLE);
}

// ----------------------------------------------------------------------------

uint32_t CWindow::get_calib(void)
{
   return m_full_ms;
}
