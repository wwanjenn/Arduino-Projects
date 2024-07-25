#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// Initialize the LCD objects with the addresses found using the scanner
LiquidCrystal_I2C lcd1(0x26, 16, 2); // Adjust the address 0x27
LiquidCrystal_I2C lcd2(0x22, 16, 2); // Adjust the address 0x26
LiquidCrystal_I2C lcd3(0x27, 16, 2); // Adjust the address 0x25
LiquidCrystal_I2C lcd4(0x25, 16, 2); // Adjust the address 0x24
LiquidCrystal_I2C lcd5(0x23, 16, 2); // Adjust the address 0x23
LiquidCrystal_I2C lcd6(0x24, 16, 2); // Adjust the address 0x22

const char message1[] = "at Nap Stop.........";
const char message2[] = "at Byte Me..........";
const char message3[] = "at Hay There........";
const char message4[] = "at CTRL+Z...........";
const char message5[] = "at Deja View........";
const char message6[] = "at Bean There.......";

const char mesg1[] = "Deja is arriving.....";
const char mesg2[] = "Bean is arriving.....";
const char mesg3[] = "Byte arriving........";

bool First = true;
bool Second = false;
bool Third = false;

void rotateBooleans3() {
  if (First) {
    First = false;
    Second = true;
  } else if (Second) {
    Second = false;
    Third = true;
  } else if (Third) {
    Third = false;
    First = true;
  }
}

void setup() {
  Serial.begin(9600);
  lcd1.init();
  lcd2.init();
  lcd3.init();
  lcd4.init();
  lcd5.init();
  lcd6.init();
  
  lcd1.backlight();
  lcd2.backlight();
  lcd3.backlight();
  lcd4.backlight();
  lcd5.backlight();
  lcd6.backlight();
  
  // Define pins for digital input from another Arduino

}

void printMessages(LiquidCrystal_I2C &lcd1, LiquidCrystal_I2C &lcd2, LiquidCrystal_I2C &lcd3,
                   LiquidCrystal_I2C &lcd4, LiquidCrystal_I2C &lcd5, LiquidCrystal_I2C &lcd6,
                   const char *msg1, const char *msg2, const char *msg3,
                   const char *msg4, const char *msg5, const char *msg6,
                   const char *mesg1, const char *mesg2, const char *mesg3,
                   bool First, bool Second, bool Third) {
  
  // Set cursor positions on the first row and clear the previous message
  lcd1.setCursor(0, 0);
  lcd1.print("                ");
  lcd2.setCursor(0, 0);
  lcd2.print("                ");
  lcd3.setCursor(0, 0);
  lcd3.print("                ");
  lcd4.setCursor(0, 0);
  lcd4.print("                ");
  lcd5.setCursor(0, 0);
  lcd5.print("                ");
  lcd6.setCursor(0, 0);
  lcd6.print("                ");

  // Determine which message to print
  const char *currentMesg = "";
  if (First) {
    currentMesg = mesg1;
  } else if (Second) {
    currentMesg = mesg2;
  } else if (Third) {
    currentMesg = mesg3;
  }

  // Read digital inputs from another Arduino
  bool lcd1State = digitalRead(2);
  bool lcd2State = digitalRead(3);
  bool lcd3State = digitalRead(4);
  bool lcd4State = digitalRead(5);
  bool lcd5State = digitalRead(6);
  bool lcd6State = digitalRead(7);

  // Print arriving messages on the first row of the selected LCD
  if (lcd1State) {
    lcd1.setCursor(0, 0);
    lcd1.print(currentMesg);
    Serial.print("LCD1 Row 0: ");
    Serial.println(currentMesg);
  } else if (lcd2State) {
    lcd2.setCursor(0, 0);
    lcd2.print(currentMesg);
    Serial.print("LCD2 Row 0: ");
    Serial.println(currentMesg);
  } else if (lcd3State) {
    lcd3.setCursor(0, 0);
    lcd3.print(currentMesg);
    Serial.print("LCD3 Row 0: ");
    Serial.println(currentMesg);
  } else if (lcd4State) {
    lcd4.setCursor(0, 0);
    lcd4.print(currentMesg);
    Serial.print("LCD4 Row 0: ");
    Serial.println(currentMesg);
  } else if (lcd5State) {
    lcd5.setCursor(0, 0);
    lcd5.print(currentMesg);
    Serial.print("LCD5 Row 0: ");
    Serial.println(currentMesg);
  } else if (lcd6State) {
    lcd6.setCursor(0, 0);
    lcd6.print(currentMesg);
    Serial.print("LCD6 Row 0: ");
    Serial.println(currentMesg);
  }
  
  // Set cursor positions on the second row
  lcd1.setCursor(0, 1);
  lcd2.setCursor(0, 1);
  lcd3.setCursor(0, 1);
  lcd4.setCursor(0, 1);
  lcd5.setCursor(0, 1);
  lcd6.setCursor(0, 1);

  // Print messages on LCDs
  lcd1.print(msg1);
  lcd2.print(msg2);
  lcd3.print(msg3);
  lcd4.print(msg4);
  lcd5.print(msg5);
  lcd6.print(msg6);

  // Serial print for debugging
  Serial.print("LCD1 Row 1: ");
  Serial.println(msg1);
  Serial.print("LCD2 Row 1: ");
  Serial.println(msg2);
  Serial.print("LCD3 Row 1: ");
  Serial.println(msg3);
  Serial.print("LCD4 Row 1: ");
  Serial.println(msg4);
  Serial.print("LCD5 Row 1: ");
  Serial.println(msg5);
  Serial.print("LCD6 Row 1: ");
  Serial.println(msg6);
  delay(3000);
}

void loop() {
  printMessages(lcd1, lcd2, lcd3, lcd4, lcd5, lcd6, message1, message2, message3, message4, message5, message6, mesg1, mesg2, mesg3, First, Second, Third);
  rotateBooleans3();
  delay(5000); // Delay before restarting the animation
}
