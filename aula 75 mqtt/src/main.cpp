#include <Arduino.h>
#include <PubSubClient.h>
#include "Internet.h"
#include <WiFi.h>
#include <DHT.h>
#include <ArduinoJson.h>
#include <Bounce2.h>
#include "Led.h"
#define LED_H 
const char *mqtt_server = "test.mosquitto.org";
const int mqtt_port = 1883;
const char *mqtt_client_id = "Rhuan";
const char *mqtt_topic_sub = "senai134/mesa04/Leticia/espsub";
const char *mqtt_topic_pub = "senai134/mesa04/Leticia/esppub";

WiFiClient espClient;
PubSubClient client(espClient);
DHT dht(23, DHT22);
JsonDocument Doc;

const int pinLed = 2;
bool estadoLed = false;
bool pisca = false;
int tempoLed = 500;
int pino;

void callback(char *, byte *, unsigned int);
void conectaMQTT(void);
void ligar();
  void desligar();
  void inverter();

  void piscar(float frequencia);
  void update();
  int getPino();

  unsigned long getIntervalo();
 
void setup()
{
  Serial.begin(9600);
  dht.begin();

  delay(2000);

  Serial.println(dht.readTemperature());
  Serial.println(dht.readHumidity());

  pinMode(2, OUTPUT);
  conectaWiFi();

  client.setServer(mqtt_server, mqtt_port);
  client.setCallback(callback);

}
void loop()
{
  checkWifi();

  if (!client.connected())
  {
    conectaMQTT();
  }

  client.loop();
  unsigned long tempoAnteriorPisca = 0;
  static unsigned long tempoAnterior = 0;
  unsigned long tempoAtual = millis();

  if (tempoAtual - tempoAnterior > 2000)
  {
    client.publish(mqtt_topic_pub, "OI");
    tempoAnterior = tempoAtual;
  }

  if (pisca)
  {
    if (tempoAtual - tempoAnteriorPisca > tempoLed)
    {
      estadoLed = !estadoLed;
      tempoAnteriorPisca = tempoAtual;
    }
  }
}
void callback(char *topic, byte *payload, unsigned int length)
{
  Serial.print("mensagem Recebida em ");
  Serial.print(topic);
  Serial.print(": ");
  String mensagem = "";
  static unsigned long tempoAnterior = 0;
  unsigned long tempoAtual = millis();

  for (int i = 0; i < length; i++)
  {
    char c = ((char)payload[i]);
    mensagem += c;
    Serial.println(mensagem);

  }
  

  JsonDocument doc;
  DeserializationError erro = deserializeJson(doc, mensagem);

  if (erro)
  {
    Serial.printf("erro %s no formato json", erro.c_str());
  }
  else
  {
    if (!Doc["estadoLed"].isNull())

    {
      int acaoLed = doc["estadoLed"];

      switch (acaoLed)
      {
      case 0:
        estadoLed = false;
        pisca = false;
        break;

      case 1:
        estadoLed = true;
        pisca = false;
        break;

      case 2:
        pisca = true;
        break;

      default:
        Serial.print("opcao nao implementada");
        break;
      }
    }

    if (!doc["tempo"].isNull())
    {
      tempoLed = Doc["tempo"];
    }
  }
}
void conectaMQTT()
{
  while (!client.connected())
  {
    Serial.print("Conectado ao MQTT....");
    if (client.connect(mqtt_client_id))
    {
      Serial.println("conectado!");
      client.subscribe(mqtt_topic_sub);
    }
    else
    {
      Serial.print("Falha, rc=");
      Serial.print(client.state());
      Serial.println(" tentando novamente em 5 segundos");
      delay(5000);
    }
  }
  
}