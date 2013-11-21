/*
 * CTempController.cpp
 *
 *  Created on: Nov 20, 2013
 *      Author: yura
 */

#include "CTempController.h"
#include "Arduino.h"


CTempController::CTempController()
{

}

// ----------------------------------------------------------------------------

void CTempController::init()
{
}

// ----------------------------------------------------------------------------

void CTempController::onExecute()
{
}

// ----------------------------------------------------------------------------

void CTempController::onCoarseTempUpdate(float in_temp, float out_temp)
{
   Serial.print("Coarse in temp: ");
   Serial.println(in_temp);
   Serial.print("Out temp: ");
   Serial.println(out_temp);
}

// ----------------------------------------------------------------------------

void CTempController::onFineTempUpdate(float in_temp, float out_temp)
{
   Serial.print("Fine in temp: ");
   Serial.println(in_temp);
   Serial.print("Out temp: ");
   Serial.println(out_temp);
}

// ----------------------------------------------------------------------------

void CTempController::sleep()
{
}

// ----------------------------------------------------------------------------

void CTempController::resume()
{
}

// ----------------------------------------------------------------------------

void CTempController::setTemp(float temperature)
{
}

// ----------------------------------------------------------------------------

float CTempController::getTemp()
{
}

// ----------------------------------------------------------------------------

float CTempController::getInTemp()
{
}

// ----------------------------------------------------------------------------

float CTempController::getOutTemp()
{
}
