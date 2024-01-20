import serial
import requests
import threading
import time

data_control = ''
data_master = ''
thread_stop = False
card = ''
status = '1'
timer = 1
mode = 1


def update_control():
    global thread_stop, data_control, data_master
    with serial.Serial('COM16', 9600) as ser:
        while not thread_stop:
            data_control = ser.readline().decode().strip()
            ser.write(card.encode())


def update_master():
    global thread_stop, data_master, status
    with serial.Serial('COM24', 9600) as ser:
        while not thread_stop:
            data_master = ser.readline().decode().strip()
            if status == '1':
                ser.write('g'.encode())
            else:
                ser.write('h'.encode())


def update_web():
    global thread_stop, data_control, status, timer, mode
    while not thread_stop:
        post = {"status": status, "timer": timer, "mode": mode}
        requests.post('http://127.0.0.1:5000/send_data', json=post)
        time.sleep(1)


if __name__ == '__main__':
    control_thread = threading.Thread(target=update_control)
    master_thread = threading.Thread(target=update_master)
    web_thread = threading.Thread(target=update_web)
    control_thread.start()
    master_thread.start()
    web_thread.start()

    try:
        while True:
            try:
                data = f'{data_control} {data_master}'
                ir, water, card, level = data_master.split()
                status, timer, *mode = data_control.split()
                mode = ' '.join(mode)
                print(f'\r{data:100}', end='')
            except ValueError:
                ...
    except KeyboardInterrupt:
        ...
    except Exception as e:
        print(e)
    thread_stop = True
    print('Done')
