#include <SoftwareSerial.h>

#define R_PIN 11
#define G_PIN 10
#define B_PIN 9

SoftwareSerial colorSensor(3, 2);
long start = 0;
int colors[4];
int i = 0;

void normalize_colors(int colors[4]);

void setup()
{
    colorSensor.begin(9600);
    Serial.begin(9600);
    pinMode(R_PIN, OUTPUT);
    pinMode(G_PIN, OUTPUT);
    pinMode(B_PIN, OUTPUT);
    pinMode(12, OUTPUT);
    digitalWrite(12, LOW);
}

void loop()
{
    if (millis() - start > 500)
    {
        colorSensor.write("AT+FRE\r\n");
        i = 0;
        start = millis();
        normalize_colors(colors);
        analogWrite(R_PIN, colors[0]);
        analogWrite(G_PIN, colors[1]);
        analogWrite(B_PIN, colors[2]);
        for (size_t i = 0; i < 3; i++)
        {
            Serial.print(colors[i]);
            Serial.print(" ");
        }
        Serial.println();
    }

    if (colorSensor.available())
    {
        char data = colorSensor.read();
        if (data == ':')
            colors[i++] = colorSensor.parseInt();
    }
}

void normalize_colors(int colors[4])
{
    float max = 0;
    for (size_t i = 0; i < 3; i++)
        if (colors[i] > max)
            max = (float)colors[i];
    for (size_t i = 0; i < 3; i++)
        colors[i] = (int)((float)colors[i] / (float)max * 255.0f);
}