#define BLYNK_PRINT Serial
#define BLYNK_TEMPLATE_ID "TMPL6iw_GLgP5"
#define BLYNK_TEMPLATE_NAME "SUHU RUANGAN"
#define BLYNK_AUTH_TOKEN "ObgpYr-EOVJlmSEtNMheXcyz-aa_TxyV"

#include <WiFi.h>
#include <BlynkSimpleEsp32.h>
#include <DHT.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

char auth[] = BLYNK_AUTH_TOKEN;
char ssid[] = "Wokwi-GUEST";
char pass[] = "";

#define LED_PIN 14
#define DHTPIN 13
#define DHTTYPE DHT22
DHT dht(DHTPIN, DHTTYPE);

LiquidCrystal_I2C lcd(0x27, 16, 2);

BlynkTimer timer;

#define VIRTUAL_PIN_TEMP V0
#define VIRTUAL_PIN_HUM V1

void sendSensorData() {

  float h = dht.readHumidity();
  float t = dht.readTemperature();

  if (t >= 32) { // Jika suhu di atas 30 derajat Celsius
    Blynk.virtualWrite(V2, 1); // Update status tombol virtual di Blynk menjadi ON
    digitalWrite(LED_PIN, HIGH); // Nyalakan lampu (HIGH/LOW tergantung modul relay aktif-HIGH/LOW)
  } else {
    Blynk.virtualWrite(V2, 0); // Update status tombol virtual di Blynk menjadi OFF
    digitalWrite(LED_PIN, LOW); // Matikan lampu
  }

  if (isnan(h) || isnan(t)) {
    Serial.println("Gagal membaca data sensor DHT!");

    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("DHT Error!");
    return;
  }


  Blynk.virtualWrite(VIRTUAL_PIN_HUM, h);
  Blynk.virtualWrite(VIRTUAL_PIN_TEMP, t);

  lcd.clear();

  lcd.setCursor(0, 0);
  lcd.print("suhu: ");
  lcd.print(t);
  lcd.print("C");

  lcd.setCursor(0, 1);
  lcd.print("humid: ");
  lcd.print(h);
  lcd.print("%");
}

void setup() {

  pinMode(LED_PIN, OUTPUT);

  Wire.begin();
  lcd.init();
  lcd.backlight();
  lcd.setCursor(4, 0);
  lcd.print("Kelompok 1");
  lcd.setCursor(5, 1);
  lcd.print("MEMULAI");

  Blynk.begin(auth, ssid, pass);

  dht.begin();

  timer.setInterval(3000L, sendSensorData);

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Blynk Terhubung!");
  lcd.setCursor(0, 1);
  lcd.print("Data Siap...");
}

void loop() {
  Blynk.run();
  timer.run();
}