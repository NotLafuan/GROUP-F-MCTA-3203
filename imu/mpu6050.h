class MPU6050
{
private:
    int16_t x, y, z;

public:
    MPU6050();
    ~MPU6050();
    void begin();
    void update();
    int get_x();
    int get_y();
    int get_z();
};
