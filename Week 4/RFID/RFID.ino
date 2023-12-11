#include <SPI.h>
#include <MFRC522.h>

#define SS_PIN 53
#define RST_PIN 5

MFRC522 rfid(SS_PIN, RST_PIN); // Instance of the class

MFRC522::MIFARE_Key key;

// Init array that will store new NUID
byte nuidPICC[4];
char data;

void setup()
{
  Serial.begin(9600);
  SPI.begin();     // Init SPI bus
  rfid.PCD_Init(); // Init MFRC522
  pinMode(12, OUTPUT);
  pinMode(13, OUTPUT);

  for (byte i = 0; i < 6; i++)
  {
    key.keyByte[i] = 0xFF;
  }
}

void loop()
{

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

  printHex(rfid.uid.uidByte, rfid.uid.size);
  Serial.println();
  rfid.PICC_HaltA();

  rfid.PCD_StopCrypto1();

  if (Serial.available() > 0)
    data = Serial.read();

  if (data == 'f')
  {
    digitalWrite(13, HIGH);
    delay(2000);
    digitalWrite(13, LOW);
  }

  if (data == 'a')
  {
    digitalWrite(12, HIGH);
    delay(2000);
    digitalWrite(12, LOW);
  }
}

void printHex(byte *buffer, byte bufferSize)
{
  for (byte i = 0; i < bufferSize; i++)
  {
    Serial.print(buffer[i] < 0x10 ? " 0" : " ");
    Serial.print(buffer[i], HEX);
  }
}
