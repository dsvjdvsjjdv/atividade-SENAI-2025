#include <Arduino.h>
#include <BluetoothSerial.h>
#include <Bounce2.h>
#include <ArduinoJson.h> //biblioteca JSON(java script object notation)
#include <LiquidCrystal_I2C.h>

// Definições
char enderecoSlave[] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
#define num_botoes 7
#define pinBotaoA 13
#define pinBotaoB 12
#define pinBotaoC 14
#define pinBotaoD 27
#define pinBotaoE 26
#define pinBotaoF 25
#define pinBotaoK 33
#define pinAnalogicoX 32
#define pinAnalogicoY 35
const char pinjoystick[num_botoes] = {
    pinBotaoA,
    pinBotaoB,
    pinBotaoC,
    pinBotaoD,
    pinBotaoE,
    pinBotaoF,
    pinBotaoK}; // A,B,C,D,E,F,K
// objetos

BluetoothSerial BT;
Bounce *joystick = new Bounce[num_botoes];
JsonDocument doc;
LiquidCrystal_I2C lcd(0x27, 20,4);

// variaveis

// prototipo de funções

void reconectarBT();
void iniciarBT();

enum pinsBotoes
{
  botaoA = 0,
  botaoB = 1,
  botaoC = 2,
  botaoD = 3,
  botaoE = 4,
  botaoF = 5,
  botaoK = 6,

};

void setup()
{

  Serial.begin(9600);
  lcd.init();
  lcd.backlight();
  lcd.print("teste");
  iniciarBT();

  for (char i = 0; i < num_botoes; i++)
  {
    joystick[i].attach(pinjoystick[i], INPUT_PULLUP);
    
  }
}

void loop()
{
  bool atualizacao = false;
  int mudancaBotoes[num_botoes] = {0, 0, 0, 0, 0, 0, 0};
  int estadoBotoes[num_botoes] = { 0,0, 0, 0, 0, 0, 0};

  static int analogicoAnterior[2] = {19,19};
  int analogicoAtual[2] = {analogRead(pinAnalogicoX)/100, analogRead(pinAnalogicoY)/100};
  doc.clear();
  for (char j = 0; j < num_botoes; j++)
  {
    joystick[j].update();
    if (joystick[j].changed())
    {
      char chave[10];
      sprintf(chave, "botao%d", j);
      doc[chave] = !joystick [j].read();
      mudancaBotoes[j] = 1;
      estadoBotoes[j] = joystick[j].read();
      atualizacao = true;
    }
  }

  if(analogicoAtual[0]!= analogicoAnterior[0] )
{
  doc["anX"] = analogicoAtual[0];
  atualizacao = true;
}

if (analogicoAtual[1]  != analogicoAnterior[1])
{
  doc["anY"] = analogicoAtual[1];
  atualizacao = true;
}

analogicoAnterior[0] = analogicoAtual[0];
analogicoAtual [1] = analogicoAtual [1];

  String payload;
  if (atualizacao)
  {

    serializeJson(doc, payload);
    Serial.println(payload);
  }
  if (BT.connect())
  {
    BT.println(payload);
  }
  else
  {
    reconectarBT();
  }
  if(atualizacao)
  {
    for(int i = 0; i< num_botoes; i++)
    {
      if(mudancaBotoes[i])
      {
        lcd.setCursor(0,0);
        lcd.printf("Botoes %d esta %s", i, estadoBotoes ? "Pressionado" : "solto");
      }
    }
  }
}

void reconectarBT()
{
  if (BT.connect())
  {
    return;
  }
  Serial.println("tentando conectar...");
  BT.end();
  delay(1000);
  iniciarBT();
}

void iniciarBT()
{
  bool iniciouSucesso = BT.begin("Master-RHUAN", true);
  if (iniciouSucesso)
  {
    Serial.println("o Bluetooth iniciou o master com sucesso");
  }
  else
  {
    Serial.println(" erro ao conectar o Bluetooth ");
    Serial.println("o esp sera iniciado em:");
    for (char i = 5; i > 0; i--)
    {
      Serial.printf("%d.......\n\r", i);
      delay(100);
    }
    ESP.restart();
  }
  Serial.println("Tentando conectar ao slave");
  if (BT.connect(enderecoSlave))
  {
    Serial.println("Conectado ao Slave com sucesso");
  }
  else
  {
    Serial.println("Nao foi possivel conectar ao slave");
  }
}