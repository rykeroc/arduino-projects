#include "DHT.h"

#define DHT_PIN 8
#define DHTTYPE DHT11 // DHT 11

DHT dht(DHT_PIN, DHTTYPE);

void setup() {
  Serial.begin(115200);

  dht.begin();

  Serial.println("Beginning DHT measurements shortly...");
}

void loop() {
  // Wait between readings
  delay(2000);

    // Reading temperature or humidity takes about 250 milliseconds!
  // Sensor readings may also be up to 2 seconds 'old' (its a very slow sensor)
  float h = dht.readHumidity();
  // Read temperature as Celsius
  float t = dht.readTemperature();

  // Check if any reads failed and exit early (to try again).
  if (isnan(h) || isnan(t)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }

  Serial.printf("Temperature: %.2f *C\tHumidity: %f%\n", t, h);
}
