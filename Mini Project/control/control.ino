#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include "config.h"

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

String modes[] = {"Delicate", "Normal", "Quickwash", "Heavy Duty", "Rinse & Spin", "Bedding"};
int modeTimers[] = {4 * 60, 2 * 60, 20, 5 * 60, 65, 5 * 60};
int modeSelector = 0;
enum statuses
{
  Stop,
  Running,
  Pause
};
statuses status; // 0=stop, 1=stop, 2=pause

bool button1Released = true;
bool button2Released = true;
bool button3Released = true;

int timer;
unsigned long startTime;

bool authorized = true;

void potUpdate();
void buttonUpdate();
void displayUpdate();
void displayTime();
void displayModes();
void timerUpdate();
void serialSend();
bool checkUpdate();
void displayNotAuthorized();

void setup()
{
  Serial.begin(9600);
  status = Stop;
  startTime = millis();

  pinMode(BUTTON1, INPUT);
  pinMode(BUTTON2, INPUT);
  pinMode(BUTTON3, INPUT);
  pinMode(POT, INPUT);

  while (!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS))
    ;
}

void loop()
{
  if (Serial.available())
  {
    char data = Serial.read();
    if (data == 'a')
      authorized = true;
    else if (data == 'n')
      authorized = false;
  }

  if (authorized)
  {
    potUpdate();
    buttonUpdate();
    displayUpdate();
    timerUpdate();
  }
  else
  {
    displayNotAuthorized();
  }
  serialSend();
}

void potUpdate()
{
  if (status != Stop)
    return;
  int pot = analogRead(POT);
  modeSelector = pot > 170 * 0 ? 0 : modeSelector;
  modeSelector = pot > 170 * 1 ? 1 : modeSelector;
  modeSelector = pot > 170 * 2 ? 2 : modeSelector;
  modeSelector = pot > 170 * 3 ? 3 : modeSelector;
  modeSelector = pot > 170 * 4 ? 4 : modeSelector;
  modeSelector = pot > 170 * 5 ? 5 : modeSelector;
}

void buttonUpdate()
{
  int button1 = digitalRead(BUTTON1);
  int button2 = digitalRead(BUTTON2);
  int button3 = digitalRead(BUTTON3);
  if (button1 && button1Released)
  {
    button1Released = false;
    if (status == Running || status == Pause)
    {
      status = Stop;
    }
    else if (status == Stop)
    {
      status = Running;
    }
  }
  if (button2 && button2Released)
  {
    button2Released = false;
    if (status == Running)
    {
      status = Pause;
    }
    else if (status == Pause)
    {
      status = Running;
    }
  }

  if (button3 && button3Released)
    button3Released = false;

  if (!button1)
    button1Released = true;
  if (!button2)
    button2Released = true;
  if (!button3)
    button3Released = true;
}

void displayUpdate()
{
  display.clearDisplay();
  display.setTextColor(BLACK, WHITE);
  display.setCursor(12, 28);
  if (status == Stop)
  {
    display.println("START");
    displayModes();
    timer = modeTimers[modeSelector];
  }
  else if (status == Running)
  {
    display.println("STOP");
    displayTime();
  }
  else if (status == Pause)
  {
    display.println("PAUSE");
    displayTime();
  }
  display.display();
}

void displayTime()
{
  display.setCursor(50, 15);
  display.setTextColor(WHITE, BLACK);
  display.setTextSize(5);
  if (int(timer / 60))
  {
    char buffer[3];
    sprintf(buffer, "%2d\0", int(timer / 60));
    display.println(buffer);
    display.setTextSize(1);
    display.setCursor(110, 42);
    display.setTextColor(BLACK, WHITE);
    display.println("min");
  }
  else
  {
    char buffer[3];
    sprintf(buffer, "%2d\0", timer);
    display.println(buffer);
    display.setTextSize(1);
    display.setCursor(110, 42);
    display.setTextColor(BLACK, WHITE);
    display.println("sec");
  }
  display.setTextSize(1);
}

void displayModes()
{
  int i = 0;
  for (String mode : modes)
  {
    display.setTextSize(1);
    if (modeSelector == i)
      display.setTextColor(BLACK, WHITE);
    else
      display.setTextColor(WHITE, BLACK);
    display.setCursor(55, 11 * i);
    display.println(mode);
    i++;
  }
}

void timerUpdate()
{
  if (millis() - startTime > 1000)
  {
    if (button3Released)
      startTime = millis();
    if (status == Running)
      timer--;
    if (timer <= 0)
      status = Stop;
  }
}

void serialSend()
{
  Serial.print(status);
  Serial.print(" ");
  Serial.print(timer);
  Serial.print(" ");
  Serial.println(modes[modeSelector]);
}

void displayNotAuthorized()
{
  display.clearDisplay();
  display.setTextColor(WHITE, BLACK);
  display.setCursor(15, 10);
  display.setTextSize(2);
  display.println("Card Not");
  display.print("Authorized");
  display.setTextSize(1);
  display.display();
}