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

bool motorDir = false;
unsigned long motorDirStart = 0;

char water, load, card, motor;
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

  if (motor == 'g')
  {
    if (!wash && water == 'f')
    {
      wash = true;
      motorTimer = millis() + 6000;
    }
    if (water == 'e')
      wash = false;
  }
  else
  {
    wash = false;
    timer = 6000;
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
      wash = false;
      digitalWrite(RED, HIGH);
      digitalWrite(BUZZER, HIGH);
    }
    if (load == 'o')
    {
      digitalWrite(RED, LOW);
      digitalWrite(BUZZER, LOW);
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

  if (timer <= 0 && wash)
    spinMotor();
  else
    stopMotor();

  detectUpdate();
  sevseg.refreshDisplay();
}

void spinMotor()
{
  if (millis() - motorDirStart >= 3000)
  {
    if (motorDir)
      motorDir = false;
    else
      motorDir = true;
    motorDirStart = millis();
  }

  if (motorDir)
  {
    analogWrite(in1, 100);
    digitalWrite(in2, LOW);
  }
  else
  {
    digitalWrite(in1, LOW);
    analogWrite(in2, 100);
  }
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
  motor = Wire.read();
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