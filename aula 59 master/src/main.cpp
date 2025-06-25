#include <Arduino.h>
#include <BluetoothSerial.h>
#define pinLed 2 
 
 BluetoothSerial BT;
 uint8_t endSLave [] = {0x84, 0xCC, 0xAB, 0x5E, 0x71, 0x2E};


void setup() 
{pinMode(pinLed,OUTPUT);
  Serial.begin(9600); // inicia o serial
  
 //!                      ↓ indica que e master
  if(BT.begin("ESPRhuan",true)) // inicia a comunicacao  do bluetooth como master e retornando o resultado depois
  {
    Serial.println("Bluetooth iniciado com sucesso"); // mostra na serial se conectou
  }
  else 
{
  Serial.println("Erro ao inciar o Bluettoth"); // caso nao conecte

}

  
   if( BT.connect(endSLave)) // o endereco do dispositivo a ser conectado e retorna se conectou ou nao
{
  Serial.println("Conectado com sucesso"); // mostrar o serial se conectou com sucesso
}
else 
{
  Serial.println("Nao foi possivel conectar o dispositivo Bluetooth"); // caso de errado
}
  Serial.println(BT.getBtAddressString()); // mostra o endereco o fisico do bluetooth
}
 
void loop() 
{  
  if(Serial.available()) // ira avaliar a funcao
  {
    String mensagemEnviar = Serial.readStringUntil('\n'); // ira acabar quando encontrar um enter
    mensagemEnviar.trim(); // tira os espacos do final
    BT.println(mensagemEnviar); // enviara a mensagem do Bluettoh do colega
  }
  if(BT.available()) // ira receber a mensagem recebida
  {
    String mensagemRecebida = BT.readStringUntil('\n'); 
    mensagemRecebida.trim();
    Serial.println(" Mensagem Recebida " + mensagemRecebida);

    if(mensagemRecebida.equals("liga"))
    {
     digitalWrite(pinLed,HIGH);
    }
    else if(mensagemRecebida.equals("desliga"))
  {
   digitalWrite(pinLed,LOW);
  }
  }
}
