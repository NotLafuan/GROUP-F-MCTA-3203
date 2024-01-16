import serial
import requests


with serial.Serial('COM16', 9600) as ser_control:
    while True:
        try:
            data = ser_control.readline().decode().strip()
            status, timer, *mode = data.split()
            mode = ' '.join(mode)
            post = {"status": status, "timer": timer, "mode": mode}
            requests.post('http://127.0.0.1:5000/send_data', json=post)
            print(status, timer, mode)
        except ValueError:
            print('ValueError', data)
        except KeyboardInterrupt:
            break
