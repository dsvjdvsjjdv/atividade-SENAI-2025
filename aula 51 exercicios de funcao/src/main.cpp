#include <Arduino.h>

float fahrenheit(float, float, float);
// float hipotenusa(float,float );
float polegadasParaCentimetros(float);
float Milimetros(float, float, float);
float tamanhoTv(float, float);
int resultado = 0;
void setup()
{

  Serial.begin(9600);
  // Serial.println(hipotenusa(5.3,3.7));
  Serial.printf("Uma tv de 50\" tem %f centimetros", polegadasParaCentimetros(50));
  Serial.printf("100mm eh igual a %f pol \n\r", Milimetros(50, 25.4, 128));
  Serial.printf("100C eh %f \n\r", fahrenheit(50, 1.8, 32));
  Serial.printf("uma tv de 50\" e 72cm d altura tem %fcm de comprimento", tamanhoTv(50, 72));
}

void loop()
{
}
// atividade1
float hipotenusa(float catetoA, float catetoB)
{
  float resultado = (catetoA * catetoA) + (catetoB * catetoB);
  resultado = sqrt(resultado);
  return resultado;
  return sqrt(sq(catetoA) + sq(catetoB));
}
// atividade A
float fahrenheit(float graus, float divisor, float numero)
{
  return (graus * divisor) + numero;
}
// atividade B
float Milimetros(float polegadas, float centimetros, float divisor)
{
  return resultado = (polegadas / centimetros) * 128;
}
// atividade C
float polegadasParaCentimetros(float polegadas)
{
  return polegadas * 2.54;
}
float tamanhoTv(float polegadas, float alturaCm)
{
  return sqrt(sq(polegadasParaCentimetros(polegadas)) - sq(alturaCm));
}
