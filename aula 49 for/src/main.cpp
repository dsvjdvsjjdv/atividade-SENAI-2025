#include <Arduino.h>
#define pinLed 2
#define pinBoot 0

void setup()
{
  pinMode(pinLed, OUTPUT);
  pinMode(pinBoot, INPUT_PULLUP);
  Serial.begin(9600);

  for (int j = 0; j <= 10; j++)
  {
    for (int i = 0; i <= 10; i++)
    { Serial.print(j);
      Serial.print("x");
      Serial.print("x");
      Serial.print(i);
      Serial.print("=");
      Serial.println(j * i);
    }
    Serial.println("----------");
  }
 
}

void loop()
{
}
  


