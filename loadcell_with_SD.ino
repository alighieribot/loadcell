/* Programa para célula de carga com o HX711
  Arduino UNO  - Modulo HX711 - celulas de Carga 1 ton
  Projeto Beyond Rocket Design   24/maio/2023
  Biblioteca https://github.com/bogde/HX711
*/

/*
 FIOS CÉLULA COM CABO PRETO:
 Vermelho:E+
 Preto:E-
 Branco:A-
 Verde:A+
 O fio restante é apenas uma malha.

 FIOS CÉLULA COM CABO CINZA:
 Vermelho:E+
 Amarelo:E-
 Branco:A-
 Verde:A+
 O fio preto é apenas uma malha.
*/

/* 
 Calibração (célula de carga com cabo preto): -4700
 Calibração (célula de carga com cabo cinza): 
 É necessário calcular um novo fator de calibração para cada célula de carga, segue o passo a passo para fazer isso:
 1. Rodar o código
 2. fatorDeCalibração = média dos valores no serial / peso conhecido em cima da célula de carga 
*/


#include <SPI.h>
#include <SD.h>
#include "HX711.h"

#define SD_CS       4               // chipSelect
// MOSI, MISO e SCLK são definidos por padrão no Arduino nos pinos:
#define SD_MOSI     11
#define SD_MISO     12
#define SD_SCLK     13
#define DOUT        2               // HX711 DATA OUT = pino A0 do Arduino 
#define CLK         3               // HX711 SCK IN = pino A1 do Arduino 

HX711 balanca;
File dataFile;

float calibration_factor = -4700;   // fator de calibração aferido na Calibraçao -4700
float valornilton;                  // variável de comparação
float units;                        // variável de leitura
float massa;                        // variável de leitura

void setup() {
  Serial.begin(9600);

  // Inicializa célula de carga com o fator de calibração aferido
  balanca.begin(DOUT, CLK);
  balanca.set_scale(calibration_factor);
  balanca.tare();

  // Inicializa o módulo SD 
  if (!SD.begin(SD_CS)) {
    Serial.println("Falha ao inicializar o cartão SD");
    while (1);                      // Aguarda até a inserção do cartão SD
  }

  Serial.println("Cartão SD inicializado com sucesso");

  // Abre o arquivo
  dataFile = SD.open("loadcell_data.txt", FILE_WRITE);

  if (!dataFile) {
    Serial.println("Erro ao abrir o arquivo");
    dataFile = SD.open("loadcell_data.txt", FILE_WRITE);
    while (!dataFile);              // Aguarda caso haja erro
  }

  Serial.println("Arquivo aberto com sucesso");

  // Escreve os dados iniciais no arquivo
  dataFile.println("Dados Iniciais");
  dataFile.close();

  Serial.println("Arquivo fechado");
}

void loop() {
  massa = balanca.get_units();
  valornilton = massa * 9.785 * 0.237;

  Serial.print("Massa: ");
  Serial.print(balanca.get_units(), 3);
  Serial.print(" kg     ");
  Serial.print("Torque: ");
  Serial.print(valornilton, 3);
  Serial.println(" NM");

  // Abre o arquivo no modo de adição
  dataFile = SD.open("data_loadcell.txt", FILE_WRITE);
  if (dataFile) {
    // Escreve os dados da célula de carga no arquivo
    dataFile.print("Massa: ");
    dataFile.print(balanca.get_units(), 3);
    dataFile.print(" kg     ");
    dataFile.print("Torque: ");
    dataFile.print(valornilton, 3);
    dataFile.println(" NM");

    // Fecha o arquivo
    dataFile.close();
  } else {
    Serial.println("Erro ao abrir o arquivo");
  }

  if (Serial.available()) {
    char temp = Serial.read();
    if (temp == 't' || temp == 'T') {
      balanca.tare();
      Serial.println("Balança zerada");
    }
  }
  // >>>REMOVA O DELAY ANTES DO TESTE<<<
  delay(1000);              
}
