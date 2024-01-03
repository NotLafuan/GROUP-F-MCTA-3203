#include <SPI.h>
#include <MFRC522.h>

#define LDR A0
#define IR 3

#define SS_PIN 53
#define RST_PIN 5

MFRC522 rfid(SS_PIN, RST_PIN); // Instance of the class

MFRC522::MIFARE_Key key;

// Init array that will store new NUID
byte nuidPICC[4];
char data;

void setup()
{
    pinMode(LDR, INPUT);
    pinMode(IR, INPUT);
    Serial.begin(9600);
    SPI.begin();     // Init SPI bus
    rfid.PCD_Init(); // Init MFRC522

    for (byte i = 0; i < 6; i++)
    {
        key.keyByte[i] = 0xFF;
    }
}

void loop()
{
    // send LDR and IR value to serial port
    int ldr = analogRead(LDR);
    int ir = digitalRead(IR);
    Serial.print(ldr);
    Serial.print(" ");
    Serial.println(ir);

    // Look for new cards
    if (!rfid.PICC_IsNewCardPresent())
        return;

    // Verify if the NUID has been readed
    if (!rfid.PICC_ReadCardSerial())
        return;

    for (byte i = 0; i < 4; i++)
    {
        nuidPICC[i] = rfid.uid.uidByte[i];
    }

    Serial.print("UUID:");
    printHex(rfid.uid.uidByte, rfid.uid.size);
    Serial.println();
    rfid.PICC_HaltA();

    rfid.PCD_StopCrypto1();

    delay(500);
}

// used for printing UUID to serial port
void printHex(byte *buffer, byte bufferSize)
{
    for (byte i = 0; i < bufferSize; i++)
    {
        Serial.print(buffer[i] < 0x10 ? " 0" : " ");
        Serial.print(buffer[i], HEX);
    }
}
