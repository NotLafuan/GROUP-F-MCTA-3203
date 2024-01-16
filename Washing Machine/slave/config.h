#include <SevSeg.h>

#define RED 6
#define BUZZER 7

byte numDigits = 4;
byte digitPins[] = {52, 46, 44, 31};
byte segmentPins[] = {50, 42, 35, 39, 41, 48, 33, 37};

#define RESISTORSONSEGMENTS false
#define HARDWARECONFIG COMMON_ANODE
#define UPDATEWITHDELAYS false
#define LEADINGZEROS true
#define DISABLEDECPOINT true