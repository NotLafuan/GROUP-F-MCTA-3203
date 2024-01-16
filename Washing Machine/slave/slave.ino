#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <SevSeg.h>
#include "config.h"

SevSeg sevseg;

unsigned long motorTimer;
bool wash = false;
int timer = 6000;
int prevTimer = 0;
bool update = false;

char water, load, card;
char prevWater, prevLoad, prevCard;
int in1 = 2;
int in2 = 3;
char test;
LiquidCrystal_I2C lcd(0x27, 16, 2);

void receiveEvent(int);

void setup()
{
  Serial.begin(9600);

  Wire.begin(9);                // Start the I2C Bus as Slave on address green
  Wire.onReceive(receiveEvent); // Attach a function to trigger when something is received.

  lcd.init();
  lcd.backlight();
  pinMode(RED, OUTPUT);
  pinMode(BUZZER, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);

  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);

  sevseg.begin(HARDWARECONFIG, numDigits, digitPins, segmentPins, RESISTORSONSEGMENTS,
               UPDATEWITHDELAYS, LEADINGZEROS, DISABLEDECPOINT);
  sevseg.setBrightness(90);
}

void loop()
{
  if (wash)
  {
    timer = motorTimer - millis();
    timer = timer / 1000;
    if (timer != prevTimer && timer >= 0)
    {
      prevTimer = timer;
      sevseg.setNumber(timer, 1);
    }
  }
  if (card == 'a')
  {
    if (update)
    {
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Card");
      lcd.setCursor(0, 1);
      lcd.print("Authorized");
    }
    if (load == 'k')
    {
      if (update)
      {
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("Overload!");
      }
      digitalWrite(RED, HIGH);
      digitalWrite(BUZZER, HIGH);
    }
    if (load == 'o')
    {
      digitalWrite(RED, LOW);
      digitalWrite(BUZZER, LOW);
      if (water == 'f')
      {
        if (!wash)
        {
          wash = true;
          motorTimer = millis() + 6000;
        }
      }

      if (water == 'e')
      {
        stopMotor();
        wash = false;
        timer = 6000;
      }
    }
  }
  if (card == 'n' && update)
  {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Card Not");
    lcd.setCursor(0, 1);
    lcd.print("Authorized");
  }
  if (update)
  {
    Serial.print(water);
    Serial.print("\t");
    Serial.print(load);
    Serial.print("\t");
    Serial.println(card);
  }
  if (timer <= 0)
  {
    directionControl();
  }
  detectUpdate();
  sevseg.refreshDisplay();
}

void directionControl()
{
  // Turn on motor A
  analogWrite(in1, 100);
  digitalWrite(in2, LOW);
  delay(2000);

  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);
  delay(1000);

  // Now change motor directions
  digitalWrite(in1, LOW);
  analogWrite(in2, 100);
  delay(2000);

  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);
  delay(1000);
}

void stopMotor()
{
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);
}

void receiveEvent(int bytes)
{
  load = Wire.read();
  water = Wire.read();
  card = Wire.read();
}

void detectUpdate()
{
  if (card != prevCard)
  {
    update = true;
    prevCard = card;
  }
  else if (load != prevLoad)
  {
    update = true;
    prevLoad = load;
  }
  else if (water != prevWater)
  {
    update = true;
    prevWater = water;
  }
  else
  {
    update = false;
  }
}