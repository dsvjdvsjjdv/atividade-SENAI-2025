#include <Arduino.h>
#include <PubSubClient.h>
#include <ArduinoJson.h>
#include <WiFiClientSecure.h>
#include "internet.h"
#include "certificados.h" 
#include <LiquidCrystal_I2C.h>
#include <Adafruit_NeoPixel.h>
 

const int mqtt_port = 8883;
const char *mqtt_id = "idDoEsp32";
const char *mqtt_SUB = "senai134/comandos";
const char *mqtt_PUB = "senai134/sensores";

WiFiClientSecure espClient;
PubSubClient mqtt(espClient);
LiquidCrystal_I2C lcd (0x27,28,4);
Adafruit_NeoPixel led(1,48,NEO_GBR);

void conectaMQTT();
void Callback(char *topic, byte *payload, unsigned int length); 

void setup()
{
  Serial.begin(9600);
  led.begin();
  led.setBrightness(32);
  led.show();





  conectaWiFi();

  espClient.setCACert(AWS_ROOT_CA);
  espClient.setCertificate(AWS_CERTY);
  espClient.setPrivateKey(AWS_KEY);

  mqtt.setServer(AWS_BROKER, mqtt_port);
  mqtt.setCallback(Callback);
}

void loop()
{
  checkWifi();

  led.setPixelColor(0,led.Color(225,0,0));
  led.show();

  if(!mqtt.connected())
  {
    conectaMQTT();
  }

  mqtt.loop();

  static unsigned long tempo_pub = 0;
  unsigned long agora = millis();

  if(agora - tempo_pub > 2000)

  {
    JsonDocument doc; 
    doc["msg"] = "Oieee";

    String mensagem;
    serializeJson (doc, mensagem);
    mqtt.publish(mqtt_PUB, mensagem.c_str());
    tempo_pub = agora;
  }

  //! mqtt.setCalback ();  //CRIAR O CALLBACK
}

void Callback(char *topic, byte *payload, unsigned int length)
{
  String msg((char *)payload, length);
  Serial.printf("Mensagem recebida (topico: [%s]): %s \n\r", topic, msg.c_str());
}

void conectaMQTT()
{
  while (mqtt.connected())
  {
    Serial.print("Conectando ao AWS Iot Core...");
    if (mqtt.connect(mqtt_id))
    {
      Serial.println("conectado.");
      mqtt.subscribe(mqtt_SUB);
    }
    else
    {
      Serial.printf("falhou (%d).  Tentando novamente em 5s \n\r", mqtt.state());
      delay(5000);
    }
  }
}