#ifndef TEMPORIZADOR_H
#define TEMPORIZADOR_H

#include <Arduino.h>

class Temporizador
{
    private: 
   uint8_t tempo;
   bool estaPronto = false;
   bool estaAtivo = false;
    bool estadoConfirmado = HIGH;
     bool flagAlteracao = false;
     bool flagreiniciar = false;
   bool flagparar = false;

   unsigned long tempo_ms = 1000;
   unsigned long tempoInicioTemporizador = 0;
   unsigned long tempocontagem = 0;
   unsigned long duracaoTemporizador = 0;




    public:
         Temporizador(uint8_t p); // construtor 

         void iniciar();
          void update();

         void parar();
         void  reiniciar();
         void  definirIntervalo();

 void configuraTemporizador(unsigned long tempo);



};








#endif