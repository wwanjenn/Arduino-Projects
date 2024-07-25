#include <Keypad.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

#define NOTE_B0  31 * 5
#define NOTE_C1  33 * 5
#define NOTE_CS1 35 * 5
#define NOTE_D1  37 * 5
#define NOTE_DS1 39 * 5
#define NOTE_E1  41 * 5
#define NOTE_F1  44 * 5
#define NOTE_FS1 46 * 5
#define NOTE_G1  49 * 5
#define NOTE_GS1 52 * 5
#define NOTE_A1  55 * 5
#define NOTE_AS1 58 * 5
#define NOTE_B1  62 * 5
#define NOTE_C2  65 * 5
#define NOTE_CS2 69 * 5
#define NOTE_D2  73 * 5
#define NOTE_DS2 78 * 5
#define NOTE_E2  82 * 5
#define NOTE_F2  87 * 5
#define NOTE_FS2 93 * 5
#define NOTE_G2  98 * 5
#define NOTE_GS2 104 * 5
#define NOTE_A2  110 * 5
#define NOTE_AS2 117 * 5
#define NOTE_B2  123 * 5
#define NOTE_C3  131 * 5
#define NOTE_CS3 139 * 5
#define NOTE_D3  147 * 5
#define NOTE_DS3 156 * 5
#define NOTE_E3  165 * 5
#define NOTE_F3  175 * 5
#define NOTE_FS3 185 * 5
#define NOTE_G3  196 * 5
#define NOTE_GS3 208 * 5
#define NOTE_A3  220 * 5
#define NOTE_AS3 233 * 5
#define NOTE_B3  247 * 5
#define NOTE_C4  262 * 5
#define NOTE_CS4 277 * 5
#define NOTE_D4  294 * 5
#define NOTE_DS4 311 * 5
#define NOTE_E4  330 * 5
#define NOTE_F4  349 * 5
#define NOTE_FS4 370 * 5
#define NOTE_G4  392 * 5
#define NOTE_GS4 415 * 5
#define NOTE_A4  440 * 5
#define NOTE_AS4 466 * 5
#define NOTE_B4  494 * 5
#define NOTE_C5  523 * 5
#define NOTE_CS5 554 * 5
#define NOTE_D5  587 * 5
#define NOTE_DS5 622 * 5
#define NOTE_E5  659 * 5
#define NOTE_F5  698 * 5
#define NOTE_FS5 740 * 5
#define NOTE_G5  784 * 5
#define NOTE_GS5 831 * 5
#define NOTE_A5  880 * 5
#define NOTE_AS5 932 * 5
#define NOTE_B5  988 * 5
#define NOTE_C6  1047 * 5
#define NOTE_CS6 1109 * 5
#define NOTE_D6  1175 * 5
#define NOTE_DS6 1245 * 5
#define NOTE_E6  1319 * 5
#define NOTE_F6  1397 * 5
#define NOTE_FS6 1480 * 5
#define NOTE_G6  1568 * 5
#define NOTE_GS6 1661 * 5
#define NOTE_A6  1760 * 5
#define NOTE_AS6 1865 * 5
#define NOTE_B6  1976 * 5
#define NOTE_C7  2093 * 5
#define NOTE_CS7 2217 * 5
#define NOTE_D7  2349 * 5
#define NOTE_DS7 2489 * 5
#define NOTE_E7  2637 * 5
#define NOTE_F7  2794 * 5
#define NOTE_FS7 2960 * 5
#define NOTE_G7  3136 * 5
#define NOTE_GS7 3322 * 5
#define NOTE_A7  3520 * 5
#define NOTE_AS7 3729 * 5
#define NOTE_B7  3951 * 5
#define NOTE_C8  4186 * 5
#define NOTE_CS8 4435 * 5
#define NOTE_D8  4699 * 5
#define NOTE_DS8 4978 * 5
#define REST      0

 // Adjust the tempo if needed

int buzzer = 13; // Define the buzzer pin

LiquidCrystal_I2C lcd(0x27, 16, 2);

const byte ROWS = 4;
const byte COLS = 4;

char keys[ROWS][COLS] = {
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'}
};

byte rowPins[ROWS] = {9, 8, 7, 6};
byte colPins[COLS] = {5, 4, 3, 2};

Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);

const int buzzerPin = 13;
int attempts = 0;

const int ledPins[] = {A0, A1, A2, A3}; // Example: 3 LEDs connected to pins 11, 12, and 13
const int numLeds = 4;

const char correctPassword[] = "1234"; // Change this to your desired password
String username= "";
char enteredPassword[5];
int attemptCount = 0;

void setup() {
  lcd.init();
  lcd.backlight();

  pinMode(buzzerPin, OUTPUT);

  for (int i = 0; i < numLeds; i++) {
    pinMode(ledPins[i], OUTPUT);
  }

  for (int i = 0; i < numLeds; i++) {
    digitalWrite(ledPins[i], LOW);
  }

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Enter password:");

  Serial.begin(9600);
}

void loop() {
  username = getUsername();
  getPassword();
  
}

String getUsername(){
  lcd.setCursor(0,0);
  lcd.print("ENTER YOUR NAME: ");
  Serial.print("ENTER YOUR NAME: ");
  while (!Serial.available());
  username = Serial.readStringUntil('\n');
  Serial.println(username);
  lcd.setCursor(0,1);
  lcd.print(username);
  delay(5000);
  return username;
}

