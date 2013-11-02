
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
   bool m_started;

public:
   virtual void init(void)
   {
      m_started = false;
   };

   virtual void onExecute(void)
   {
      if (!m_started)
      {
         m_started = true;
         window.calibrate();
         lcd.print("Calibration started");
      }
      else
      {
         if (window.is_calibrating())
         {
            lcd.clear();
            lcd.print("In progress...");
         }
         else
         {
            lcd.clear();
            lcd.print("Done: ");
            lcd.print(window.get_calib());
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
  task_mgr.Add(&test, 1000);
}


void loop()
{
   task_mgr.processTasks();
}
