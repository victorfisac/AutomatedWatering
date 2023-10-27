#if !defined(SENSOR_AIR_H)
#define SENSOR_AIR_H

// Project: Automatic plant watering
// Technology: Arduino
// Author: Victor Fisac (git@victorfisac)


#include <DHT.h>

#define PIN_DHT          8          // Define pin ID 8 for the external temperature and humidity sensors
#define DHTTYPE         DHT11       // Define version used in DHT sensor


DHT dht(PIN_DHT, DHTTYPE);          // Reference to sensor
float airHumidity = 0.0f;           // In percentage (%)
float airTemperature = 0.0f;        // In Celsius (ºC)


void InitSensorAir()
{
    dht.begin();
}

void UpdateSensorAir()
{
    airHumidity = dht.readHumidity();
    airTemperature = dht.readTemperature();
}

#endif