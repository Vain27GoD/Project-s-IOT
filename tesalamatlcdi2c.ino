#include <LiquidCrystal_I2C.h>
#include <Wire.h>

void setup() {
  Serial.begin(115200);
  Serial.println("\nI2C Scanner");
  Wire.begin(); // Inisialisasi bus I2C, pin SDA dan SCL default akan digunakan
}

void loop() {
  int nDevices = 0;
  for(byte address = 1; address < 127; ++address) {
    Wire.beginTransmission(address);
    if (Wire.endTransmission() == 0) {
      Serial.print("Ditemukan perangkat I2C di alamat 0x");
      if (address<16) {
        Serial.print("0");
      }
      Serial.println(address, HEX);
      nDevices++;
    }
  }
  if (nDevices == 0)
    Serial.println("Tidak ada perangkat I2C yang ditemukan.");
  else
    Serial.println("Selesai.");
  
  delay(5000); // Ulangi pemindaian setiap 5 detik
}