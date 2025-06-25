#ifndef BOTAO_H
#define BOTAO_H

#include <Arduino.h>

class botao
{
    private: 
   uint8_t pino;
   bool estadoAtual = HIGH;
   bool estadoAnterior = HIGH;
   bool estadoConfirmado = HIGH;
   bool flagAlteracao = false;
   bool flagPressionado = false;
   bool flagSolto = false;

   unsigned long tempoInicioEstado = 0;
   unsigned long tempoFiltro = 50;
   unsigned long tempoUltimaMudanca = 0;
   unsigned long duracaoEstado = 0;



    public:
         botao(uint8_t p); // construtor 

         void begin();
         void update();

         bool pressioado();
         bool solto();
         bool alteracaoEstado();
         unsigned long duracaoUltimoEstado();

         void configuraFiltro(unsigned long tempo);




};








#endif