#include <SPI.h>
#include <MFRC522.h>
#include <Wire.h>
#include "config.h"

MFRC522 rfid(SS_PIN, RST_PIN);
MFRC522::MIFARE_Key key;

byte nuidPICC[4];                        // Init array that will store new NUID
byte uid1[4] = {0x23, 0x0C, 0xC3, 0x10}; // authorize card1
byte uid2[4] = {0x23, 0x1F, 0xE6, 0x0D}; // authorize card2
bool verify;

char outgoingByteIR;
char outgoingByteWaterLevel;
char outgoingByteCard;

void setup()
{
    pinMode(IR, INPUT);
    pinMode(WATER_LEVEL_PIN, INPUT);

    Serial.begin(9600);
    Wire.begin();
    SPI.begin();
    rfid.PCD_Init();

    for (byte i = 0; i < 6; i++)
        key.keyByte[i] = 0xFF;
}
void loop()
{
    if (rfid.PICC_IsNewCardPresent())
    {
        rfid.PICC_ReadCardSerial();
        for (byte i = 0; i < 4; i++)
            nuidPICC[i] = rfid.uid.uidByte[i];
        printHex(rfid.uid.uidByte, rfid.uid.size);
        Serial.println();

        for (size_t i = 0; i < 4; i++)
        {
            if (nuidPICC[i] == uid1[i] || nuidPICC[i] == uid2[i])
                verify = true;
            else
            {
                verify = false;
                break;
            }
        }
    }

    if (verify)
        outgoingByteCard = 'n';
    else
        outgoingByteCard = 'a';

    if (digitalRead(IR))
        outgoingByteIR = 'o';
    else
        outgoingByteIR = 'k';

    if (analogRead(WATER_LEVEL_PIN) >= 100)
        outgoingByteWaterLevel = 'f';
    else
        outgoingByteWaterLevel = 'e';

    delay(500);
    Serial.print(outgoingByteIR);
    Serial.print("\t");
    Serial.print(outgoingByteWaterLevel);
    Serial.print("\t");
    Serial.print(outgoingByteCard);
    Serial.print("\t");
    Serial.println(analogRead(WATER_LEVEL_PIN));
    Wire.beginTransmission(9);
    Wire.write(outgoingByteIR);
    Wire.write(outgoingByteWaterLevel);
    Wire.write(outgoingByteCard);
    Wire.endTransmission(); // end transmission
}

void printHex(byte *buffer, byte bufferSize)
{
    for (byte i = 0; i < bufferSize; i++)
    {
        Serial.print(buffer[i] < 0x10 ? " 0" : " ");
        Serial.print(buffer[i], HEX);
    }
}