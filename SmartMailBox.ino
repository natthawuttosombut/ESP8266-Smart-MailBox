#include <ESP8266WiFi.h>
#include <TridentTD_LineNotify.h>
#include <FirebaseESP8266.h>
#include <DHT.h>
#include <time.h>

// ค่า secret (WiFi / LINE / Firebase) อยู่ในไฟล์ secrets.h (ไม่ขึ้น GitHub)
// ถ้ายังไม่มี ให้คัดลอก secrets.example.h เป็น secrets.h แล้วแก้ค่า
#include "secrets.h"

String state = "LOCK";
const int relayPin = D0;

FirebaseData fbdo;

String WiFiStatusTrue = "Connected";
String WiFiStatusFalse = "Not Connected";

void setup() {

  Serial.begin(9600);
  pinMode(LED_BUILTIN, OUTPUT);

  pinMode(relayPin, OUTPUT);

  digitalWrite(relayPin, HIGH);

  //WifiZone
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);

  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
  Firebase.reconnectWiFi(true);
  LINE.setToken(LINE_TOKEN);

  //!=
  while (WiFi.status() != WL_CONNECTED) {
    Serial.println("ไม่สามารถเชื่อมต่อWifiได้ครับ/ค่ะ");

    delay(500);
    Firebase.setString(fbdo, "/Mail/StatusWifi", "Not Connected");
    LINE.notify("สถานะการเชื่อมต่อ" + String(WiFiStatusFalse));
  }
  //=WL_CONNETED

  Serial.println(" เชื่อมต่อWifiสำเร็จครับ/ค่ะ");
  Serial.println("IP ADDRESS : " + WiFi.localIP().toString());  //show IP

  //setStringWifiStatusS
  Serial.println("พร้อมใช้งานเเล้วครับ/ค่ะ");
  LINE.notify("สถานะการเชื่อมต่อ : " + String(WiFiStatusTrue));
  Firebase.setString(fbdo, "/Mail/StatusWifi", String(WiFiStatusTrue));
}

void loop() {

  if (Firebase.getString(fbdo, "/Mail/StatusLock/status")) {

    state = fbdo.stringData();
    if (state == "UNLOCK") {
      digitalWrite(relayPin, LOW);
      Serial.println(state);

    } else if (state == "LOCK") {
      digitalWrite(relayPin, HIGH);
      Serial.println(state);
    }
  }
}
