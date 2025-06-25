#include <Arduino.h>
#define pinA 13
#define pinB 12
#define pinC 14
#define pinD 27
#define pinE 26
#define pinF 25
#define pinK 33
#define pinX 32
#define pinY 35



void setup() 
{
  Serial.begin(9600);
  pinMode(pinA,INPUT);
  pinMode(pinB,INPUT);
  pinMode(pinC,INPUT);
  pinMode(pinD,INPUT);
   pinMode(pinE,INPUT);
  pinMode(pinF,INPUT);
  pinMode(pinK,INPUT);
  pinMode(pinX,INPUT);
  pinMode(pinK,INPUT);

}

void loop() 
{
  Serial.printf("A: %d\n\r",digitalRead(pinA));
  Serial.printf("B: %d\n\r",digitalRead(pinB));
   Serial.printf("C: %d\n\r",digitalRead(pinC));
  Serial.printf("D: %d\n\r",digitalRead(pinD));
  Serial.printf("E: %d\n\r",digitalRead(pinE));
  Serial.printf("F: %d\n\r",digitalRead(pinF));
   Serial.printf("K: %d\n\r",digitalRead(pinK));
  Serial.printf("X: %d\n\r",analogRead(pinX));
  Serial.printf("Y: %d\n\r",analogRead(pinY));
  Serial.println("                             ");
}