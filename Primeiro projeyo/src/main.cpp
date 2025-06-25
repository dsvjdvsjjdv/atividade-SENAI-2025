#include <Arduino.h>
#define pinBotao 23
#define pinLed 2

void setup()
{
  pinMode(pinLed, OUTPUT);
  pinMode(pinBotao, INPUT_PULLUP);
  Serial.begin(9600);
}
void loop()
{
  bool estadoAtualBotao = digitalRead(pinBotao);
  static bool estadoAnteriorBotao = 1;
  static int contagem = 0;
  static bool ultimaAcao = 1;

  static unsigned long tempoUltiAlteracao = 0;
  unsigned long tempoAtual = millis();
  static bool tempoFiltro = 50;

  static bool estadoLed = 0;

  if (estadoAtualBotao != estadoAnteriorBotao)
  {
    tempoUltimaAlteracao = tempoAtual;
  }

  if (tempoAtual - tempoUltimaAlteracao > tempoFiltro)
  {

    if (estadoAtualBotao != ultimaAcao)
    {
      ultimaAcao = estadoAtualBotao;
      if (estadoAtualBotao == 0)
    
      {
       estadoLed = !estadoLed;
      digitalWrite(pinLed, estadoLed);
      }
       else
      {

      }

       } 
  }
  estadoAnteriorBotao = estadoAtualBotao;
  //! FINAL DO BOTAO
}