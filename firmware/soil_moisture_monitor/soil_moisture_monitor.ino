#include <WiFi.h>
#include <HTTPClient.h>
#include "secrets.h"  // needs: ssid, password, influx_url, influx_token, influx_org, influx_bucket

#define LED_PIN 15  // onboard blue status LED
#define SENSOR_POWER 21 //hold high to power sensor
#define SENSOR_PIN 17

#define CAL_SENSOR_MAX 7878 //highest value while in open air
#define CAL_SNESOR_MIN 2448 //lowest value while in glass of water

int Adjusted_Data_Value = 0;

void setup() {
  LED_init();
  sensor_init();
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
  pollSensor();
  sendHTTP();
  delay(1000);
}

void LED_init() {
  pinMode(LED_PIN, OUTPUT);
}

void sensor_init() {
  pinMode(SENSOR_POWER, OUTPUT);
  digitalWrite(SENSOR_POWER, HIGH);
}

//blink the sole LED on board
void blink() {
  digitalWrite(LED_PIN, HIGH);
  delay(500);
  digitalWrite(LED_PIN, LOW);
}

void pollSensor() {
  int raw_data = analogRead(SENSOR_PIN);
  Adjusted_Data_Value = ( raw_data - CAL_SENSOR_MIN ) / (CAL_SENSOR_MAX - CAL_SENSOR_MIN) 
  return;
}

void sendHTTP() {
  int httpCode;
  HTTPClient http;
  
  if (WiFi.status() == WL_CONNECTED) {


    // Build the full write URL: endpoint + org + bucket + precision
    String url = String(influx_url) + "/api/v2/write?org=" + influx_org +
                 "&bucket=" + influx_bucket + "&precision=s";

    http.begin(url);
    http.addHeader("Authorization", "Token " + String(influx_token));
    http.addHeader("Content-Type", "text/plain; charset=utf-8");

    // Line Protocol format: measurement,tag=value field=value
    String lineProtocol = "soil_moisture,location=patio value=" + String(Adjusted_Data_Value);

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
}