#include <SPI.h>
#include <MFRC522.h>

// PIN Numbers : RESET + SDAs
#define RST_PIN         10
#define SS_1_PIN        9
#define SS_2_PIN        8
#define SS_3_PIN        7

// Led and Relay PINS
#define GreenLed        2
#define relayIN         3
#define RedLed          4

// List of Tags UIDs that are allowed to open the puzzle
byte tagarray[][4] = {
  {0x4B, 0x17, 0xBC, 0x79},
  {0x8A, 0x2B, 0xBC, 0x79}, 
  {0x81, 0x29, 0xBC, 0x79},
  {0xE6, 0xDF, 0xBB, 0x79},
};

// Unlocking status:
int tagcount = 0;
bool access = false;

#define NR_OF_READERS   3

byte ssPins[] = {SS_1_PIN, SS_2_PIN, SS_3_PIN};

// Create an MFRC522 instance:
MFRC522 mfrc522[NR_OF_READERS];

/**
   Initialize.
*/
void setup() {
  Serial.begin(9600);           // Initialize serial communications with the PC
  Serial.println("serial begins");   
  while (!Serial);              // Do nothing if no serial port is opened (added for Arduinos based on ATMEGA32U4)

  SPI.begin();                  // Init SPI bus

  // Initializing Inputs and Outputs
  pinMode(GreenLed, OUTPUT);
  digitalWrite(GreenLed, LOW);
  pinMode(relayIN, OUTPUT);
  digitalWrite(relayIN, HIGH);
  pinMode(RedLed, OUTPUT);
  digitalWrite(RedLed, LOW);

  // Looking for MFRC522 readers
  for (uint8_t reader = 0; reader < NR_OF_READERS; reader++) {
    Serial.print("Initializing reader ");
    Serial.println(reader);
    mfrc522[reader].PCD_Init(ssPins[reader], RST_PIN);
    Serial.print("Reader ");
    Serial.print(reader);
    Serial.println(" initialized successfully.");
    mfrc522[reader].PCD_DumpVersionToSerial();
    delay(1000);
    mfrc522[reader].PCD_Init(ssPins[reader], RST_PIN);
    mfrc522[reader].PCD_DumpVersionToSerial();
    delay(1000);
  }
}

/*
   Main loop.
*/
void loop() {
  for (uint8_t reader = 0; reader < NR_OF_READERS; reader++) {
    // Looking for new cards
    if (mfrc522[reader].PICC_IsNewCardPresent() && mfrc522[reader].PICC_ReadCardSerial()) {
      Serial.print(F("Reader "));
      Serial.print(reader);

      // Show some details of the PICC (that is: the tag/card)
      Serial.print(F(": Card UID:"));
      dump_byte_array(mfrc522[reader].uid.uidByte, mfrc522[reader].uid.size);
      Serial.println();

      for (int x = 0; x < sizeof(tagarray); x++) {               // tagarray's row
        for (int i = 0; i < mfrc522[reader].uid.size; i++) {     // tagarray's columns
          if (mfrc522[reader].uid.uidByte[i] != tagarray[x][i]) { // Comparing the UID in the buffer to the UID in the tag array
            DenyingTag();
            break;
          } else {
            if (i == mfrc522[reader].uid.size - 1) {              // Test if we browsed the whole UID
              AllowTag();
            } else {
              continue;                                           // We still didn't reach the last cell/column: continue testing!
            }
          }
        }
        if (access) break;                                        // If the Tag is allowed, quit the test
      }

      if (access) {
        if (tagcount == NR_OF_READERS) {
          OpenDoor();
        } else {
          MoreTagsNeeded();
        }
      } else {
        UnknownTag();
      }
      
      // Halt PICC
      mfrc522[reader].PICC_HaltA();
      // Stop encryption on PCD
      mfrc522[reader].PCD_StopCrypto1();
    }
  }
}

/**
   Helper routine to dump a byte array as hex values to Serial.
*/
void dump_byte_array(byte * buffer, byte bufferSize) {
  for (byte i = 0; i < bufferSize; i++) {
    Serial.print(buffer[i] < 0x10 ? " 0" : " ");
    Serial.print(buffer[i], HEX);
  }
}

void printTagcount() {
  Serial.print("Tag n°");
  Serial.println(tagcount);
}

void DenyingTag() {
  tagcount = tagcount;
  access = false;
}

void AllowTag() {
  tagcount = tagcount + 1;
  access = true;
}

void Initialize() {
  tagcount = 0;
  access = false;
}

void OpenDoor() {
  Serial.println("Welcome! the door is now open");
  Initialize();
  digitalWrite(relayIN, LOW);
  digitalWrite(GreenLed, HIGH);
  delay(2000);
  digitalWrite(relayIN, HIGH);
  delay(500);
  digitalWrite(GreenLed, LOW);
}

void MoreTagsNeeded() {
  printTagcount();
  Serial.println("System needs more cards");
  digitalWrite(RedLed, HIGH);
  delay(1000);
  digitalWrite(RedLed, LOW);
  access = false;
}

void UnknownTag() {
  Serial.println("This Tag isn't allowed!");
  printTagcount();
  for (int flash = 0; flash < 5; flash++) {
    digitalWrite(RedLed, HIGH);
    delay(100);
    digitalWrite(RedLed, LOW);
    delay(100);
  }
}
