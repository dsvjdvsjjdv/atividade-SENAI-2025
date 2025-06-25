#include "botao.h"

Botao::Botao(int boot)
{
    botaoboot = boot;
    estadobotao;
    BotaoPressionado = false;
    
}
/**
 * @brief botao e pressionado
 */
void Botao::Botaopressionado()
{
    estadobotao = true;
    BotaoPressionado = false;
    
}
/**
 

 *@brief botao solto
 */
void Botao::BotaoSolto()
{
    estadobotao = false;
    BotaoPressionado= false;
    
}



/**
 * @brief Funcao que atualiza o estado do botao no modo piscar
 */
void Botao::update()
{
    if(!tempoBotaopressionado) return;

    unsigned long agora = millis();
    if(agora - botaoSolto >= intervalo)
    {
        inverter();
        botaoSolto = agora;
    }
}


