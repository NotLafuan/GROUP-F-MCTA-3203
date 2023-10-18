#pragma once

class HMC5883L
{
private:
    int16_t x, y, z;
    double heading;

public:
    HMC5883L();
    ~HMC5883L();
    void begin();
    void update();
    int get_x();
    int get_y();
    int get_z();
    double get_heading();
};
