#if !defined(PUMP_H)
#define PUMP_H

// Project: Automatic plant watering
// Technology: Arduino
// Author: Victor Fisac (git@victorfisac)


#include "config.h"

#define PIN_PUMP                7           // Define pin ID 7 for the pump

#define PUMP_STATE_IDLE         0           // State that defines when the pump is not working
#define PUMP_STATE_WORKING      1           // State that defines when the pump is working

#define PIN_WATER_LEVEL         2           // Define pin ID 2 for the water level


int pumpState = PUMP_STATE_IDLE;          // Note: PUMP_STATE_IDLE = HIGH & PUMP_STATE_WORKING = LOW
int waterLevel = 0;                       // 0 = no enough water & 1 = enough water
int pumpTimer = 0;


void InitPump()
{
    pinMode(PIN_PUMP, OUTPUT);
    pinMode(PIN_WATER_LEVEL, INPUT);

    digitalWrite(PIN_PUMP, HIGH);
}

void SetPump(int enabled)
{
    if (enabled == pumpState)
    {
        return;
    }

    if (enabled == 1 && waterLevel == 0 && WATER_LEVEL_SECURITY == 1)
    {
        PrintConsole("Tried to enable the pump but there is no water in the tank");
        return;
    }

    pumpState = enabled;
    SetLed(pumpState);

    if (enabled == 1)
    {
        PrintConsole("Turning pump on");

        digitalWrite(PIN_PUMP, LOW);
    }
    else
    {
        PrintConsole("Turning pump off");

        digitalWrite(PIN_PUMP, HIGH);
    }
}

void UpdatePump()
{
    waterLevel = digitalRead(PIN_WATER_LEVEL);

    if (pumpState == PUMP_STATE_WORKING && waterLevel == 0 && WATER_LEVEL_SECURITY == 1)
    {
        // SetPump(0);
    }
}

#endif