void setup()
{
    Serial.begin(9600);
}

void loop()
{
    int potValue = analogRead(A0);
    int percentage = map (potValue,0,1023,0,100);
    Serial.println(percentage);
    if (percentage>70)
        digitalWrite(9,HIGH);
    else
        digitalWrite(9,LOW);
    delay(1000);
}