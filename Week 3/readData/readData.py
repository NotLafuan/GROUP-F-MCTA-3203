import serial
import matplotlib.pyplot as plt

ser = serial.Serial('COM6', 9600)
array= []

try:
    while True:
        pot_value = ser.readline().decode().strip()
        array.append(float(pot_value))
        plt.clf()
        plt.plot(array)
        plt.pause(0.00001)
        print("Potentiometer Value:", pot_value)
except KeyboardInterrupt:
    plt.close()
    ser.close()
    print("Serial connection closed.")
