#include <BluetoothSerial.h>
#include <ESP32Servo.h>

BluetoothSerial SerialBT;
Servo myservo;
long start_time;

const int resistorValue = 10;

void setup() {
  Serial.begin(115200);
  SerialBT.begin("ESP32_BT_Server");  // Set a name for Bluetooth server
  myservo.attach(32); // Adjust the pin to match your hardware setup
 start_time = millis();

}

void loop() {

if (millis() - start_time > 2000)
{
  int sensorValue = analogRead(A0);
  double voltage = sensorValue * (5.0 / 1023.0);  // Convert to voltage
  // Use the Steinhart-Hart equation to convert voltage to temperature
  double temperature = (1.0 / ((log(voltage / 5.0) / resistorValue) + (1.0 / 298.15))) - 273.15;
  SerialBT.print("Temperature: ");
  SerialBT.print(temperature);
  SerialBT.print(" °C\n");
  start_time = millis();
  Serial.println(temperature);
}
  
  

  if (SerialBT.available()) {
    char inputChar = SerialBT.read();
    Serial.println(inputChar);
    
    if (inputChar == 'M') {
      // When "M" command is received, set the flag to move the servo
      myservo.write(90);
      Serial.println("inputChar");
      }if (inputChar == 'A') {
      // When "M" command is received, set the flag to move the servo
      myservo.write(180);
      Serial.println("inputChar");
      }

  // Add a small delay to avoid excessive looping
  }
  delay(20);
  
}
