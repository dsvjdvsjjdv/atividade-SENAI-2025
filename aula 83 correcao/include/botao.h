#ifndef BOTAO_H
#define BOTAO_H

#include <Arduino.h>

class Botao
{
private: // Atributos(caracterisitcas)
  int botaoboot;
  bool estadobotao;
  bool BotaoPressionado = false;
  unsigned long botaoSolto = 0; 
  unsigned long tempoBotaopressionado = 0;
  unsigned long intervalo = 0;
  



public:         // Metodos)(acoes)
  
  
  Botao(int boot); // Metodo construtor tem o mesmo nome da classe
  bool  Botaopressionado();
  bool BotaoSolto();
  void  update();
   bool inverter();

};

#endif