// Project: Automatic plant watering
// Technology: Arduino
// Author: Victor Fisac (git@victorfisac)

#include "core.h"


void setup()
{
    Serial.begin(PROGRAM_SERIAL_PORT);
    
    Init();
}

void loop()
{
    Update();
    Render();

    delay(PROGRAM_LOOP_DELAY);
}