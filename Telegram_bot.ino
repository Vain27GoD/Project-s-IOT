#include "CTBot.h";

CTBot mybot;
String ssid = "koki";
String pass = "33Ioo847";

String token = "8207771132:AAHRKeqBtccoCNOFX_raRiPlYj2CKJK9snQ";
const int id = 7902708562;
int led = 2;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(led, OUTPUT);
  Serial.println("Memulai telegram bot");
  mybot.wifiConnect(ssid, pass);

  mybot.setTelegramToken(token);

  if(mybot.testConnection())
    Serial.println("koneksi berhasil");
  else
    Serial.println("Koneksi Gagal ");
}

void loop() {
  // put your main code here, to run repeatedly:
  TBMessage msg;
  if(mybot.getNewMessage(msg)){
    Serial.println("Pesan masuk : "+msg.text);
    String pesan = msg.text;
    if(pesan=="on"){
      digitalWrite(led, LOW); //led nodemcu menyala
      mybot.sendMessage(id, "Led Menyala");
      }
    else if (pesan=="off"){
      digitalWrite(led, HIGH); //led nodemcu mati
      mybot.sendMessage(id, "Led Mati");
    }
  }
}
