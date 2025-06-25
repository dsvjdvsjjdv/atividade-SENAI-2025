#include "Temporizador.h"

/**
 * @brief construtor da classe botao
 *
 * @param p numero do pino digital ao qual o botao esta conectado
 * */
Temporizador::Temporizador(uint8_t p) : tempo(p) {}

/**
 * @brief inicializa o temporizador
 *
 * configura o pino como entrada. o modo pull-up padrao
 */

void Temporizador::iniciar()
{
  pinMode(tempo, INPUT_PULLUP);
  estaAtivo = digitalRead(tempo);
  estaPronto = estaAtivo;
  estadoConfirmado = estaAtivo;
  tempo_ms = millis();
}
/**
 * @brief define o tempo de temporizador (debounce) para estabilizar as leituras do temporizador
 *
 * @param tempo tempo de debounce em millissegundos
 */
void Temporizador::configuraTemporizador(unsigned long tempo)
{
  tempo_ms = tempo;
}
/**
 * @brief defini o tempo do temporizador (debounce) ficara parado
 */
void Temporizador::parar()
{
  tempo_ms = tempocontagem--;
}
/**
 * @brief tempo que o temporizador reiniciara
 */
void Temporizador::reiniciar()
{
  estaAtivo = tempocontagem;
}
/**
 * @brief tempo de intervalo do esp ao parar e reiniciar
 */
void Temporizador::definirIntervalo()
{
   estaPronto = !estaAtivo;
}
/**
 * @brief Atualiza o estado interno do botao
 *
 * Deve ser chamada frequentemente dentro do loop principal
 * Detecta mudancas de estado e aciona as flags internas de
 * eventos do pressionado,solto e de mudanca de estado
 */
void Temporizador::update()
{
  unsigned long agora = millis();
  estaAtivo = digitalRead(tempo);

  if (estaAtivo != estaPronto)
    tempocontagem = agora;

  if ((agora - tempocontagem) > tempoInicioTemporizador)
  {
    if (estaAtivo != estadoConfirmado)
    {
      estadoConfirmado = estaAtivo;
      duracaoTemporizador = agora - tempoInicioTemporizador;
      tempoInicioTemporizador = agora;
      flagAlteracao = true;
    }
    estaPronto = estaAtivo;
  }
  
  
}