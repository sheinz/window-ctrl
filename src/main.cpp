
#include "Arduino.h"

#include "AFMotor.h"

#include "LiquidCrystal.h"

#include "CTaskMgr.h"

#include "CWindow.h"


LiquidCrystal lcd(22, 24, 26, 28, 30, 32, 34);
static CTaskMgr task_mgr;
static CWindow window;

class Test : public ITask
{
private:
   uint8_t m_window_state;
   uint8_t m_step;

public:
   virtual void init(void)
   {
      m_window_state = 0;
      m_step = 5;

      // keys
      pinMode(36, INPUT_PULLUP);
      pinMode(38, INPUT_PULLUP);
      pinMode(40, INPUT_PULLUP);
      pinMode(42, INPUT_PULLUP);

      lcd.setCursor(0, 1);
      lcd.print("open");
      lcd.setCursor(11, 1);
      lcd.print("close");
   };

   virtual void onExecute(void)
   {
      if (!window.is_idle())
      {
         lcd.setCursor(0, 0);
         lcd.print("In progress...");
         return;
      }
      else
      {
         lcd.setCursor(0, 0);
         lcd.print("State: ");
         lcd.print(m_window_state);
         lcd.print("        ");
      }

      if (!digitalRead(36))   // right "close"
      {
         if (m_window_state >= m_step)
         {
            m_window_state -= m_step;
            window.set(m_window_state);
         }
      }
      if (!digitalRead(38))   // down
      {
         //lcd.clear();
         //lcd.print("38");
      }
      if (!digitalRead(40))   // up
      {
         //lcd.clear();
         //lcd.print("40");
      }
      if (!digitalRead(42))   // left "open"
      {
         if (m_window_state + m_step <= 100)
         {
            m_window_state += m_step;
            window.set(m_window_state);
         }
      }
   };
};

static Test test;

void setup()
{
  Serial.begin(9600);           // set up Serial library at 9600 bps
  Serial.println("Motor test!");

  lcd.begin(16, 2);

  task_mgr.init();
  window.init();
  test.init();

  task_mgr.Add(&window, 100);
  task_mgr.Add(&test, 200);
}


void loop()
{
   task_mgr.processTasks();
}
