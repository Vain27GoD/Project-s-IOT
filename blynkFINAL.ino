#define BLYNK_PRINT Serial
#define BLYNK_TEMPLATE_ID "TMPL6cM9bonn2"
#define BLYNK_TEMPLATE_NAME "LED ESP32 1"
#define BLYNK_AUTH_TOKEN "eSi_Iod4VZ-RsROaW52RLyhNwmdN-or4"

#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <WiFiClient.h>

// Ganti dengan Auth Token Blynk Anda
// Ganti dengan nama WiFi dan password
char ssid[] = "koki";
char pass[] = "33Ioo847";
char auth[] = BLYNK_AUTH_TOKEN;

// Pin LED
#define LED_PIN D1

void setup() {
  Serial.begin(115200);
  Blynk.begin(auth, ssid, pass); //// You can also specify server:
  //Blynk.begin(auth, ssid, pass, "blynk.cloud", 80);
  //Blynk.begin(auth, ssid, pass, IPAddress(192,168,1,100), 8080);
  pinMode(LED_PIN, OUTPUT);
}

BLYNK_WRITE(V0) {
  int value = param.asInt();
  if (value == 1) {
    digitalWrite(LED_PIN, HIGH); // LED menyala
  } else {
    digitalWrite(LED_PIN, LOW); // LED mati
  }
}

void loop() {
  Blynk.run();
}