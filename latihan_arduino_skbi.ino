#include <BlynkSimpleEsp32.h>
#include <WiFiClient.h>
#include <WiFi.h>

#define BLYNK_TEMPLATE_ID "TMPL60XHKS9bH"
#define BLYNK_TEMPLATE_NAME "PELAJARAN SKBI LDR LED"
#define BLYNK_AUTH_TOKEN "t7N10Z3KjBFZF6UCDd_1v6fh-WEsjDGo"

// --- HEADER ---
#define LDR_PIN 34       // Pin analog untuk LDR (ESP32 gunakan GPI034, ESP8266, gunakan A0)
#define LED_PIN 5        // Pin Relay

#define VIRTUAL_LDR V0
#define VIRTUAL_LED V1

char ssid[] = "MI 8";
char pass[] = "vian2727";
char auth[] = BLYNK_AUTH_TOKEN;

// --- DEKLARASI VARIABEL GLOBAL ---
int ldrValue = 0;        // Variabel untuk menyimpan nilai LDR
int threshold = 1500;    // Batas ambang cahaya (sesuaikan dengan kondisi ruangan)
//bool ledState = false;

// --- FUNGSI SETUP ---
void setup() {
  Serial.begin(115200);
  Blynk.begin(auth, ssid, pass);
  pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN, LOW); // Matikan relay saat awal
}

// --- FUNGSI LOOPING ---
void loop() {
  Blynk.run();
  ldrValue = analogRead(LDR_PIN);
  Blynk.virtualWrite(VIRTUAL_LDR, ldrValue);
  Serial.print("Nilai LDR: ");
  Serial.println(ldrValue);

  // Logika kontrol lampu
  if (ldrValue < threshold) { // Kondisi terang
    digitalWrite(LED_PIN, LOW); // Matikan relay
    Blynk.virtualWrite(VIRTUAL_LED, 0);
    Serial.println("Lampu: OFF (kondisi terang)");
  } else { // Kondisi gelap
    digitalWrite(LED_PIN, HIGH); // Matikan relay
    Blynk.virtualWrite(VIRTUAL_LED, 1);
    Serial.println("Lampu: ON (kondisi gelap)");
  }
 
  delay(1000); // Baca tiap 1 detik
}
