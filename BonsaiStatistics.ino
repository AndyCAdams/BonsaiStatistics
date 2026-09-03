#include <WiFi.h>
#include "secrets.h"

void setup() {
  Serial.begin(115200);
  delay(1000);

  Serial.println("Starting WiFi connection test...");
  Serial.print("Connecting to: ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);
  
  unsigned long startAttempt = millis();
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print("WiFi status code: ");
    Serial.println(WiFi.status());

    // fail out after 15 seconds instead of hanging forever
    if (millis() - startAttempt > 15000) {
      Serial.println("\nFailed to connect. Check credentials or signal.");
      return;
    }
  }

  Serial.println("\nConnected!");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
  Serial.print("Signal strength (RSSI): ");
  Serial.print(WiFi.RSSI());
  Serial.println(" dBm");
}

void loop() {
  //NULL
}