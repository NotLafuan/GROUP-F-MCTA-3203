#define NUMBER_AMOUNT 10
#define SEGMENT_AMOUNT 7

int sevenPins[SEGMENT_AMOUNT] = {2, 3, 4, 5, 6, 7, 8};
int sevenSegment[NUMBER_AMOUNT * SEGMENT_AMOUNT] =
    {0, 0, 0, 0, 0, 0, 1,  // 0
     1, 0, 0, 1, 1, 1, 1,  // 1
     0, 0, 1, 0, 0, 1, 0,  // 2
     0, 0, 0, 0, 1, 1, 0,  // 3
     1, 0, 0, 1, 1, 0, 0,  // 4
     0, 1, 0, 0, 1, 0, 0,  // 5
     0, 1, 0, 0, 0, 0, 0,  // 6
     0, 0, 0, 1, 1, 1, 1,  // 7
     0, 0, 0, 0, 0, 0, 0,  // 8
     0, 0, 0, 0, 1, 0, 0}; // 9

int currentNumber = 0;
bool clickedAdd = false;
bool clickedReset = false;
const int addButton = A4;
const int resetButton = A5;

void setup()
{
    pinMode(addButton, INPUT_PULLUP);
    pinMode(resetButton, INPUT_PULLUP);
    for (int i = 0; i < SEGMENT_AMOUNT; i++)
        pinMode(sevenPins[i], OUTPUT);
    Serial.begin(9600);
}

void loop()
{
    for (int i = 0; i < SEGMENT_AMOUNT; i++)
        digitalWrite(sevenPins[i], sevenSegment[currentNumber * SEGMENT_AMOUNT + i]);
    int add = digitalRead(addButton);
    if (!add && !clickedAdd)
    {
        clickedAdd = true;
        currentNumber++;
        if (currentNumber >= NUMBER_AMOUNT)
            currentNumber = 0;
    }
    if (add)
        clickedAdd = false;
    int reset = digitalRead(resetButton);
    if (!reset && !clickedReset)
    {
        clickedReset = true;
        currentNumber = 0;
    }
    if (reset)
        clickedReset = false;
}