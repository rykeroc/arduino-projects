#include "DHT.h"

#define DHT_PIN 13
#define DHTTYPE DHT11 // DHT 11

DHT dht(DHT_PIN, DHTTYPE);

float h = 0;
float t = 0;

void setup() {
  Serial.begin(115200);

  dht.begin();

  Serial.println("Beginning DHT measurements shortly...");
}

void loop() {
  // Wait between readings
  delay(2000);

  // Reading humidity
  h = dht.readHumidity();
  // Read temperature as Celsius
  t = dht.readTemperature();

  // Check if any reads failed and exit early (to try again).
  if (isnan(h) || isnan(t)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }

  Serial.printf("Temperature: %.2f *C\tHumidity: %.2f%\n", t, h);
}
