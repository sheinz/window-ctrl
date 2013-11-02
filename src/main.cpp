
#include "Arduino.h"

#include "AFMotor.h"

#include "LiquidCrystal.h"


AF_DCMotor motor(4);

LiquidCrystal lcd(22, 24, 26, 28, 30, 32, 34);

void setup()
{
  Serial.begin(9600);           // set up Serial library at 9600 bps
  Serial.println("Motor test!");

  pinMode(52, INPUT_PULLUP);
  pinMode(53, INPUT_PULLUP);

  // turn on motor
  motor.setSpeed(255);

  motor.run(RELEASE);

  lcd.begin(16, 2);
  lcd.setCursor(0, 0);
  lcd.print("Closing:");
  lcd.setCursor(0, 1);
  lcd.print("Opening:");
}

void test(void)
{
   uint32_t timeout = 0;

   motor.run(FORWARD);

   lcd.setCursor(9, 0);
   lcd.print("   ");
   while (!digitalRead(52))
   {
      timeout++;
      lcd.setCursor(9, 0);
      lcd.print(timeout);
      delay(1000);
   }

   motor.run(RELEASE);
   delay(10000);

   Serial.println();

   timeout = 0;

   motor.run(BACKWARD);

   lcd.setCursor(9, 1);
   lcd.print("   ");

   while (!digitalRead(53))
   {
      timeout++;
      lcd.setCursor(9, 1);
      lcd.print(timeout);
      delay(1000);
   }

   motor.run(RELEASE);
   delay(10000);
}



void loop()
{
   test();
}
