/* Programa para célula de carga com o HX711
  Arduino UNO  - Modulo HX711 - celulas de Carga 1 ton
  Projeto Beyond Rocket Design   29/maio/2023
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

// Biblioteca HX711
#include "HX711.h"                                     


#define DOUT  2 // HX711 DATA OUT = pino A0 do Arduino                                    
#define CLK  3 // HX711 SCK IN = pino A1 do Arduino                                      

// Define instância balança HX711
HX711 balanca;                                        

   float calibration_factor = -4700;                 // fator de calibração aferido na Calibraçao -4700
   float valornilton;                                 // variável de comparação
   float units;                                       // variável de leitura
   float massa;                                       // variável de leitura
   void setup()
{
  Serial.begin(9600);
  balanca.begin(DOUT, CLK);                          // inicializa a balança
  Serial.println("Balança com HX711 - celula de carga ");            
  Serial.println("PRESSIONE t PARA TARA  ");          // imprime no monitor serial
  balanca.set_scale(calibration_factor);             // ajusta fator de calibração
  balanca.tare();                                    // zera a Balança
}

void loop()
{
  massa=balanca.get_units();
  valornilton=massa*9.785*0.237; //cálculo para o Torque da máquina
  Serial.print("Massa: ");                            // imprime no monitor serial
  Serial.print(balanca.get_units(), 3) ;             // imprime peso na balança com 3 casas decimais 
  Serial.print(" kg     ");                          // imprime no monitor serial 
  
  Serial.print("Torque: ");
  Serial.print((valornilton),3);                     //imprime torque com 3 casas decimais 
  Serial.println(" NM  ");
   delay(1000) ; 
  if (Serial.available())                           // se a serial estiver disponivel
  {
  char temp = Serial.read();                        // le caracter da serial 
  if (temp == 't' || temp == 'T')                   // se pressionar t ou T
    {
  balanca.tare();                                   // zera a balança
  Serial.println(" Balança zerada");                // imprime no monitor serial
    }
  }
}
