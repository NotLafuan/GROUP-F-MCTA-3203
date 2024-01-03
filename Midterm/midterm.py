import serial
import matplotlib.pyplot as plt
import msvcrt

inputs_arduino = serial.Serial('COM14', 9600) # arduino with inputs 
outputs_arduino = serial.Serial('COM7', 9600) # arduino with outputs

plot = False
disable = False

ldrs = []

# uuid and users pairs
users = {'35 B2 15 AD': 'E',
         'E1 A5 CB 93': 'F'}

if __name__ == '__main__':
    while True:
        try:
            # detect keyboard input from laptop
            keypress = ord(msvcrt.getch()) if msvcrt.kbhit() else 0
            if chr(keypress) == 'q':
                disable = False
            if chr(keypress) == 'w':
                disable = True
            if chr(keypress) == 'e':
                outputs_arduino.write('C'.encode()) # turn on LED (only when disabled)
            if chr(keypress) == 'r':
                outputs_arduino.write('D'.encode()) # turn off LED (only when disabled)
            if disable:
                continue

            data = inputs_arduino.readline().decode().strip() # read data from arduino with inputs
            print(f'\r{data:50}', end='') # print serial data from arduino
            # check if the serial data is from card reader
            if data.startswith('UUID:'):
                uuid = data.split(':')[1].strip() # UUID: 35 B2 15 AD -> uuid = 35 B2 15 AD
                if uuid not in users: # check if uuid in the users list
                    outputs_arduino.write('G'.encode()) # if not send "unknown"
                    continue
                outputs_arduino.write(users[uuid].encode()) # else send the user
                continue
            # if the data is not from card reader
            # and from the LDR and IR sensor
            # splitting data string to usable integer value
            ldr, ir = map(int, data.split())
            if plot:
                ldrs.append(ldr) # add ldr values for plotting
                plt.clf()
                plt.plot(ldrs)
                plt.pause(0.00001)
            # use the ir value to turn on LED
            if not ir:
                outputs_arduino.write('C'.encode()) # ON
            else:
                outputs_arduino.write('D'.encode()) # OFF
            # use the ldr value to turn on buzzer
            if ldr < 200:
                outputs_arduino.write('A'.encode()) # ON
            else:
                outputs_arduino.write('B'.encode()) # OFF
        except KeyboardInterrupt:
            inputs_arduino.close()
            outputs_arduino.close()
            print('\nstopped')
            break
        except ValueError:
            ...
