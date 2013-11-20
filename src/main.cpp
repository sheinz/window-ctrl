
#include "Arduino.h"

#include "AFMotor.h"

#include "LiquidCrystal.h"

#include "CTaskMgr.h"

#include "CWindow.h"
#include "CKeyboard.h"
#include "CKeyHandler.h"
#include "CBeep.h"
#include "DS18B20.h"


LiquidCrystal lcd(22, 24, 26, 28, 30, 32, 34);
static CTaskMgr task_mgr;
static CWindow window;
static CKeyHandler key_handler(&window, &lcd);
static CKeyboard keyboard(&key_handler);
CBeep beep;

static DS18B20 ds18b20(50);

class PrintTemp : public ITask
{
private:
   uint8_t mNumSensors;
public:
   virtual void init()
   {
      mNumSensors = ds18b20.search();
      Serial.print("Sensors found: ");
      Serial.println(mNumSensors);

      ds18b20.startMeasurementAll();
   }

   virtual void onExecute()
   {
      float indoor = ds18b20.getTemperature(0);
      float outdoor = ds18b20.getTemperature(1);
      ds18b20.startMeasurementAll();

      lcd.setCursor(0, 1);
      lcd.print("In ");
      lcd.print(indoor, 1);
      lcd.print(" Out ");
      lcd.print(outdoor, 1);
   }
};

static PrintTemp print_temp;

void setup()
{
  Serial.begin(9600);           // set up Serial library at 9600 bps
  Serial.println("Motor test!");

  lcd.begin(16, 2);

  task_mgr.init();
  window.init();
  keyboard.init();
  beep.init();
  print_temp.init();

  task_mgr.Add(&window, 100);
  task_mgr.Add(&keyboard, 100);
  task_mgr.Add(&key_handler, 1000);
  task_mgr.Add(&beep, 50);
  task_mgr.Add(&print_temp, 2000);
}


void loop()
{
   task_mgr.processTasks();
}
