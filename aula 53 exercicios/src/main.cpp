#include <Arduino.h>
#include <Bounce2.h>
#include <LiquidCrystal_I2C.h>

#define pinBotaoA 19
#define pinBotaoB 18
#define pinBotaoC 5

// Instancia de Objetos
Bounce botaoA = Bounce();
Bounce botaoB = Bounce();
Bounce botaoC = Bounce();

LiquidCrystal_I2C lcd(0x27, 20, 4);

// Prototipo das Funcoes
void apagarCaracterLcd(byte, byte);

// Criacao de Variaveis

// Vetor com os pinos dos Leds
byte pinLeds[4] = {12, 14, 27, 26};

void setup()
{
  Serial.begin(9600);

  botaoA.attach(pinBotaoA, INPUT_PULLUP);
  botaoB.attach(pinBotaoB, INPUT_PULLUP);
  botaoC.attach(pinBotaoC, INPUT_PULLUP);

  for (byte i = 0; i < sizeof(pinLeds); i++)
  {
    pinMode(pinLeds[i], OUTPUT);
  }

  lcd.init();
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print(">LED 1 - Des.");
  lcd.setCursor(0, 1);
  lcd.print(" LED 2 - Des.");
  lcd.setCursor(0, 2);
  lcd.print(" LED 3 - Des.");
  lcd.setCursor(0, 3);
  lcd.print(" LED 4 - Des.");
}

void loop()
{
  static bool modoSelecao = 1;
  static int contador = 0;
  static bool alteracao = 0;

  static int itnsLedA = 0;
  static int itnsLedB = 0;
  static int itnsLedC = 0;
  static int itnsLedD = 0;

  botaoA.update();
  botaoB.update();
  botaoC.update();

  // Botao C pressionado
  if (botaoC.fell())
  {
    alteracao = 1;
    modoSelecao = !modoSelecao;
  }

  // Botao B pressionado
  if (botaoB.fell())
  {
    alteracao = 1;
    if (modoSelecao)
    {
      contador++;
      if (contador > 3)
        contador = 0;
    }
    else
    {
      if (contador == 0 && itnsLedA > 0)
        itnsLedA -= 10;
      else if (contador == 1 && itnsLedB > 0)
        itnsLedB -= 10;
      else if (contador == 2 && itnsLedC > 0)
        itnsLedC -= 10;
      else if (contador == 3 && itnsLedD > 0)
        itnsLedD -= 10;
    }
  }

  // Botao A pressionado
  if (botaoA.fell())
  {
    alteracao = 1;
    if (modoSelecao)
    {
      contador--;
      if (contador < 0)
        contador = 3;
    }
    else
    {
      if (contador == 0 && itnsLedA < 100)
        itnsLedA += 10;
      else if (contador == 1 && itnsLedB < 100)
        itnsLedB += 10;
      else if (contador == 2 && itnsLedC < 100)
        itnsLedC += 10;
      else if (contador == 3 && itnsLedD < 100)
        itnsLedD += 10;
    }
  }

  // LCD
  if (alteracao) // executa somente se ouve alteração, ou seja, quando um botao for pressionado
  {
    alteracao = 0;

    if (modoSelecao) // modoSelecao == true
    {
      if (contador == 0) // verifica o valor da variavel contador, utilizado para posicionar a seta
      {
        lcd.setCursor(0, 0);
        lcd.print(">");

        apagarCaracterLcd(8, 0);
        apagarCaracterLcd(0, 1);
        apagarCaracterLcd(0, 3);
      }
      else if (contador == 1)
      {
        lcd.setCursor(0, 1);
        lcd.print(">");

        apagarCaracterLcd(8, 1);
        apagarCaracterLcd(0, 0);
        apagarCaracterLcd(0, 2);
      }
      else if (contador == 2)
      {
        lcd.setCursor(0, 2);
        lcd.print(">");

        apagarCaracterLcd(8, 2);
        apagarCaracterLcd(0, 1);
        apagarCaracterLcd(0, 3);
      }
      else // é 3
      {
        lcd.setCursor(0, 3);
        lcd.print(">");

        apagarCaracterLcd(8, 3);
        apagarCaracterLcd(0, 2);
        apagarCaracterLcd(0, 0);
      }
    }
    else // modoSelecao == false
    {
      if (contador == 0)
      {
        lcd.setCursor(8, 0);
        lcd.print(">");

        apagarCaracterLcd(0, 0);
        apagarCaracterLcd(8, 1);
        apagarCaracterLcd(8, 3);

        lcd.setCursor(9, 0);
        if (itnsLedA == 100)
          lcd.print("Max.");
        else if (itnsLedA == 0)
          lcd.print("Des.");
        else
          lcd.print(itnsLedA);
        lcd.print("  ");
      }
      else if (contador == 1)
      {
        lcd.setCursor(8, 1);
        lcd.print(">");

        apagarCaracterLcd(0, 1);
        apagarCaracterLcd(8, 0);
        apagarCaracterLcd(8, 2);

        lcd.setCursor(9, 1);
        if (itnsLedB == 100)
          lcd.print("Max.");
        else if (itnsLedB == 0)
          lcd.print("Des.");
        else
          lcd.print(itnsLedB);
        lcd.print("  ");
      }
      else if (contador == 2)
      {
        lcd.setCursor(8, 2);
        lcd.print(">");

        apagarCaracterLcd(0, 2);
        apagarCaracterLcd(8, 1);
        apagarCaracterLcd(8, 3);

        lcd.setCursor(9, 2);
        if (itnsLedC == 100)
          lcd.print("Max.");
        else if (itnsLedC == 0)
          lcd.print("Des.");
        else
          lcd.print(itnsLedC);
        lcd.print("  ");
      }
      else // é 3
      {
        lcd.setCursor(8, 3);
        lcd.print(">");

        apagarCaracterLcd(0, 3);
        apagarCaracterLcd(8, 2);
        apagarCaracterLcd(8, 0);

        lcd.setCursor(9, 3);
        if (itnsLedD == 100)
          lcd.print("Max.");
        else if (itnsLedD == 0)
          lcd.print("Des.");
        else
          lcd.print(itnsLedD);
        lcd.print("  ");
      }
    }

    // LEDs
    analogWrite(12, itnsLedA * 2.55);
    analogWrite(pinLeds[1], itnsLedB * 2.55);
    analogWrite(pinLeds[2], itnsLedC * 2.55);
    analogWrite(pinLeds[3], itnsLedD * 2.55);
  }
}

void apagarCaracterLcd(byte numCol, byte numLin)
{
  lcd.setCursor(numCol, numLin);
  lcd.print(" ");
}