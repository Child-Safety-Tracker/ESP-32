#include <HardwareSerial.h>
#include <WiFi.h>
#include <HTTPClient.h>

HardwareSerial SerialPort(2);

const char* ssid = "Giangvien";
const char* password = "dhbk@2024";

String serverName = "http://35.209.25.56:80/";
String locationPath = serverName + "location";

String receivedLocation = "";
String longitude = "";
String latitude = "";
int accuracy = 0;

unsigned long lastTime = 0;
unsigned long timerDelay = 5000;

void setup() {
  WiFi.begin(ssid, password);
  Serial.begin(115200);
  SerialPort.begin(115200, SERIAL_8N1, 16, 17);
}

void loop() {
  
  if (SerialPort.available() > 0){
    receivedLocation = SerialPort.readString();
    //SerialPort.println(receivedLocation);
  }
    
  if ((millis() - lastTime) > timerDelay) {
    if (WiFi.status() == WL_CONNECTED) {
      WiFiClient client;
      HTTPClient http;

      http.begin(client, locationPath);

      http.addHeader("Content-Type", "application/json");
      int httpResponseCode = http.POST(receivedLocation);

      http.end();
    } else {
    }
  }
  lastTime = millis();
}
