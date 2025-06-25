#include <WiFi.h>
#include <WiFiClientSecure.h>
#include <PubSubClient.h>
#include <ArduinoJson.h>
#include <Bounce2.h>
#include <Adafruit_NeoPixel.h>
#include <LiquidCrystal_I2C.h>
#include "internet.h"
#include "certificados.h"
#include <Arduino.h>

#define botao 0

// Broker MQTT
const int mqtt_port = 8883;
const char *mqtt_id = "idDoEsp32/lembretes";
const char *mqtt_sub = "senai134/mesa04";
const char *mqtt_pub = "senai134/mesa04";

// Objeto LCD
LiquidCrystal_I2C lcd(0x27, 16, 2);

// Conexões MQTT
WiFiClientSecure espClient;
PubSubClient mqtt(espClient);
Adafruit_NeoPixel ledRGB(1, 48, NEO_GRB);
Bounce boot = Bounce();

void Callback(char *topic, byte *payLoad, unsigned int Length);
void ConectaMQTT();
void controleLED();

bool novaMensagem = false;

unsigned long ultimoBlink = 0;
bool ledLigado = false;

void setup()
{
  Serial.begin(9600);
  conectaWiFi();

  boot.attach(botao, INPUT_PULLUP);

  ledRGB.begin();
  ledRGB.setBrightness(255);
  ledRGB.setPixelColor(0, ledRGB.Color(0, 0, 0));
  ledRGB.show();

  lcd.init();
  lcd.backlight();

  espClient.setCACert(AWS_ROOT_CA);
  espClient.setCertificate(AWS_CERT);
  espClient.setPrivateKey(AWS_KEY);

  mqtt.setServer(AWS_BROKER, mqtt_port);
  mqtt.setCallback(Callback);
}

void loop()
{
  checkWiFi();
  boot.update();

  if (!mqtt.connected())
  {
    ConectaMQTT();
  }
  mqtt.loop();

  controleLED();
}

void Callback(char *topic, byte *payLoad, unsigned int Length)
{
  String mensagem((char *)payLoad, Length);

  Serial.print("Payload recebido:");
  Serial.print(mensagem);

  JsonDocument doc;
  DeserializationError error = deserializeJson(doc, mensagem);
  if (error)
  {

    Serial.print("Erro ao parear JSON: ");
    Serial.print(error.f_str());
    return;
  }
  const char *lembrete = doc["lembrete"];
  if (lembrete)
  {
    Serial.print("Lembrete recebido:");
    Serial.println("lembrete");
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Lembrete: ");
    lcd.setCursor(0, 1);
    lcd.print(lembrete);

    novaMensagem = true;
  }
  else
  {
    Serial.println("Campo 'lembrete' nao encontrado no JSON.");
  }
}

void ConectaMQTT()
{
  while (!mqtt.connected())
  {
    Serial.print("Conectando ao AWS IoT core ...");
    if (mqtt.connect(mqtt_id))
    {
      Serial.println("conectado.");
      mqtt.subscribe(mqtt_sub);
    }
    else
    {
      Serial.print("Falha, rc=");
      Serial.print(mqtt.state());
      delay(2000);
    }
  }
}

void controleLED()
{
  if (!novaMensagem)
  {
    ledRGB.setPixelColor(0, ledRGB.Color(0, 0, 0));
    ledRGB.show();
    return;
  }

  if (boot.fell())
  {
    novaMensagem = false;
    ledRGB.setPixelColor(0, ledRGB.Color(0, 0, 0));
    ledRGB.show();
    return;
  }

  if (millis() - ultimoBlink >= 500)
  {
    ultimoBlink = millis();
    ledLigado = !ledLigado;
    ledRGB.setPixelColor(0, ledRGB.Color(255, 8, 32));
    ledRGB.show();
  }
}