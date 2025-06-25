#include <Arduino.h>
#include <Adafruit_NeoPixel.h>

Adafruit_NeoPixel ledRGB (1,48,NEO_GBR); //quantidade de led,pino,tipo

int r = 0;
int g = 0;
int b = 0;
void setup() 
{
  ledRGB.begin();
  ledRGB.setBrightness(32); //0 -225 intensidade de brilho
  
  ledRGB.setPixelColor(0,ledRGB.Color(156, 20, 20));
  ledRGB.show();
}

void loop() 
{
  ledRGB.setPixelColor(0,ledRGB.Color(r,g,b));
  ledRGB.show();

}