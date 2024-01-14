// Mario's Ideas
// MAX7219 - using Led Control library to display all   leds one by one
#include <LedControl.h>

int DIN = 11;
int CS = 7;
int CLK = 13;

LedControl lc = LedControl(12, 11, 10, 1);

void setup()
{
    lc.shutdown(0, false);
    lc.setIntensity(0, 8);
    lc.clearDisplay(0);
}

void loop()
{
    for (int j = 0; j < 8; j++)
    {
        for (int i = 0; i < 8; i++)
        {
            lc.setLed(0, j, i, true);
            delay(100);
            lc.setLed(0, j, i, false);
        }
    }
}