#include <Wire.h>
#include <SPI.h>
#include <SD.h>

#define SD_CS 5

void setup() {
  Serial.begin(115200);
  delay(1000);
  Serial.println("\n--- I2C Scanner ---");

  Wire.begin(21, 22); // SDA, SCL

  byte count = 0;
  for (byte addr = 1; addr < 127; addr++) {
    Wire.beginTransmission(addr);
    byte error = Wire.endTransmission();
    if (error == 0) {
      Serial.print("Found device at 0x");
      if (addr < 16) Serial.print("0");
      Serial.println(addr, HEX);
      count++;
    }
  }
  Serial.print(count);
  Serial.println(" device(s) found.\n");

  Serial.println("--- SD Card Test ---");
  if (!SD.begin(SD_CS)) {
    Serial.println("SD card init FAILED - check wiring/card");
  } else {
    Serial.println("SD card init OK");
    File testFile = SD.open("/test.txt", FILE_WRITE);
    if (testFile) {
      testFile.println("Weather station test write");
      testFile.close();
      Serial.println("Test file written successfully");
    } else {
      Serial.println("Failed to open test file for writing");
    }
  }
}

void loop() {
}