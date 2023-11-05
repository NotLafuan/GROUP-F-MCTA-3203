import serial
ser = serial.Serial('COM6', 9600)
while True:
    data = ser.readline().decode('utf-8').strip()
    if data.startswith("Detected Gesture: "):
        gesture = data.split(": ")[1]
        if gesture == "Up":
            # Perform an action for Gesture 1
            print("Left Gesture detected")
        elif gesture == "Down":
            # Perform an action for Gesture 2
            print("Right Gesture detected")
        elif gesture == "No Gesture":
            print("No gesture detected")
        # Add more gesture actions as needed    