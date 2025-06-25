#include "botao.h"



/**
 * @brief construtor da classe botao
 *
 * @param p numero do pino digital ao qual o botao esta conectado
 * */
botao::botao(uint8_t p) : pino(p) {}

/**
 * @brief inicializa o botao 
 * 
 * configura o pino como entrada. o modo pull-up padrao
 */


void botao::begin()
{
  pinMode(pino,INPUT_PULLUP); 
  estadoAtual = digitalRead(pino);
  estadoAnterior = estadoAtual;
  estadoConfirmado = estadoAtual;
  tempoInicioEstado = millis();
}
/**
 * @brief define o tempo de filtro (debounce) para estabilizar as leituras do botao
 * 
 * @param tempo tempo de debounce em millissegundos
 */
void botao::configuraFiltro(unsigned long tempo)
{
  tempoFiltro = tempo;
}
/**
 * @brief Atualiza o estado interno do botao
 * 
 * Deve ser chamada frequentemente dentro do loop principal
 * Detecta mudancas de estado e aciona as flags internas de 
 * eventos do pressionado,solto e de mudanca de estado
 */
void botao::update()
{
    unsigned long agora = millis();
    estadoAtual = digitalRead(pino);
    flagAlteracao = false;
    flagPressionado = false;
    flagSolto = false;

    if(estadoAtual != estadoAnterior)
    tempoUltimaMudanca = agora;

    if((agora - tempoUltimaMudanca) > tempoFiltro)
    {
      if(estadoAtual != estadoConfirmado )
      {
        estadoConfirmado = estadoAtual;
        duracaoEstado = agora - tempoInicioEstado;
        tempoInicioEstado = agora;
        flagAlteracao = true;

        if(!estadoAtual) // botao Pressionado
        {
            flagPressionado = true;
        }
        else // botao solto
        {
            flagSolto = true;
        }
      }
    }
    estadoAnterior = estadoAtual;
}
/**
 * @brief verifica se o botao acabou de ser pressionado
 * 
 * @return true se tiver uma transicao para o estado pressionado na ultima atualizacao
 */
bool botao::pressioado()
{
 return flagPressionado;
}
/**
 * @brief verifica se o botao acabou de ser solto
 * 
 * @return true se houve uma trasicao para o estado solto na ultima atualizacao
 */
bool botao::solto()
{
    return flagSolto;
}

/**
 * @brief Verifica se houve uma mudanca de estado do botao
 * 
 * @return true se o estado do botao mudou (pressionado ou solto )
 * na ultima atualizacao
 */
bool botao::alteracaoEstado()
    {
        return flagAlteracao;
    }
    /**
     * @brief Retorna a duracao do ultimo estado mantido (pressionado ou solto)
     * 
     * @return tempo em millissegundos que o botao permaneceu no ultimo estado
     */
    unsigned long botao::duracaoUltimoEstado()
    {
        return duracaoEstado;
    }
