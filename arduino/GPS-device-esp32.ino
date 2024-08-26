#include <HardwareSerial.h>
#include <WiFi.h>
#include <HTTPClient.h>

HardwareSerial SerialPort(2);

const char* ssid = "ai cho";
const char* password = "123456788";

char* serverName = "http://35.209.25.56:80/location";

String receivedLocation = "";
String modifiedReceivedLocation = "";


unsigned long lastTime = 0;
unsigned long timerDelay = 3000;

void setup() {
  Serial.begin(115200);
  SerialPort.begin(115200, SERIAL_8N1, 16, 17);

  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
    Serial.println(WiFi.localIP());
  }
}

void loop() {

  if (SerialPort.available() > 0) {
    receivedLocation = SerialPort.readString();
    for (int i = 0; i < receivedLocation.length(); i++) {
      if (receivedLocation[i] == '\0')
        break;
      modifiedReceivedLocation += receivedLocation[i];
    }

    if (WiFi.status() == WL_CONNECTED) {
      Serial.println(modifiedReceivedLocation);
      WiFiClient client;
      HTTPClient http;

      http.begin(client, serverName);

      http.addHeader("Content-Type", "application/json");
      int httpResponseCode = http.POST(modifiedReceivedLocation);
      Serial.println(httpResponseCode);
      http.end();
    } else {
    }
    // lastTime = millis();
  }
  if (receivedLocation.length() != 0)
    modifiedReceivedLocation = "";
}
