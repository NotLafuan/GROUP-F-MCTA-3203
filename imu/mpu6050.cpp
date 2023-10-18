#include <Wire.h>
#include "mpu6050.h"

MPU6050::MPU6050()
{
}

MPU6050::~MPU6050()
{
}

void MPU6050::begin()
{
    Wire.beginTransmission(0x68);
    Wire.write(0x6B);
    Wire.write(0x00);
    Wire.endTransmission();
}

void MPU6050::update()
{
    Wire.beginTransmission(0x68);
    Wire.write(0x43);
    Wire.endTransmission();
    Wire.requestFrom(0x68, 6);
    x = Wire.read() << 8 | Wire.read();
    y = Wire.read() << 8 | Wire.read();
    z = Wire.read() << 8 | Wire.read();
}

int MPU6050::get_x()
{
    return x;
}

int MPU6050::get_y()
{
    return y;
}

int MPU6050::get_z()
{
    return z;
}