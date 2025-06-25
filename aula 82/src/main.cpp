#include <Arduino.h>
#include "botao.h"

botao btn_boot(0);


void setup() 
{
  Serial.begin(9600);
  btn_boot.begin();

}

void loop() 
{
  btn_boot.update();
  if(btn_boot.pressioado())
  {
    Serial.println("Botao pressionado");
  }
  if(btn_boot.solto())
  {
    Serial.printf("O botao ficou pressionado %.02f segundos\n\r", btn_boot.duracaoUltimoEstado()/1000.0);
  }
}
