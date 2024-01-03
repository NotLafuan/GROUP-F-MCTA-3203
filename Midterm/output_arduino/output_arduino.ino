#include <LCD_I2C.h>
#define BUZZER 8
#define LED 2

LCD_I2C lcd(0x27, 16, 2); // Default address of most PCFBUZZER574 modules, change according

char signal;
void setup()
{

    pinMode(BUZZER, OUTPUT);
    pinMode(LED, OUTPUT);
    Serial.begin(9600);
    lcd.begin();
    lcd.backlight();
}

void loop()
{
    if (Serial.available())
    {
        signal = Serial.read();
        if (signal == 'A')
        {
            digitalWrite(BUZZER, HIGH);
        }
        if (signal == 'B')
        {
            digitalWrite(BUZZER, LOW);
        }
        if (signal == 'C')
        {
            digitalWrite(LED, HIGH);
        }
        if (signal == 'D')
        {
            digitalWrite(LED, LOW);
        }
        if (signal == 'E')
        {
            lcd.clear();
            lcd.setCursor(5, 0);
            lcd.print("AIMAN");
        }
        if (signal == 'F')
        {
            lcd.clear();
            lcd.setCursor(5, 0);
            lcd.print("NAUFAL");
        }
        if (signal == 'G')
        {
            lcd.clear();
            lcd.setCursor(5, 0);
            lcd.print("UNKNOWN");
        }
    }
}