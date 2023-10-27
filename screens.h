#if !defined(SCREENS_H)
#define SCREENS_H

// Project: Automatic plant watering
// Technology: Arduino
// Author: Victor Fisac (git@victorfisac)


#include "logic.h"

#define   MENU_INDEX_SETTINGS     menuIndexMap[0] - 1
#define   MENU_INDEX_RESET        menuIndexMap[1] - 1


const int MAX_MENU_LEVELS = 3;

int menuIndexMap[MAX_MENU_LEVELS] = { 4, 6, 0 };
int currentMenu = 0;
int currentSubMenu = 0;
int menuTimer = 0;
int isBlinking = 0;
int canCheckHold = 1;
int resetData = 0;


void InitMenu()
{
    currentMenu = 0;
    currentSubMenu = 0;
    menuTimer = 0;
    isBlinking = 0;
    canCheckHold = 1;
    resetData = 0;

    PrintText("Watering System", "by Victor Fisac");

    delay(PROGRAM_INTRO_DELAY);
}

void ResetSettings()
{
    resetData = 1;
}

void EnterNextMenu()
{
    if (currentMenu == 0)
    {
        if (currentSubMenu == MENU_INDEX_SETTINGS)
        {
            currentMenu = 1;
            currentSubMenu = 0;
        }
    }
    else if (currentMenu == 1)
    {
        currentMenu = 2;
    }
}

void EnterPrevMenu()
{
    if (currentMenu == 1)
    {
        currentMenu = 0;
        currentSubMenu = 0;
    }
    else if (currentMenu == 2)
    {
        currentMenu = 1;
    }
}

void NavigateCurrentSubMenu()
{
    currentSubMenu++;

    if (currentSubMenu >= menuIndexMap[currentMenu])
    {
        currentSubMenu = 0;
    }
}

void UpdateNavigation()
{
    int rightButton = IsButtonUp(BUTTON_RIGHT);

    if (rightButton == 1)
    {
        if (canCheckHold == 0)
        {
            canCheckHold = 1;
            return;
        }

        EnterNextMenu();
        return;
    }

    int leftButton = IsButtonUp(BUTTON_LEFT);

    if (leftButton == 1 && canCheckHold == 1)
    {
        NavigateCurrentSubMenu();
    }
}

void UpdateEditSetting()
{
    int leftButton = IsButtonUp(BUTTON_LEFT);
    int rightButton = IsButtonUp(BUTTON_RIGHT);

    if (leftButton == rightButton && currentSubMenu != MENU_INDEX_RESET)
    {
        return;
    }

    switch (currentSubMenu)
    {
        case 0:
        {
            userMinHumidityThreshold += rightButton;
            userMinHumidityThreshold -= leftButton;

            if (userMinHumidityThreshold < MAP_HUMIDITY_MIN_Y)
            {
                userMinHumidityThreshold = MAP_HUMIDITY_MIN_Y;
            }
            
            if (userMinHumidityThreshold >= userMaxHumidityThreshold)
            {
                userMinHumidityThreshold = userMaxHumidityThreshold - 1;
            }

            if (userMinHumidityThreshold > MAP_HUMIDITY_MAX_Y)
            {
                userMinHumidityThreshold = MAP_HUMIDITY_MAX_Y;
            }
        } break;
        case 1:
        {
            userMaxHumidityThreshold += rightButton;
            userMaxHumidityThreshold -= leftButton;

            if (userMaxHumidityThreshold < MAP_HUMIDITY_MIN_Y)
            {
                userMaxHumidityThreshold = MAP_HUMIDITY_MIN_Y;
            }
            
            if (userMaxHumidityThreshold <= userMinHumidityThreshold)
            {
                userMaxHumidityThreshold = userMinHumidityThreshold + 1;
            }

            if (userMaxHumidityThreshold > MAP_HUMIDITY_MAX_Y)
            {
                userMaxHumidityThreshold = MAP_HUMIDITY_MAX_Y;
            }
        } break;
        case 2:
        {
            userTemperatureThreshold += rightButton;
            userTemperatureThreshold -= leftButton;

            if (userTemperatureThreshold < 0)
            {
                userTemperatureThreshold = 0;
            }
            
            if (userTemperatureThreshold > 50)
            {
                userTemperatureThreshold = 50;
            }
        } break;
        case 3:
        {
            userRainCheck = (userRainCheck == 1) ? 0 : 1;
        } break;
        case 4:
        {
            userMinHumidityForRain += rightButton;
            userMinHumidityForRain -= leftButton;

            if (userMinHumidityForRain <= userMaxHumidityThreshold)
            {
                userMinHumidityForRain = userMaxHumidityThreshold + 1;
            }

            if (userMinHumidityForRain > MAP_HUMIDITY_MAX_Y)
            {
                userMinHumidityForRain = MAP_HUMIDITY_MAX_Y;
            }
        } break;
        case 5:
        {
            if (leftButton == 1 && rightButton == 1)
            {
                ResetSettings();
            }
        } break;
    }
}

