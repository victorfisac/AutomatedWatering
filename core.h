#if !defined(CORE_H)
#define CORE_H

// Project: Automatic plant watering
// Technology: Arduino
// Author: Victor Fisac (git@victorfisac)


#include "lcd.h"
#include "input.h"
#include "led.h"
#include "pump.h"
#include "sensor_floor.h"
#include "sensor_air.h"
#include "screens.h"
#include "config.h"
#include "logic.h"


void Init()
{
    InitLeds();
    LedLightPip();

    InitInput();
    InitScreen();
    InitLogic();
    InitMenu();
    
    InitPump();
    InitSensorAir();
    InitSensorFloor();

    PrintConsole("--------------------------------------------------------------");
    PrintConsole("--------------------------------------------------------------");
    PrintConsole("Watering System connected to debugger");
}

void Update()
{
    UpdateSensorFloor();
    UpdateSensorAir();
    
    CheckHumidity();
    CheckPumpBehaviour();
    CheckInput();

    UpdatePump();
    UpdateLeds();
    UpdateMenu();
}

void Render()
{
    RenderCurrentMenu();

    if (resetData == 1)
    {
        Init();
    }
}

#endif