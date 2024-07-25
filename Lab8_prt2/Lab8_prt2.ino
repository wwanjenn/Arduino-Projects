#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// Initialize the library with the I2C address of your LCD.
// The address 0x27 is a common default address for I2C LCDs. 
// Change it if your LCD uses a different address.
LiquidCrystal_I2C lcd(0x27, 16, 2); // Set the LCD address to 0x27 for a 16 chars and 2 line display

const int LDR1 = A2;
const int LDR2 = A3;

const int lcdColumns = 16;
const int lcdRows = 2;
String message1 = "                WELCOME TO THE PUP-CPE DEPARTMENT";

String message2 = "        GOODBYE, SEE YOU AGAIN NEXT TIME!!!!        ";
int msgLength1 = message1.length();
int msgLength2 = message2.length();

void setup() {
  // Initialize the LCD
  lcd.init();
  lcd.backlight();
  lcd.clear();
  pinMode(LDR1, INPUT);
  pinMode(LDR2, INPUT);
  Serial.begin(9600);
}

void loop() {
  int ldr1Value = analogRead(LDR1);
  int ldr2Value = analogRead(LDR2);
  Serial.println("ldr1");
  Serial.println(ldr1Value);
  Serial.println("ldr2");
  Serial.println(ldr2Value);

  // Determine if LDRs are enabled
  bool ldr1Enabled = ldr1Value > 100; // Adjust threshold as needed
  bool ldr2Enabled = ldr2Value > 100; // Adjust threshold as needed

  if (ldr1Enabled && !ldr2Enabled) {
    scrollMessageLTR(message1, msgLength1, ldr1Enabled, ldr2Enabled);
  } else if (!ldr1Enabled && ldr2Enabled) {
    scrollMessageLTR(message2, msgLength2, ldr1Enabled, ldr2Enabled);
  } else {
  
  }
  
}

void scrollMessageLTR(String message2, int messageLength2, bool ldr1State, bool ldr2State) {
  for (int position = msgLength2 + lcdColumns; position >= 0; position--) {
    int ldr1Value = analogRead(LDR1);
    int ldr2Value = analogRead(LDR2);
    Serial.println(ldr1Value);
    Serial.println(ldr2Value);
  
    bool ldr1Enabled = ldr1Value > 100; // Adjust threshold as needed
    bool ldr2Enabled = ldr2Value > 100; // Adjust threshold as needed
    if (ldr1Enabled != ldr1State || ldr2Enabled != ldr2State) {
        lcd.clear();
        return;
    }
    lcd.clear();

    lcd.setCursor(0, 1);

    int start = max(0, position - lcdColumns);

    int len = min(position, lcdColumns);

    lcd.print(message2.substring(start, start + len));

    if (position < lcdColumns && position > 0) {
      lcd.setCursor(lcdColumns - position, 1);
      lcd.print(message2.substring(0, position));
    }
    
    delay(300);
  }
  lcd.setCursor(0, 1);
  lcd.clear();
}
