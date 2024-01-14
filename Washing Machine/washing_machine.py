import serial

prev_send_data = ''
with serial.Serial('COM18', 9600) as ser_control, \
        serial.Serial('COM7', 9600) as ser_display:
    while True:
        raw_time = int(ser_control.readline().decode())
        second = raw_time % 60
        minute = raw_time // 60
        send_data = str(minute*100 + second) + '\r\n'
        if send_data != prev_send_data:
            print(send_data.encode())
            ser_display.write(send_data.encode())
            prev_send_data = send_data
