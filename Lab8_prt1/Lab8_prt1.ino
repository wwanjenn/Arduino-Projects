#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// Initialize the library with the I2C address of the LCD (usually 0x27 or 0x3F)
LiquidCrystal_I2C lcd(0x27, 16, 2);

// Custom characters (icons)
byte peace1[8] = {
  0b00000,
  0b00001,
  0b00010,
  0b00010,
  0b00010,
  0b00010,
  0b00001,
  0b00000
};

byte peace2[8] = {
  0b11100,
  0b01010,
  0b01001,
  0b01001,
  0b01001,
  0b10101,
  0b00010,
  0b11100
};

byte love1[8] = {
  0b00110,
  0b01111,
  0b11111,
  0b11111,
  0b01111,
  0b00111,
  0b00011,
  0b00001
};

byte love2[8] = {
  0b01100,
  0b11110,
  0b11111,
  0b11111,
  0b11110,
  0b11100,
  0b11000,
  0b10000
};

byte code1[8] = {
  0b00010,
  0b00100,
  0b01000,
  0b10000,
  0b01000,
  0b00100,
  0b00010,
  0b00000
};

byte code2[8] = {
  0b01000,
  0b00100,
  0b00010,
  0b00001,
  0b00010,
  0b00100,
  0b01000,
  0b00000
};

void setup() {
  // Initialize the LCD
  lcd.init();
  lcd.backlight();

  // Create custom characters
  lcd.createChar(0, peace1);
  lcd.createChar(1, peace2);
  lcd.createChar(2, love1);
  lcd.createChar(3, love2);
  lcd.createChar(4, code1);
  lcd.createChar(5, code2);

  // Display custom characters and text

  lcd.setCursor(1, 0);
  lcd.write(byte(0));  // Peace icon
  lcd.write(byte(1)); 

  lcd.setCursor(7, 0);
  lcd.write(byte(2));  // Love icon
  lcd.write(byte(3)); 

  lcd.setCursor(12, 0);
  lcd.write(byte(4));  // Code icon
  lcd.write(byte(5));

  lcd.setCursor(0,1);
  lcd.print("PEACE");
  
  lcd.setCursor(6, 1);
  lcd.print("LOVE");
 
  lcd.setCursor(11, 1);
  lcd.print("CODE");
}

void loop() {
  // No need to do anything in loop
}