#include <SPI.h>
#include <SD.h>
#include "HX711.h"

#define SD_CS       4               // chipSelect
// MOSI, MISO, and SCLK are default Arduino pins:
#define SD_MOSI     11
#define SD_MISO     12
#define SD_SCLK     13
#define DOUT        2               // HX711 DATA OUT = Arduino A0 pin
#define CLK         3               // HX711 SCK IN = Arduino A1 pin

HX711 balanca;
File dataFile;

float calibration_factor = -4700;   // calibration factor obtained during calibration (-4700)
float valornilton;                  // comparison variable
float units;                        // reading variable
float massa;                        // reading variable

void setup() {
  Serial.begin(9600);

  // Initialize load cell with the calibrated factor
  balanca.begin(DOUT, CLK);
  balanca.set_scale(calibration_factor);
  balanca.tare();

  // Initialize SD module
  if (!SD.begin(SD_CS)) {
    Serial.println("Failed to initialize SD card");
    while (1);                      // Wait for SD card insertion
  }

  Serial.println("SD card initialized successfully");

  // Open the file
  dataFile = SD.open("data.txt", FILE_WRITE);

  if (!dataFile) {
    Serial.println("Error opening file");
    while (!dataFile);              // Wait if there's an error
  }
  Serial.println("File opened successfully");

  dataFile.close();
  Serial.println("File closed");
}

void loop() {
  // Open the file in append mode
  dataFile = SD.open("data.txt", FILE_WRITE);
  if (dataFile) {
    massa = balanca.get_units();
    valornilton = massa * 9.785 * 0.237;

    Serial.print("Mass: ");
    Serial.print(balanca.get_units(), 3);
    Serial.print(" kg     ");
    Serial.print("Torque: ");
    Serial.print(valornilton, 3);
    Serial.println(" NM");

    // Write load cell data to the file
    dataFile.print(balanca.get_units(), 3);
    dataFile.print(", ");
    dataFile.println(valornilton, 3);

    // Close the file
    dataFile.close();
  } else {
    Serial.println("Error opening file");
  }

  if (Serial.available()) {
    char temp = Serial.read();
    if (temp == 't' || temp == 'T') {
      balanca.tare();
      Serial.println("Scale tared");
    }
  }

  delay(1000);
}
