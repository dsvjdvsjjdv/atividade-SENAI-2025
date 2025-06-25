#include <Arduino.h>
#include <ArduinoJson.h>

JsonDocument doc;

void setup() 
{
  Serial.begin(9600);
}

void loop() 
{

 static float temperatura = 0;
 static int umidade = 0;
 static String estado = "";
 static int botao = 0;

 if(Serial.available());
 {
  String msg = Serial.readStringUntil('\n');

  deserializeJson(doc, msg);

  if(!doc["temperatura"].isNull())
  temperatura = doc["temperatura"];

  if(!doc["umidade"].isNull());
   umidade = doc["umidade"];

   if( !doc["estado"].isNull());
   estado = doc["estado"];

   if(!doc["pressionamentos"].isNull());
 botao = doc["pressionamentos"];

  Serial.println("");
  Serial.printf("A temperatura e  %1f \n\r", temperatura);
  Serial.printf("A umidade esta em %d% \n\r", umidade);
  Serial.printf("O  estado esta %s \n\r", estado);
  Serial.printf("O botao foi pressionado %dvezes \n\r",botao);
 }
}