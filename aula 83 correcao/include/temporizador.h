#ifndef TEMPORIZADOR_H
#define TEMPORIZADOR_h

#include <Arduino.h>
class temporizador 
{
 private:
 unsigned long intervalo;
 bool ativo;
 unsigned long inicio;


 public: 
   temporizador(unsigned long tempo_ms = 1000 );
   void iniciar();
   void parar();
   bool  estaPronto();
   void reiniciar();
   bool estaAtivo();
   void definirIntervalo(unsigned long tempo_ms );
};



#endif