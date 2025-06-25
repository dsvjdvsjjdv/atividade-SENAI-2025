#include <Arduino.h>
#include <BluetoothSerial.h>




BluetoothSerial  BT;
uint8_t endSlave[]; 

void setup() 
{
  Serial.begin(9600); // inicia o serial 
  BT.begin("ESPRhuan"); // inicia a comunicacao  do bluetooth como master e retornando o resultado depois
  
   BT.connect(endSlave); // o endereco do dispositivo a ser conectado e retorna se conectou ou nao

  Serial.println(BT.getBtAddressString()); // mostra o endereco o fisico do bluetooth
}



void loop() 
{
 
}