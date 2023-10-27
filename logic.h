#if !defined(LOGIC_H)
#define LOGIC_H

// Project: Automatic plant watering
// Technology: Arduino
// Author: Victor Fisac (git@victorfisac)


#define     TIME_24_HOURS       1000*60*60*24


int userMaxHumidityThreshold;       // Maximum humidity threshold to stop watering
int userMinHumidityThreshold;       // Minimum humidity threshold to start watering
int userTemperatureThreshold;       // Minimum temperature threshold to start watering
int userMinHumidityForRain;         // Minimum humidity threshold to be considered as rain
int userRainCheck;                  // Flag to avoid watering in case it has rained in the previous 24 hours

int timesWatered;
int timesRaining;
int isRaining;
int timeCounter;


void InitLogic()
{
    userMaxHumidityThreshold = 60;
    userMinHumidityThreshold = 15;
    userTemperatureThreshold = 20;
    userMinHumidityForRain = 90;
    userRainCheck = 1;

    timesWatered = 0;
    timesRaining = 0;
    isRaining = 0;
    timeCounter = 0;
}

void CheckHumidity()
{
    if (isRaining == 1)
    {
        if (airHumidity <= userMinHumidityForRain)
        {
            isRaining = 0;

            PrintConsole("It has stopped raining");
        }
    }
    else
    {
        if (airHumidity > userMinHumidityForRain)
        {
            isRaining = 1;
            timesRaining++;

            PrintConsole("It is now raining");
        }
    }

    timeCounter += PROGRAM_DELTA_TIME;

    if (timeCounter >= TIME_24_HOURS)
    {
        timeCounter = 0;
        timesRaining = 0;
    }
}

int CheckRainLogic()
{
    int result = 1;

    if (userRainCheck == 1)
    {
        if (timesRaining > 0)
        {
            result = 0;
        }
    }

    return result;
}

void CheckPumpBehaviour()
{
    if (floorHumidity > userMaxHumidityThreshold)
    {
        SetPump(0);
        return;
    }
    
    if (airTemperature >= userTemperatureThreshold &&
      floorHumidity <= userMinHumidityThreshold &&
        CheckRainLogic() == 1)
    {
        SetPump(1);
    }
}

#endif