void getPassword() {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("ENTER PASSWORD: ");
  
  char enteredPassword[5]; // Create a 5-char array for 4 digits + null terminator
  memset(enteredPassword, 0, sizeof(enteredPassword)); // Clear the enteredPassword array
  int index = 0;

  while (index < 4) {
    char key = keypad.getKey();
    if (key != NO_KEY) {
      if (key == '*' || key == '#') {
        // Ignore '*' and '#'
        continue;
      } else {
        enteredPassword[index] = key;
        lcd.setCursor(index, 1); // Set cursor to the position where the asterisk should be displayed
        lcd.print("*");
        index++;
      }
    }
  }

  // After entering 4 digits, add null terminator
  enteredPassword[4] = '\0';

  // Compare entered password with the correct password
  if (strcmp(enteredPassword, correctPassword) == 0) {
    correctPasswordEntered();
    return;
  } else {
    wrongPasswordEntered(); 
  }
}

void correctPasswordEntered() {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("WELCOME, ");
  lcd.setCursor(0, 1);
  lcd.print(username);
  lcd.print("!!!");

  for (int i = 0; i < numLeds; i++) {
    digitalWrite(ledPins[i-1], LOW);
    digitalWrite(ledPins[i], HIGH);
    delay(500);
  }
  successMelody();

  for (int i = 0; i < numLeds; i++) {
    digitalWrite(ledPins[i], LOW);
  }
  lcd.clear();
  attempts = 0;
  username = "";
  
}

void wrongPasswordEntered() {
  attempts++;
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("ACCESS DENIED!!!, ");
  lcd.setCursor(2, 1);
  lcd.print(attempts);
  lcd.print(" ATTEMPTS");
  tone(13, NOTE_A3, 2000);

  for (int i = 0; i < numLeds; i++) {
    digitalWrite(ledPins[i], HIGH);
  }

  for (int i = 0; i < numLeds; i++) {
    digitalWrite(ledPins[i-1], HIGH);
    digitalWrite(ledPins[i], LOW);
    delay(500);
  }

  for (int i = 0; i < numLeds; i++) {
    digitalWrite(ledPins[i], LOW);
  }

  lcd.clear();
  lcd.setCursor(0, 0);
  if (attempts >= 3) {
    disableKeypad();
  }
  else{
    lcd.clear();
    lcd.setCursor(0, 0);
    getPassword();
  }
}

void disableKeypad() {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.println("ACCESS DENIED!!!");
  noKeyMelody();



  for(int i = 3600; i >= 0; i--){
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Locked for:");
    lcd.setCursor(0, 1);
    lcd.print(i);
    lcd.print("s");

    for (int i = 0; i < numLeds; i++) {
      digitalWrite(ledPins[i], HIGH);
    }

    delay(1000);

    for (int i = 0; i < numLeds; i++) {
      digitalWrite(ledPins[i], LOW);
    }
  }

}

void noKeyMelody() {
  int tempo = 180;
  int melody1[] = {
    // Nokia Ringtone 
    NOTE_E5, 8, NOTE_D5, 8, NOTE_FS4, 4, NOTE_GS4, 4, 
    NOTE_CS5, 8, NOTE_B4, 8, NOTE_D4, 4, NOTE_E4, 4, 
    NOTE_B4, 8, NOTE_A4, 8, NOTE_CS4, 4, NOTE_E4, 4,
    NOTE_A4, 2
  };
  
  int notes1 = sizeof(melody1) / sizeof(melody1[0]) / 2;
  int wholenote1 = (60000 * 4) / tempo;
  int divider1 = 0, noteDuration1 = 0;

  for (int thisNote = 0; thisNote < notes1 * 2; thisNote = thisNote + 2) {
    divider1 = melody1[thisNote + 1];
    if (divider1 > 0) {
      noteDuration1 = (wholenote1) / divider1;
    } else if (divider1 < 0) {
      noteDuration1 = (wholenote1) / abs(divider1);
      noteDuration1 *= 1.5;
    }
    tone(buzzer, melody1[thisNote], noteDuration1 * 0.9);
    delay(noteDuration1);
    noTone(buzzer);
  }
}

void successMelody() {
  int tempo = 160;
  int melody2[] = {
    // Pacman
    NOTE_B4, 16, NOTE_B5, 16, NOTE_FS5, 16, NOTE_DS5, 16, //1
    NOTE_B5, 32, NOTE_FS5, -16, NOTE_DS5, 8, NOTE_C5, 16,
    NOTE_C6, 16, NOTE_G6, 16, NOTE_E6, 16, NOTE_C6, 32, NOTE_G6, -16, NOTE_E6, 8,
    NOTE_B4, 16,  NOTE_B5, 16,  NOTE_FS5, 16,   NOTE_DS5, 16,  NOTE_B5, 32,  //2
    NOTE_FS5, -16, NOTE_DS5, 8,  NOTE_DS5, 32, NOTE_E5, 32,  NOTE_F5, 32,
    NOTE_F5, 32,  NOTE_FS5, 32,  NOTE_G5, 32,  NOTE_G5, 32, NOTE_GS5, 32,  NOTE_A5, 16, NOTE_B5, 8
  };

  int notes2 = sizeof(melody2) / sizeof(melody2[0]) / 2;
  int wholenote2 = (60000 * 4) / tempo;
  int divider2 = 0, noteDuration2 = 0;

  for (int thisNote = 0; thisNote < notes2 * 2; thisNote = thisNote + 2) {
    divider2 = melody2[thisNote + 1];
    if (divider2 > 0) {
      noteDuration2 = (wholenote2) / divider2;
    } else if (divider2 < 0) {
      noteDuration2 = (wholenote2) / abs(divider2);
      noteDuration2 *= 1.5;
    }
    tone(buzzer, melody2[thisNote], noteDuration2 * 0.9);
    delay(noteDuration2);
    noTone(buzzer);
  }
}


