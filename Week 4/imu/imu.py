import serial
import time

time.sleep(3)
ax_lst, ay_lst, az_lst, gx_lst, gy_lst, gz_lst = [], [], [], [], [], []
with serial.Serial('COM11', 9600) as ser:
    ax_lst, ay_lst, az_lst, gx_lst, gy_lst, gz_lst = [], [], [], [], [], []
    while True:
        try:
            data = ser.readline().decode('utf-8').strip()
            _, ax, ay, az, _, gx, gy, gz = data.split()
            ax, ay, az, gx, gy, gz = \
                float(ax), float(ay), float(az), float(gx), float(gy), float(gz)
            ax_lst.append(ax)
            ay_lst.append(ay)
            az_lst.append(az)
            gx_lst.append(gx)
            gy_lst.append(gy)
            gz_lst.append(gz)
            print(f'Accel: {ax:7.2f} {ay:7.2f} {az:7.2f} Gyro: {gx:7.2f} {gy:7.2f} {gz:7.2f}')
        except ValueError:
            continue
        except KeyboardInterrupt:
            break

with open('data.txt', 'w+') as f:
    text = ''
    for ax, ay, az, gx, gy, gz in zip(ax_lst, ay_lst, az_lst, gx_lst, gy_lst, gz_lst):
        text += f'{ax} {ay} {az} {gx} {gy} {gz}\n'
    f.write(text)
