#if !defined(SENSOR_FLOOR_H)
#define SENSOR_FLOOR_H

// Project: Automatic plant watering
// Technology: Arduino
// Author: Victor Fisac (git@victorfisac)


#define PIN_VCC_HUMIDITY       4           // Define pin ID 4 for the internal humidity sensor
#define PIN_SENSOR_TYPE        A0
#define MAP_HUMIDITY_MIN_X     0
#define MAP_HUMIDITY_MAX_X     1023
#define MAP_HUMIDITY_MIN_Y     0
#define MAP_HUMIDITY_MAX_Y     120


float floorHumidity = 0.0f;                 // In percentage (0% - 120%)


void InitSensorFloor()
{
    pinMode(PIN_VCC_HUMIDITY, OUTPUT);
    digitalWrite(PIN_VCC_HUMIDITY, LOW);
}

void UpdateSensorFloor()
{
    digitalWrite(PIN_VCC_HUMIDITY, HIGH);
    int rawValue = analogRead(PIN_SENSOR_TYPE);
    digitalWrite(PIN_VCC_HUMIDITY, LOW);

    floorHumidity = map(rawValue, MAP_HUMIDITY_MIN_X, MAP_HUMIDITY_MAX_X, MAP_HUMIDITY_MAX_Y, MAP_HUMIDITY_MIN_Y);
}

#endif