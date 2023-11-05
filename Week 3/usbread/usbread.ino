#include <Servo.h>
char incomingByte;
String data = "";
String data = "";

Servo servo;

void setup()
{
  Serial.begin(9600);
  servo.attach(9);
  Serial.begin(9600);
  servo.attach(9);
}

void loop()
{
  if (Serial.available() > 0)
  {
  if (Serial.available() > 0)
  {
    incomingByte = Serial.read();

    if (incomingByte == 'A')

    if (incomingByte == 'A')
    {
      servo.write(data.toInt());
      data = "";
    }
    else
    else
    {
      data += incomingByte;
      data += incomingByte;
    }
  }
}


  }
}
