#if !defined(LED_H)
#define LED_H

// Project: Automatic plant watering
// Technology: Arduino
// Author: Victor Fisac (git@victorfisac)


#include "config.h"

#define PIN_LED             9       // Define pin ID 9 for the LED
#define LIGHT_DURATION      2000.0  // Duration (in ms) when the LED is ON


int ledTimer = 0;
int isLightOn = 0;                  // Note: 1 = HIGH & 0 = LOW
int tempLightOn = 0;


void InitLeds()
{
    pinMode(PIN_LED, OUTPUT);

    digitalWrite(PIN_LED, LOW);
}

void LogLeds()
{
    PrintConsoleValue("Led: ", isLightOn, "");
}

void LedLightPip()
{
    isLightOn = 1;
    tempLightOn = 1;
    digitalWrite(PIN_LED, HIGH);
}

void SetLed(int enabled)
{
    digitalWrite(PIN_LED, enabled == 1 ? HIGH : LOW);

    PrintConsoleValue("Led State: ", enabled, "");
}

void UpdateLeds()
{
    if (!isLightOn)
    {
        return;
    }

    ledTimer += PROGRAM_DELTA_TIME;
    PrintConsoleValue("LedTimer: ", ledTimer, "");

    if (ledTimer % 10 == 0)
    {
        tempLightOn = (tempLightOn == 1) ? 0 : 1;
        SetLed(tempLightOn);
    }

    if (ledTimer > LIGHT_DURATION)
    {
        ledTimer = 0;
        isLightOn = 0;
        tempLightOn = 0;

        SetLed(0);
    }

    LogLeds();
}

#endif