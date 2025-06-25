#include <Arduino.h>

 

void setup()

{
   delay(2000);

   pinMode(0,INPUT_PULLUP);
   pInMode(2,OUTPUT);
   Serial.begin(9600);




   while(estadoBotao ==0);
  { 
  
 digitalWrite(2,HIGH);
 delay(300);
 digitalWrite(2,LOW);
 delay(300);
  }
  
}

void loop()
{

}
