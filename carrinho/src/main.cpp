#include <Arduino.h>
#include <BluetoothSerial.h>
BluetoothSerial BT;
#define pinLed 25



void setup()
{
  Serial.begin(9600);

  pinMode(2,OUTPUT);
  
  if (BT.begin("espSlaveRhuan"))
  {
    Serial.println("Bluetooth inciado com sucesso");
  }

  else
  {
    Serial.println("Erro ao iniciar o Bluettoth");
  }
}

void loop()
{
  static bool estadoLed = false;
  static bool piscaled = false;
   if (Serial.available()) // ira avaliar a funcao
   {
     String mensagemEnviar = Serial.readStringUntil('\n'); // ira acabar quando encontrar um enter
 mensagemEnviar.trim();                                // tira os espacos do final
     BT.println(mensagemEnviar);                           // enviara a mensagem do Bluettoh do colega
  }
  if (BT.available()) // ira receber a mensagem recebida
  {
    String mensagemRecebida = BT.readStringUntil('\n');
    mensagemRecebida.trim();
    Serial.println(" Mensagem Recebida " + mensagemRecebida);

    if (mensagemRecebida.equals("liga"))
    {
    }
    else if (mensagemRecebida.equals("desliga"))
    {
    }
    if (mensagemRecebida.equals("setaE"))
    {
      Serial.printf("←---");
    }
    else
  {
    Serial.printf("   ");
  }
  if(mensagemRecebida.equals("setaD"))
  {
    Serial.printf("---→");
  }
  else 
  {
    Serial.printf("   ");
  }
  if(mensagemRecebida.equals("LedA"))
  {
    estadoLed = (pinLed);
    delay(200);
    estadoLed = true;
    delay(200);
    estadoLed = false;


    
  }
  
  
  if (BT.available())
   
  {
    String mensagem = BT.readStringUntil('\n');
    mensagem.trim();

    if (mensagem.equals("Liga"))
    { 
      estadoLed = true;
      piscaled = true;
      BT.println("LED LIGADO");
    }
    else if (mensagem.equals("Desliga"))
    {
      estadoLed = false;
      piscaled = false;
      BT.println("LED DESLIGADO");
    }
    
  }
  digitalWrite(pinLed,HIGH);
  }
}