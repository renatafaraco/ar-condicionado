#include "DHT.h"

#define DHTPIN 2  // pino D4 do NodeMCU
#define DHTTYPE DHT11  

DHT dht(DHTPIN, DHTTYPE);

void sensorSetup() {
  dht.begin();
}


float getTemperatura() {
  float t = dht.readTemperature();
  if (isnan(t)) {
    return -1;
  }
  return t;
}

float getUmidade() {
  float h = dht.readHumidity();
  if (isnan(h)) {
    return -1;
  }
  return h;
}

