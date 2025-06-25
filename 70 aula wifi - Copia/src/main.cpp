#include <Arduino.h>
#include <WiFi.h>
//*------CONFIGURACAO DO WIFI---------
const char *SSID = "MQTT";      // rede wifi
const char *SENHA = "info@134"; // semha do wifi
const unsigned long tempoEsperaConexao = 15000;
const unsigned long tempoEsperaReconexao = 5000;

//*----------- PROTOTIPOS DA FUNCOES -------
void conectaWiFi(void);
void checkWifi(void);

void setup()
{
  Serial.begin(9600);
  conectaWiFi();
}

void loop()
{
 checkWifi();
} 

void conectaWiFi()
{

  Serial.printf("Conectando ao WiFi: %s", SSID); // frase para mostrar conectado

  WiFi.begin(SSID, SENHA); // semha

  unsigned long tempoInicialWiFi = millis();
  while (WiFi.status() != WL_CONNECTED && millis() - tempoInicialWiFi < tempoEsperaConexao) // se conectado mostrar 3
  {
    Serial.print(".");
    delay(500);
  }
  if (WiFi.status() == WL_CONNECTED)
  {
    Serial.println("\nWiFi Conectado com sucesso!");
    Serial.print("Endeco IP :");
    Serial.println(WiFi.localIP());
  }
  else
  {
    Serial.println("\nFalha ao conectar no WiFi.Verifique o nome da rede e a senha");
  }
}

void checkWifi()
{

   unsigned long tempoAtual = millis();
  static unsigned long tempoUltimaConexao = 0;
  if (tempoAtual - tempoUltimaConexao > tempoEsperaReconexao)
  {
    checkWifi();
    tempoUltimaConexao = tempoAtual;
  }
  if (WiFi.status() != WL_CONNECTED)
  {
    Serial.println("\n Conexao Perdida! Tentando reconectar...");
    conectaWiFi();
  }
}