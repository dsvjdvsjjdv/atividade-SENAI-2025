#include <Arduino.h>// biblioteca do arduino

const int pinBotao = 3; // constante inteira que define o botao

void ligaLed(int); // variavel inteira que ligao led
void desligaLed(int);// variavel inteira que desliga o led
void piscaLed(int, unsigned long);// variavel que ira piscar o led
int somaDeDoisNumeros(int, int); // variavel inteira que ira fazer uma soma

void setup()
{
  pinMode(2, OUTPUT); //definiu a saida do led
  Serial.begin(9600); // velocidade 
}

void loop()
{
  piscaLed(2, 100); // numero do led + o tempo que  ira piscar
  int resultadosDaSoma = somaDeDoisNumeros(4, 8); // variavel inteira que ira somar dois numeros
  Serial.println(resultadosDaSoma); // ira mostrar o resultado da soma
}

void ligaLed(int pin) // funcão que liga o led do tipo inteira 
{
  digitalWrite(pin, HIGH); // funcão que liga o led com o pino definido
}

void desligaLed(int pin) // funcão que desliga o led do tipo inteira
{
  digitalWrite(pin, LOW); // funcão que desliga o led com o pino definido
}

void piscaLed(int pin, unsigned long tempo) // funcão que pisca o led com uma variavel inteira e de tempo
{
  ligaLed(pin); // funcão que liga o led com o pino definido
  delay(tempo); // funcão para parar um codigo
  desligaLed(pin); // funcão que desliga o led com o pino definido
  delay(tempo); // funcão para parar um codigo
}
int somaDeDoisNumeros(int numeroA, int numeroB) // funcão com uma variavel inteira da soma de dois numeros , com duas variaveis inteiras com numeroA e numero B
{
  int resultado = numeroA + numeroB; // variavel inteira resultado da soma de numeroA + numeroB
  return resultado; // mostrara o resultado
}
