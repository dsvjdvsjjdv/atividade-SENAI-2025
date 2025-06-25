#include "temporizador.h"

temporizador::temporizador(unsigned long tempo_ms)
{
    intervalo = tempo_ms;
    ativo = false;
}


void temporizador::iniciar()
{
    inicio = millis();
    ativo = true;
}

void temporizador::parar()
{
    ativo = false;
}

bool temporizador::estaPronto()
{
    return ativo && ((millis() - inicio) >= intervalo);
}

void temporizador::reiniciar()
{
    inicio = millis();
}

bool temporizador::estaAtivo()
{
    return ativo;
}

void temporizador::definirIntervalo(unsigned long tempo_ms)
{
    intervalo = tempo_ms;
}