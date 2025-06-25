#include <Arduino.h>
#include <ezTime.h>
#include "internet.h"
#include <LiquidCrystal_I2C.h>
#include <Bounce2.h>

LiquidCrystal_I2C lcd(0x27, 20, 4); // Cria um objeto lcd da classe LiquidCrystal_I2C com endereço 0x27 e dimensões 20x4.
Timezone tempo; // Cria um objeto tempo da classe Timezone.
Bounce botaoBoot = Bounce(); // Cria um objeto botaoBoot da classe Bounce.

int dia = 0; // Declara uma variável inteira para armazenar o dia.
int mes = 0; // Declara uma variável inteira para armazenar o mês.
int ano = 0; // Declara uma variável inteira para armazenar o ano.
int hora = 0; // Declara uma variável inteira para armazenar a hora.
int minuto[2] = {0, 0}; // Declara um array de dois inteiros para armazenar o minuto atual e anterior.
int segundo[2] = {0, 0}; // Declara um array de dois inteiros para armazenar o segundo atual e anterior.
int diaSemana = 0; // Declara uma variável inteira para armazenar o dia da semana.
int diaAno = 0; // Declara uma variável inteira para armazenar o dia do ano.
bool formato24h = true; // Declara uma variável booleana para controlar o formato da hora (true para 24h).
bool manha = false; // Declara uma variável booleana para indicar se é AM (true) ou PM (false).

const char *diaSemanaTexto[] = { // Declara um array de ponteiros para caracteres (strings) com os dias da semana em português.
    "Domingo",
    "Segunda",
    "Terca",
    "Quarta",
    "Quinta",
    "Sexta",
    "Sabado"};

const char *mesTexto[] = { // Declara um array de ponteiros para caracteres (strings) com as abreviações dos meses em português.
  "jan",
  "fev",
  "mar",
  "abr",
  "mai",
  "jun",
  "jul",
  "ago",
  "set",
  "out",
  "nov",
  "dez",
};

void display(void); // Declara a função display que não retorna valor e não recebe argumentos.
void setup() {
  Serial.begin(9600); // Inicializa a comunicação serial com uma taxa de 9600 bauds.
  botaoBoot.attach(0, INPUT_PULLUP); // Associa o objeto botaoBoot ao pino digital 0 e configura o modo como INPUT_PULLUP.
  conectaWiFi(); // Chama a função conectaWiFi (definida na biblioteca "internet.h") para conectar à rede Wi-Fi.
  tempo.setLocation("America/Sao_Paulo"); // Define o fuso horário para "America/Sao_Paulo".
  waitForSync(); // Aguarda a sincronização do tempo com um servidor NTP.

  dia = tempo.day(); // Obtém o dia do mês atual.
  mes = tempo.month(); // Obtém o mês atual.
  ano = tempo.year(); // Obtém o ano atual.
  hora = formato24h ? tempo.hour() : tempo.hourFormat12(); // Obtém a hora no formato 24h ou 12h dependendo da variável formato24h.
  minuto[1] = tempo.minute(); // Obtém o minuto atual.
  segundo[1] = tempo.second(); // Obtém o segundo atual.
  diaSemana = tempo.weekday(); // Obtém o dia da semana (1 para Domingo, 7 para Sábado).
  diaAno = tempo.dayOfYear(); // Obtém o dia do ano (1 a 365 ou 366).
  manha = tempo.isAM(); // Verifica se a hora está no período AM.

  lcd.init(); // Inicializa o display LCD.
  lcd.backlight(); // Liga a luz de fundo do display LCD.

  display(); // Chama a função display para exibir as informações iniciais no LCD.
}

void loop() {
  botaoBoot.update(); // Atualiza o estado do botão para detectar mudanças.

  if (botaoBoot.fell()) { // Verifica se o botão foi pressionado (transição de HIGH para LOW).
    formato24h = !formato24h; // Inverte o valor da variável formato24h para alternar o formato da hora.
    if (!formato24h) { // Se o formato de 12 horas estiver ativo.
      lcd.setCursor(9, 2); // Define a posição do cursor na coluna 9, linha 2.
      lcd.printf("%s", manha ? "AM" : "PM"); // Imprime "AM" ou "PM" dependendo do valor da variável manha.
      lcd.setCursor(0,2); // Define a posição do cursor na coluna 0, linha 2.
      lcd.printf("%02d",tempo.hourFormat12()); // Imprime a hora no formato de 12 horas com dois dígitos.
    } else { // Se o formato de 24 horas estiver ativo.
      lcd.setCursor(9,2); // Define a posição do cursor na coluna 9, linha 2.
      lcd.print("   "); // Imprime três espaços para apagar "AM" ou "PM".
      lcd.setCursor(0, 2); // Define a posição do cursor na coluna 0, linha 2.
      lcd.printf("%02d",tempo.hour()); // Imprime a hora no formato de 24 horas com dois dígitos.
    }
  }

   void checkWiFi(); // Chama a função checkWiFi (definida na biblioteca "internet.h") para verificar a conexão Wi-Fi.
  segundo[1] = tempo.second(); // Atualiza o valor atual dos segundos.
  minuto[1] = tempo.minute(); // Atualiza o valor atual dos minutos.
  if (segundo[1] != segundo[0]) { // Verifica se o valor dos segundos mudou.
    lcd.setCursor(6, 2); // Define a posição do cursor na coluna 6, linha 2 (onde os segundos são exibidos).
    lcd.printf("%02d", segundo[1]); // Imprime o valor atual dos segundos com dois dígitos.
    segundo[0] = segundo[1]; // Atualiza o valor anterior dos segundos.
  }

  if (minuto[0] == 59 && minuto[1] == 0) { // Verifica se o minuto anterior era 59 e o minuto atual é 0 (mudança de hora).
    dia = tempo.day(); // Atualiza o dia.
    mes = tempo.month(); // Atualiza o mês.
    ano = tempo.year(); // Atualiza o ano.
    hora = tempo.hour(); // Atualiza a hora.
    diaSemana = tempo.weekday(); // Atualiza o dia da semana.
    diaAno = tempo.dayOfYear(); // Atualiza o dia do ano.
    manha = tempo.isAM(); // Atualiza o estado AM/PM.
    display(); // Chama a função display para atualizar todas as informações no LCD.
  }
  if (minuto[1] != minuto[0]) { // Verifica se o valor dos minutos mudou.
    lcd.setCursor(3, 2); // Define a posição do cursor na coluna 3, linha 2 (onde os minutos são exibidos).
    lcd.printf("%02d", minuto[1]); // Imprime o valor atual dos minutos com dois dígitos.
    minuto[0] = minuto[1]; // Atualiza o valor anterior dos minutos.
  }
}
void display() {
  lcd.setCursor(0, 0); // Define a posição do cursor na coluna 0, linha 0.
  lcd.printf("%02d/%s/%04d", dia, mesTexto[mes-1], ano); // Imprime a data no formato DD/MMM/AAAA.

  lcd.setCursor(16, 0); // Define a posição do cursor na coluna 16, linha 0.
  lcd.printf("%03d", diaAno); // Imprime o dia do ano com três dígitos.

  lcd.setCursor(0, 1); // Define a posição do cursor na coluna 0, linha 1.
  lcd.print(diaSemanaTexto[diaSemana - 1]); // Imprime o dia da semana por extenso.

  lcd.setCursor(0, 2); // Define a posição do cursor na coluna 0, linha 2.
  lcd.printf("%02d:%02d:%02d", hora, minuto[1], segundo[1]); // Imprime a hora, minutos e segundos no formato HH:MM:SS.
}