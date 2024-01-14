#include "SevSeg.h"
SevSeg sevseg; // Initiate a seven segment controller object

int time = 10;
unsigned long prevTime;

void setup()
{
    Serial.begin(9600);
    byte numDigits = 4;
    byte digitPins[] = {5, 4, 3, 2};
    byte segmentPins[] = {6, 7, 8, 9, 10, 11, 12, 13};
    bool resistorsOnSegments = 0;
    // variable above indicates that 4 resistors were placed on the digit pins.
    // set variable to 1 if you want to use 8 resistors on the segment pins.
    sevseg.begin(COMMON_ANODE, numDigits, digitPins, segmentPins, resistorsOnSegments);
    sevseg.setBrightness(90);
    prevTime = millis();
}
void loop()
{
    if (millis() - prevTime > 500)
    {
            prevTime = millis();
            String a = Serial.readString();
            time = a.toInt();
    }
    printTime(time);
}
void printTime(int temp)
{
    sevseg.setNumber(temp, 3);
    sevseg.refreshDisplay(); // Must run repeatedly
}