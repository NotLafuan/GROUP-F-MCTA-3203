#include "mpu6050.h"

MPU6050 mpu6050;

void setup()
{
    mpu6050.begin();
    Serial.begin(9600);
}

void loop()
{
    mpu6050.update();
    Serial.print(mpu6050.get_x());
    Serial.print("\t");
    Serial.print(mpu6050.get_y());
    Serial.print("\t");
    Serial.println(mpu6050.get_z());
}