void UpdateMenu()
{
    if (currentMenu > 0 && canCheckHold == 1)
    {
        if (IsButtonHold(BUTTON_RIGHT) == 1)
        {
            canCheckHold = 0;
          
            EnterPrevMenu();  
            return;
        }
    }

    if (currentMenu < 2)
    {
        UpdateNavigation();
    }
    else
    {
        UpdateEditSetting();
    }
}

void RenderMainNavigation()
{
    switch (currentSubMenu)
    {
        case 0:
        {
            PrintTitleValue("Temp: ", airTemperature, "C");
            PrintSubtitleValue("A. Humid: ", (int)airHumidity, "%");
        } break;
        case 1:
        {
            PrintTitleValue("F. Humid: ", (int)floorHumidity, "%");
            PrintSubtitleValue("Water Level: ", -1, waterLevel == 0 ? "NO!" : "OK");
        } break;
        case 2:
        {
            PrintTitleValue("Watering: ", timesWatered, " tms");
            PrintSubtitleValue("Raining: ", timesRaining, " tms");
        } break;
        case 3:
        {
            PrintText("Settings Menu", "");
        } break;
    }
}

void RenderSettingsMenu()
{
    switch (currentSubMenu)
    {
        case 0:
        {
            PrintTitleValue("START F. Humid:", -1, "");
            PrintSubtitleValue(" ", userMinHumidityThreshold, "%");
        } break;
        case 1:
        {
            PrintTitleValue("STOP F. Humid:", -1, "");
            PrintSubtitleValue(" ", userMaxHumidityThreshold, "%");
        } break;
        case 2:
        {
            PrintTitleValue("START if Temp:", -1, "");
            PrintSubtitleValue(" ", userTemperatureThreshold, " C");
        } break;
        case 3:
        {
            PrintTitleValue("Check if rained:", -1, "");
            PrintSubtitleValue(" ", -1, (userRainCheck == 1) ? " YES" : " NO");
        } break;
        case 4:
        {
            PrintTitleValue("Rain Humid:", -1, "");
            PrintSubtitleValue(" ", userMinHumidityForRain, "%");
        } break;
        case 5:
        {
            PrintText("FACTORY RESET", "");
        } break;
        default: break;
    }
}

void RenderSettingsPropertiesEdit()
{
    switch (currentSubMenu)
    {
        case 0:
        {
            PrintTitleValue("START F. Humid:", -1, "");
            PrintSubtitleValue(" <-  ", userMinHumidityThreshold, "% ->");
        } break;
        case 1:
        {
            PrintTitleValue("STOP F. Humid:", -1, "");
            PrintSubtitleValue(" <- ", userMaxHumidityThreshold, "% ->");
        } break;
        case 2:
        {
            PrintTitleValue("START if Temp:", -1, "");
            PrintSubtitleValue(" <- ", userTemperatureThreshold, "C ->");
        } break;
        case 3:
        {
            PrintTitleValue("Check if rained:", -1, "");
            PrintSubtitleValue(" <- ", -1, (userRainCheck == 1) ? " YES ->" : " NO ->");
        } break;
        case 4:
        {
            PrintTitleValue("Rain Humid:", -1, "");
            PrintSubtitleValue(" <- ", userMinHumidityForRain, "% ->");
        } break;
        case 5:
        {
            PrintText("FACTORY RESET", " -press 2 btns-");
        } break;
        default: break;
    }
}

void RenderSettingProperties()
{
    menuTimer += PROGRAM_DELTA_TIME;

    if (menuTimer > 3000)
    {
        menuTimer = 0;
    }

    if ((menuTimer % 1000) == 0)
    {
        isBlinking = (isBlinking == 1) ? 0 : 1;
    }

    if (isBlinking == 1)
    {
        RenderSettingsPropertiesEdit();
    }
    else if (isBlinking == 0)
    {
        ClearScreen();
        PrintText("", "");

        isBlinking = -1;
    }
}

void RenderCurrentMenu()
{
    ClearScreen();

    switch (currentMenu)
    {
        case 0:
        {
            RenderMainNavigation();
        } break;
        case 1:
        {
            RenderSettingsMenu();
        } break;
        case 2:
        {
            RenderSettingProperties();
        } break;
        default: break;
    }
}

#endif