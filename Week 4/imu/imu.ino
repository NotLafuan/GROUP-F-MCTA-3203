#include <Wire.h>
#include <MPU6050.h>

MPU6050 mpu;
int16_t ax, ay, az, gx, gy, gz;
uint32_t ax_0 = 0, ay_0 = 0;

void Calibrate()
{
    unsigned int count1;
    count1 = 0;
    do
    {
        mpu.getMotion6(&ax, &ay, &az, &gx, &gy, &gz);
        ax_0 = ax_0 + ax; // Accumulate Samples
        ay_0 = ay_0 + ay;
        count1++;
    } while (count1 != 0x0400); // 1024 times
    ax_0 = ax_0 >> 10;          // division between 1024
    ay_0 = ay_0 >> 10;
}

void setup()
{
    Serial.begin(9600);
    Wire.begin();
    mpu.initialize();
    Calibrate();
}

void loop()
{
    mpu.getMotion6(&ax, &ay, &az, &gx, &gy, &gz);
    Serial.print("Accel: ");
    Serial.print(ax - (int)ax_0);
    Serial.print(" ");
    Serial.print(ay - (int)ay_0);
    Serial.print(" ");
    Serial.print(az);
    Serial.print(" Gyro: ");
    Serial.print(gx);
    Serial.print(" ");
    Serial.print(gy);
    Serial.print(" ");
    Serial.println(gz);
    delay(10); // Adjust the delay as needed
}