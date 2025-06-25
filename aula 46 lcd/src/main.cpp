#include <Arduino.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 20 , 4);

#define pinLedBranco 2
 #define pinBotao 23

 byte sorriso[] = {
  B00000,
  B00000,
  B01010,
  B00100,
  B10001,
  B01110,
  B00000,
  B00000
};


void setup()
{
 
  pinMode(2,INPUT);
  pinMode(pinBotao, INPUT_PULLUP);
   lcd.init();
   lcd.backlight();
   lcd.print('FELIZ');
   lcd.setCursor(0,1);
   lcd.write(0);
   digitalWrite(pinLedBranco, HIGH); 
}


void loop()
{
  
 bool estadoAtualBotao = digitalRead(pinBotao);
 static bool estadoAnteriorBotao =0;
  static bool estadoLed = 0;
  
  if(estadoAtualBotao == 1 && estadoAnteriorBotao ==0)
  {
     estadoLed = !estadoLed;
    digitalWrite(pinLedBranco,estadoLed);
    
    if(estadoLed == 1)
    {
      
    
    lcd.setCursor(0,0);
    lcd.print("FELIZ  ");
      
      }
    
      else
      {
        lcd.setCursor(0,1);
        lcd.print("SORRISO");
      }
    }
    estadoAnteriorBotao = estadoAtualBotao;
    }


