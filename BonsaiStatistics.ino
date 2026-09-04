#include <WiFi.h>
#include <HTTPClient.h>
#include "secrets.h"  // needs: ssid, password, influx_url, influx_token, influx_org, influx_bucket

#define LED_PIN 15  // onboard blue status LED
#define SENSOR_PIN 1 //placeholder

void setup() {
  Serial.begin(115200);
  delay(1000);

  WiFi.begin(ssid, password);
  Serial.print("Connecting to WiFi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nConnected! IP: " + WiFi.localIP().toString());
}

void loop() {
  int rawValue = analogRead(SENSOR_PIN);
  int httpCode;
  
  if (WiFi.status() == WL_CONNECTED) {

    HTTPClient http;

    // Build the full write URL: endpoint + org + bucket + precision
    String url = String(influx_url) + "/api/v2/write?org=" + influx_org +
                 "&bucket=" + influx_bucket + "&precision=s";

    http.begin(url);
    http.addHeader("Authorization", "Token " + String(influx_token));
    http.addHeader("Content-Type", "text/plain; charset=utf-8");

    // Line Protocol format: measurement,tag=value field=value
    String lineProtocol = "soil_moisture,location=patio value=" + String(rawValue);

    httpCode = http.POST(lineProtocol);

    Serial.print("Sent: ");
    Serial.println(lineProtocol);
    Serial.print("Response code: ");
    Serial.println(httpCode);  // 204 = success for InfluxDB writes

    if (httpCode != 204) {
      Serial.println(http.getString());  // print error body if something's wrong
    }

    http.end();
  } else {
    Serial.println("NoCon");
    blink();
  }

  delay(1000);
}