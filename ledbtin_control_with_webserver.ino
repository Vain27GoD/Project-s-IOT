#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>

// Ganti dengan SSID dan password WiFi Anda
const char* ssid = "koki";
const char* password = "33Ioo847";

// Port untuk server web
const int webServerPort = 80;

// Pin LED (GPIO2 untuk LED built-in)
const int ledPin = 2;

// Variabel untuk menyimpan status LED
bool ledState = false;

// Membuat objek server web
ESP8266WebServer server(webServerPort);

void setup() {
  Serial.begin(115200);
  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, LOW); // Pastikan LED mati saat start

  // Koneksi ke WiFi
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

  // Menangani request ke root path ("/")
  server.on("/", handleRoot);

  // Menangani request ke "/led/on"
  server.on("/led/off", handleLedOn);

  // Menangani request ke "/led/off"
  server.on("/led/on", handleLedOff);

  // Mulai server
  server.begin();
  Serial.println("HTTP server started");
}

void loop() {
  server.handleClient();
}

// Handler untuk root path ("/")
void handleRoot() {
  String html = "<html><head><title>ESP8266 LED Control</title></head><body>";
  html += "<h1>ESP8266 LED Control</h1>";
  html += "<p>LED is currently: " + String(ledState ? "ON" : "OFF") + "</p>";
  html += "<a href=\"/led/off\"><button>Turn LED ON</button></a>";
  html += "<a href=\"/led/on\"><button>Turn LED OFF</button></a>";
  html += "</body></html>";
  server.send(200, "text/html", html);
}

// Handler untuk "/led/on"
void handleLedOn() {
  ledState = true;
  digitalWrite(ledPin, LOW); // LED dihidupkan (HIGH untuk logika terbalik pada ESP8266)
  server.sendHeader("Location", String("/"));
  server.send(302, "text/plain", "");
}

// Handler untuk "/led/off"
void handleLedOff() {
  ledState = false;
  digitalWrite(ledPin, HIGH); // LED dimatikan
  server.sendHeader("Location", String("/"));
  server.send(302, "text/plain", "");
}