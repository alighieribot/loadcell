#include <SPI.h>
#include <SD.h>

// Chip select
#define SD_CS       4
#define SD_MOSI     11
#define SD_MISO     12
#define SD_SCLK     13

File dataFile;

void setup() {
  Serial.begin(9600);

  // Inicializa o SD
  if (!SD.begin(SD_CS)) {
    Serial.println("Falha ao inicializar o cartão SD");
    while (1); // Aguarda até a inserção do cartão SD
  }

  Serial.println("Cartão SD inicializado com sucesso");

  // Abre o arquivo
  dataFile = SD.open("dados.txt", FILE_WRITE);

  if (!dataFile) {
    Serial.println("Erro ao abrir o arquivo");
    dataFile = SD.open("dados.txt", FILE_WRITE);
    while (!dataFile); // Aguarda caso haja erro ao abrir o arquivo
  }

  Serial.println("Arquivo aberto com sucesso");

  // Escreve os dados
  dataFile.println("Dados");

  // Fecha o arquivo
  dataFile.close();

  Serial.println("Arquivo fechado");
}

void loop() {
  // O loop não executa nenhuma ação
}
