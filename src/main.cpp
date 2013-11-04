
#include "Arduino.h"

#include "AFMotor.h"

#include "LiquidCrystal.h"

#include "CTaskMgr.h"

#include "CWindow.h"
#include "CKeyboard.h"
#include "CKeyHandler.h"


LiquidCrystal lcd(22, 24, 26, 28, 30, 32, 34);
static CTaskMgr task_mgr;
static CWindow window;
static CKeyHandler key_handler(&window, &lcd);
static CKeyboard keyboard(&key_handler);


void setup()
{
  Serial.begin(9600);           // set up Serial library at 9600 bps
  Serial.println("Motor test!");

  lcd.begin(16, 2);

  task_mgr.init();
  window.init();
  keyboard.init();

  task_mgr.Add(&window, 100);
  task_mgr.Add(&keyboard, 100);
  task_mgr.Add(&key_handler, 1000);
}


void loop()
{
   task_mgr.processTasks();
}
