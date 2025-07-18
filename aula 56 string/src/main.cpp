#include <Arduino.h>

// *formas de escrever palavras em C:

char palavra[10] = "OLA MUNDO"; // QUNATIDADE DE PALAVRAS
char palavra2[10] = {'O', 'L', 'A', ' ', 'M', 'U', 'N', 'D', 'O', '\0'};

String palavra3 = "HOJE EH QUINTA";

void setup()
{
  Serial.begin(9600);
  Serial.println();
  Serial.println(palavra);

  strcpy(palavra, "SENAI"); // STR + COPIA

  if (strcmp(palavra, "SENAI") == 0) // SE FOR IGUAL RETORNA ZERO//
  {
    Serial.println("SAO IGUAIS");
  }

  if (strncmp(palavra2, "OLA", 3) == 0)
  {
    Serial.println("As primeiras letras da palavra e OLA");
  }
  if (strstr(palavra2, "MUNDO"))
  {
    Serial.println("Palavra MUNDO detectada");
  }

  Serial.println(palavra3.length());          // retorna o numero de letras do objeto da classe String
  Serial.println(palavra3.charAt(8));         // retorna a oitava posicao da letra da palavra.
  Serial.println(palavra3.substring(8, 14));  // retorna a oitava posicao ate a 14 posicao.
  Serial.println(palavra3.indexOf('U'));      // retorna a posicao da primeira ocorrencia da letra procurada
  Serial.println(palavra3.lastIndexOf('E'));  // retorna a posicao ultima ocorrencia da letra procurada
  if (palavra3.equals("HOJE EH QUINTA") == 1) // retorna verdade se forem iguais
    Serial.println("Sao iguais");

  if (palavra3.equalsIgnoreCase("hoje eh quinta") == 1) // retorna verdadeiro se forem iguais ignorando letras maisculas/minusculas
    Serial.println("Sao iguais");

  if (palavra3.startsWith("HOJE") == 1) // retorna verdadeiro se a palavra comecar com determinado texto
    Serial.println("Comeca com HOJE");

  if (palavra3.endsWith("INTA") == 1) // retorna verdadeiro se a palavra terminar com determinado texto
    Serial.println("Termina com INTA");

  String valor = "123";
  int valorNumerico = valor.toInt(); // retorna o valor do texto em valor numerico de "123" para "123"(numero)

  String valor2 = "10.5";
  float valorNumerico2 = valor2.toFloat();
//EXEMPLO: transforme o numero do texto em valor numerico tipo inteiro
  String mensagem = "Valor = 50";
  int tamanho = mensagem.length(); // Medir o tamanho do texto
  String extracao = mensagem.substring(8, tamanho); // extrair o numero iniciando  em uma posicao conhecida ate o fim do texto
  
  Serial.println(tamanho); 
  Serial.println(extracao);

  int numero = extracao.toInt(); // transforme o conteudo extraido em um numero inteiro
  Serial.println(numero * 2); // utilize o numero sem moderacao ... HAHAHA 

  palavra3.toLowerCase(); // Alterar todas as letras para minusculas
  Serial.println(palavra3);
  palavra3.toUpperCase(); // Alterar todas as letras para maiusculas
  Serial.println(palavra3);

  String textoled = "Led = ON";
Serial.println(textoled);
textoled.replace("ON", "OFF"); // substitui uma palavra no texto por outra
Serial.println(textoled); // "led = off"

String novaFrase = "Texto       "; // varios espacos
novaFrase.trim(); // remove os espaços do fim do do texto

novaFrase.concat(" adicionando"); //adiciona um texto a string 
Serial.println(novaFrase);


}

void loop()
{
}.