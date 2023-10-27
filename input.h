#if !defined(INPUT_H)
#define INPUT_H

// Project: Automatic plant watering
// Technology: Arduino
// Author: Victor Fisac (git@victorfisac)


#include "config.h"

#define PIN_BUTTON_01   12        // Left button
#define PIN_BUTTON_02   13        // Right button

#define BUTTON_LEFT     0
#define BUTTON_RIGHT    1
#define MIN_TIME_HOLD   1000


const int MAX_BUTTONS = 2;

int btnStates[MAX_BUTTONS] = { 0, 0 };
int btnPrevStates[MAX_BUTTONS] = { 0, 0 };
int holdTimers[MAX_BUTTONS] = { 0, 0 };


void InitInput()
{
    for (int i = 0; i < MAX_BUTTONS; i++)
    {
        btnStates[i] = 0;
        btnPrevStates[i] = 0;
        holdTimers[i] = 0;

        pinMode(PIN_BUTTON_01 + i, INPUT_PULLUP);
    }
}

void CheckInput()
{
    for (int i = 0; i < MAX_BUTTONS; i++)
    {
        btnPrevStates[i] = btnStates[i];
    }

    for (int i = 0; i < MAX_BUTTONS; i++)
    {
        int value = digitalRead(PIN_BUTTON_01 + i);
        btnStates[i] = value;

        if (value == 1)
        {
            if (holdTimers[i] <= MIN_TIME_HOLD)
            {
                holdTimers[i] += PROGRAM_DELTA_TIME;
            } 
        }
        else
        {
            holdTimers[i] = 0;
        }
    }
}

int IsButtonDown(int button)
{
    return (btnStates[button] != btnPrevStates[button] && btnStates[button] == 1) ? 1 : 0;
}

int IsButtonUp(int button)
{
    return (btnStates[button] != btnPrevStates[button] && btnPrevStates[button] == 1) ? 1 : 0;
}

int IsButtonHold(int button)
{
    return (holdTimers[button] >= MIN_TIME_HOLD) ? 1 : 0;
}

#endif