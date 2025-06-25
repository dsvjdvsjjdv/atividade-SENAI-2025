#include <Arduino.h>
#include "temporizador.h"
#include "Led.h"
#include "botao.h"

temporizador tempo_10s(500);
Led led_placa(2);
Botao btn_boot(0);

void setup() 
{
 tempo_10s.iniciar();
 
 }

void loop() 
{
  btn_boot.update();
  led_placa.update();
  
  if(btn_boot.Botaopressionado())
  {
    if(!tempo_10s.estaAtivo())
    tempo_10s.iniciar();

    else 
    tempo_10s.reiniciar();

    led_placa.piscar(3);
  }
  if(tempo_10s.estaPronto())
  {
    led_placa.desligar();
    tempo_10s.parar();
  }
  
}