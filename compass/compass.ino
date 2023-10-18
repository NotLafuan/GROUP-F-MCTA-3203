#include <Wire.h>
#include "hmc5883l.h"

HMC5883L hmc;

void setup()
{
    Wire.begin();
    hmc.begin();
    Serial.begin(9600);
}

void loop()
{
    hmc.update();
    Serial.print(hmc.get_x());
    Serial.print("\t");
    Serial.print(hmc.get_y());
    Serial.print("\t");
    Serial.print(hmc.get_z());
    Serial.print("\t");
    Serial.println(hmc.get_heading());
}