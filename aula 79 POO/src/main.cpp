#include <Arduino.h>
#include "Led.h"


Led ledESP(2);


void setup() 
{
  
  
}

void loop() 
{
  ledESP.update();
  ledESP.ligar();
  ledESP.desligar();
  ledESP.inverter();
  ledESP.piscar(2);
  
}