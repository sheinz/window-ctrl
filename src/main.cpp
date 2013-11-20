
#include "Arduino.h"

#include "CLifeCycle.h"

static CLifeCycle life_cycle;


void setup()
{
   life_cycle.init();
}

void loop()
{
   life_cycle.process();
}
