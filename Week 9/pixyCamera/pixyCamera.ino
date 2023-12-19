#include <Pixy.h>
Pixy pixy;

const int R = 8;
const int G = 9;
const int B = 10;

void setup()
{
    Serial.begin(9600);
    pixy.init();

    pinMode(R, OUTPUT);
    pinMode(G, OUTPUT);
    pinMode(B, OUTPUT);
}
void loop()
{
    int blocks = pixy.getBlocks();
    if (blocks)
    {
        // Loop through detected blocks
        for (int i = 0; i < blocks; i++)
        {
            Serial.print("Block ");
            Serial.print(i);
            Serial.print(": ");
            Serial.print("Signature: ");
            Serial.print(pixy.blocks[i].signature);
            Serial.print(" X: ");
            Serial.print(pixy.blocks[i].x);
            Serial.print(" Y: ");
            Serial.println(pixy.blocks[i].y);

            // Detect Colour Blue
            if (pixy.blocks[i].signature == 1)
            {

                digitalWrite(R, LOW);
                digitalWrite(G, LOW);
                digitalWrite(B, HIGH);

                // Detect Colour Green
            }
            else if (pixy.blocks[i].signature == 2)
            {
                digitalWrite(R, LOW);
                digitalWrite(G, HIGH);
                digitalWrite(B, LOW);

                // Detect Colour Red
            }
            else if (pixy.blocks[i].signature == 3)
            {
                digitalWrite(R, HIGH);
                digitalWrite(G, LOW);
                digitalWrite(B, LOW);
            }
        }
    }
}