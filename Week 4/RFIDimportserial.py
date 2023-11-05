import serial

# Open a serial connection to the Arduino
arduino = serial.Serial('COM6', baudrate=9600, timeout=1)

while True:
    arduino_data = arduino.readline().decode('utf-8').strip()
    if arduino_data:
        print(f'Received data from Arduino: {arduino_data}')
    if arduino_data == '35 B2 15 AD':
        arduino.write('f'.encode())
    elif arduino_data == '2D 83 06 31':
        arduino.write('a'.encode())


