#if !defined(LCD_H)
#define LCD_H

// Project: Automatic plant watering
// Technology: Arduino
// Author: Victor Fisac (git@victorfisac)


#include <LiquidCrystal_I2C.h>


LiquidCrystal_I2C lcd(0x27, 16, 2);


void InitScreen()
{
    lcd.init();
    lcd.backlight();
}

void ClearScreen()
{
    lcd.clear();
}

void PrintText(String first, String second)
{
    ClearScreen();

    lcd.setCursor(0, 0);
    lcd.print(first);

    if (second.length() > 0)
    {
        lcd.setCursor(0, 1);
        lcd.print(second);
    }
}

void PrintTitleValue(String first, int value, String units)
{
    lcd.setCursor(0, 0);
    lcd.print(first);

    if (value != -1)
    {
        lcd.print(value);
    }

    lcd.print(units);
}

void PrintTitleValue(String first, float value, String units)
{
    lcd.setCursor(0, 0);

    lcd.print(first);

    if (value != -1)
    {
        lcd.print(value);
    }
    
    lcd.print(units);
}

void PrintSubtitleValue(String first, int value, String units)
{
    lcd.setCursor(0, 1);

    lcd.print(first);

    if (value != -1)
    {
        lcd.print(value);
    }

    lcd.print(units);
}

void PrintSubtitleValue(String first, float value, String units)
{
    lcd.setCursor(0, 1);

    lcd.print(first);

    if (value != -1)
    {
        lcd.print(value);
    }

    lcd.print(units);
}

void PrintText(String first, int second)
{
    ClearScreen();

    lcd.print(first);

    lcd.setCursor(0, 1);
    lcd.print(second);
}

void PrintConsole(String value)
{
    Serial.println(value);
}

void PrintConsoleValue(String title, String value, String unit)
{
    Serial.print(title);
    Serial.print(value);
    Serial.println(unit);
}

void PrintConsoleValue(String title, int value, String unit)
{
    Serial.print(title);
    Serial.print(value);
    Serial.println(unit);
}

void PrintConsoleValue(String title, float value, String unit)
{
    Serial.print(title);
    Serial.print(value);
    Serial.println(unit);
}

#endif