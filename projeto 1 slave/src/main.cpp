#include <Arduino.h>
#include <BluetoothSerial.h>
#include <ArduinoJson.h>
#include <LiquidCrystal_I2C.h>

// Definiçoes
BluetoothSerial BT;
LiquidCrystal_I2C lcd(0x27, 20, 4);
JsonDocument doc;

void setup()
{
  Serial.begin(9600);
  BT.begin("SlaveRhuan"); // Nome do Bluetooth (modo Slave)
  Serial.println(BT.getBtAddressString());
  lcd.init();
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("teste");
}

void loop()

{
  unsigned long tempoAtual = millis();
  static unsigned long tempoInicial = 0;

  if (BT.available())
  {
    String mensaemRecebida = BT.readStringUntil('\n');
    mensaemRecebida.trim();
    Serial.println(mensaemRecebida);
  }
}

 