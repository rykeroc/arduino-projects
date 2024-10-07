
#include <WiFi.h>
#include <WebServer.h>
#include <ArduinoJson.h>
#include "DHT.h"

#define SENSOR_TH 1
#define SENSOR_NAME "<sensor name here>"

#define DHT_PIN 13
#define DHTTYPE DHT11 // DHT 11

#define APPLICATION_JSON "application/json"

DHT dht(DHT_PIN, DHTTYPE);

const char* ssid = "<network name here>";
const char* password = "<network password here";

WebServer server(80);

String jsonResponse;

int statusCode;
float humidity;
float temp;

void handleRoot() {
  JsonDocument json;
  json["status"] = "online";
  json["name"] = SENSOR_NAME;
  json["type"] = SENSOR_TH;
  serializeJson(json, jsonResponse);
  server.send(200, APPLICATION_JSON, jsonResponse);
}

void handleTemperatureAndHumidity() {
  JsonDocument json;
  // Reading humidity
  humidity = dht.readHumidity();
  // Read temperature as Celsius
  temp = dht.readTemperature();

  if (isnan(humidity) || isnan(temp)) {
    // Send back error response
    json["detail"] = "Failed to read from DHT sensor";
    statusCode = 500;
  } else {
    Serial.printf("Temperature: %.2f *C\tHumidity: %.2f\n", temp, humidity);
    json["humidity"] = humidity;
    json["temperature"] = temp;
    statusCode = 200;
  }
  serializeJson(json, jsonResponse);
  server.send(statusCode, APPLICATION_JSON, jsonResponse);
}

void setup() {
  Serial.begin(115200);

  dht.begin();

  WiFi.begin(ssid, password);
  Serial.printf("Connecting to %s", ssid);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print(".");
  }
  Serial.printf("\nIP Address: %s\n", WiFi.localIP().toString());

  // Endpoints
  server.on("/", handleRoot);
  server.on("/info", handleTemperatureAndHumidity);

  server.begin();
  Serial.println("Started HTTP server");
}

void loop() {
  server.handleClient();   // Listen for incoming clients
}
