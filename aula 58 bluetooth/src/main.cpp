#include <Arduino.h>
#include <BluetoothSerial.h>

#define pinLed 2

BluetoothSerial BT;

void setup()
{
  pinMode(pinLed, OUTPUT);

  BT.begin("ESPRhuan");
}

void loop()
{
  static bool estadoLed = false;
  static bool piscaled = false;
  if (BT.available())

  {
    String mensagem = BT.readStringUntil('\n');
    mensagem.trim();

    if (mensagem.equals("Liga"))
    {
      estadoLed = true;
      BT.println("LED LIGADO");
    }
    else if (mensagem.equals("Desliga"))
    {
      estadoLed = false;
      BT.println("LED DESLIGADO");
    }
    else if (mensagem.equals("pisca"))
    {
      piscaled = true;
    }
  }
  digitalWrite(pinLed, estadoLed);
}