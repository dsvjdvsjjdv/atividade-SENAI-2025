#include "Led.h"



Led::Led(int pin)
{
    pino = pin;
    estadoLed = false;
    pinMode(pino,OUTPUT);
    digitalWrite(pino,LOW);
}
/**
 * @brief liga o led
 */
void Led::ligar()
{
    estadoLed = true;
    modoPiscar = false;
    digitalWrite(pino,estadoLed);
}
/**
 

 *@brief desliga o led
 */
void Led::desligar()
{
    estadoLed = false;
    modoPiscar = false;
    digitalWrite(pino,estadoLed);
}
/**
 * @brief inverte o led
 */
void Led::inverter()
{
    estadoLed = !estadoLed;
    digitalWrite(pino,estadoLed);
}
 /**
  * @brief pisca o led
  * @param frequencia frequencia em Hz que o led devera piscar
  */
void Led::piscar(float frequencia)
{
    if(frequencia ==0) return;
    intervalo =  1000.0/(frequencia * 2);
    ultimaTroca = millis();
    modoPiscar = true;
}
/**
 * @brief Funcao que atualiza o estado do led no modo piscar
 */
void Led::update()
{
    if(!modoPiscar) return;

    unsigned long agora = millis();
    if(agora - ultimaTroca >= intervalo)
    {
        inverter();
        ultimaTroca = agora;
    }
} 
int Led::getPino()
{
    return pino;
}
unsigned long Led::getIntervalo()
{
    return intervalo;
}