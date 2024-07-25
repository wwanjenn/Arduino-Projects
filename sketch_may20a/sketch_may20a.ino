#include <Keypad.h>

const byte ROWS = 4; 
const byte COLS = 3; 

const int ledPins[] = {A2, A1, 2, 10, 11, 12, 13, A0}; // Pins for the 8 LEDs
const int numLEDs = 8;
const int duration = 3000; // Duration in milliseconds (3 seconds)
const int delayTime = duration / numLEDs; // Time each LED stays on

const int leftLEDs[] = {A2, A1, 2, 10}; // Pins for the first 4 LEDs
const int rightLEDs[] = {A0, 13, 12, 11};  // Pins for the next 4 LEDs (right to left)
const int numLEDss = 4;
const int blinkDuration = 500; // Duration in milliseconds for each LED to stay on

const int blinkDuration9 = 2000; // Duration in milliseconds (2 seconds)



char hexaKeys[ROWS][COLS] = {
  {'9', '6', '3'},
  {'8', '5', '2'},
  {'7', '4', '1'},
  {'*', '0', '#'}
};

  int num1 = 0;
  int num2 = 1;
  int numNext;


byte rowPins[ROWS] = {9, 8, 7, A3}; 
byte colPins[COLS] = {5, 4, 3}; 

Keypad customKeypad = Keypad(makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS); 

bool isNumeric(String str) {
  bool foundDecimal = false;
  for (unsigned int i = 0; i < str.length(); i++) {
    if (!isdigit(str[i])) {
      if (str[i] == '.' && !foundDecimal) {
        foundDecimal = true;
      } else {
        return false;
      }
    }
  }
  return true;
}

void setup(){
  Serial.begin(9600);
  for (int i = 0; i < numLEDs; i++) {
      pinMode(ledPins[i], OUTPUT);
  }
  for (int i = 0; i < numLEDss; i++) {
        pinMode(leftLEDs[i], OUTPUT);
        pinMode(rightLEDs[i], OUTPUT);
    }

  Serial.println("Input on Keypad");
}
  
void loop(){

  char customKey = customKeypad.getKey();
  if (customKey){
    Serial.println(customKey);
  
    if(customKey == '1'){
      Serial.print("Enter the number of rows for the pyramid:");
      while(!Serial.available());
      String inputrows = Serial.readStringUntil('\n');
      Serial.println(inputrows);
      int rows = inputrows.toFloat();
      if (!isNumeric(inputrows)) {
        Serial.println("Invalid Input");
        Serial.println("Input on Keypad");
        return;
        
      }

      for (int i = 1; i <= rows; i++) {
      // Print spaces
        for (int j = i; j < rows; j++) {
          Serial.print(" ");
        }
      // Print stars
          for (int k = 1; k <= (2 * i - 1); k++) {
            Serial.print("*");
          }
      // Move to the next line
      Serial.println();
      }
    }
    if(customKey == '2'){
      Serial.print("Enter the size of the square:");
      while(!Serial.available());
      String inputsize = Serial.readStringUntil('\n');
      Serial.println(inputsize);
      int size = inputsize.toFloat();
      if (!isNumeric(inputsize)) {
        Serial.println("Invalid Input");
        Serial.println("Input on Keypad");
        return;
      }
      for (int i = 0; i < size; ++i) {
          for (int j = 0; j < size; ++j) {
              if (i == 0 || i == size - 1 || j == 0 || j == size - 1) {
                  Serial.print("[]");
              } else {
                  Serial.print("  ");
              }
          }
          Serial.println();
      }
    }
    else if(customKey == '3'){
      Serial.print("Enter the number of Fibonacci Terms:");
      while (!Serial.available()); // Wait for input
      String inputterm = Serial.readStringUntil('\n');
      Serial.println(inputterm);
      int numTerms = inputterm.toFloat();
      if (!isNumeric(inputterm)) {
        Serial.println("Invalid Input");
        Serial.println("Input on Keypad");
        return;
      }

      // Print the initial two terms manually
      Serial.print("Fibonacci Series: 0, 1");

      // Initialize Fibonacci sequence with 0 and 1
      int num1 = 0;
      int num2 = 1;

      // Calculate and display the rest of the Fibonacci sequence
      for (int i = 2; i < numTerms; ++i) {
          int numNext = num1 + num2;
          Serial.print(", ");
          Serial.print(numNext);
          num1 = num2;
          num2 = numNext;
      }
      Serial.println();
    }
    else if(customKey == '4'){
      Serial.print("Enter a number to generate its multiplication table up to x10:");
      while(!Serial.available());
      String inputnum = Serial.readStringUntil('\n');
      Serial.println(inputnum);
      int number = inputnum.toFloat();
      if (!isNumeric(inputnum)) {
        Serial.println("Invalid Input");
        Serial.println("Input on Keypad");
        return;
      }
      if (number) {
        // Print the multiplication table for the given number
        Serial.print("Multiplication table for ");
        Serial.println(number);
        for (int i = 1; i <= 10; i++) {
          Serial.print(number);
          Serial.print(" x ");
          Serial.print(i);
          Serial.print(" = ");
          Serial.println(number * i);
        }
      } else {
        Serial.println("Invalid input. Please enter a valid number.");
      }
    }
    else if(customKey == '5'){
      Serial.print("Enter radius:");
      while(!Serial.available());
      String inputrad = Serial.readStringUntil('\n');
      Serial.println(inputrad);
      float radius = inputrad.toFloat();
      if (!isNumeric(inputrad)) {
        Serial.println("Invalid Input");
        Serial.println("Input on Keypad");
        return;
      }
      Serial.print("Enter height:");
      while(!Serial.available());
      String inputhei = Serial.readStringUntil('\n');
      Serial.println(inputhei);
      float height = inputhei.toFloat();
      if (!isNumeric(inputhei)) {
        Serial.println("Invalid Input");
        Serial.println("Input on Keypad");
        return;
      }
      float surface_area = 3.14 * radius * (radius + sqrt(pow(radius, 2) + pow(height, 2)));
      Serial.print("Surface Area:");
      Serial.println(surface_area);
      
    }
    else if(customKey == '6'){
      String logo[] = {
      "  ****          ***  ",
      "    ***  ****  **    ",
      "     *** **   **     ",
      "      ****   **      ",
      "      ****  **       ",
      "     ** ****     *   ",
      "    **           *   ",
      "  ****************   "
      };
    // Print each line of the pattern
      for (int i = 0; i < 8; i++) {
        Serial.println(logo[i]);
      }
    }
    else if(customKey == '7'){
      for (int i = 0; i < numLEDs; i++) {
        digitalWrite(ledPins[i], HIGH); // Turn on the LED
        delay(delayTime); // Wait for the calculated delay time
        // digitalWrite(ledPins[i], LOW); // Turn off the LED 
      }
      delay(3000); // Wait for 3 seconds
      for (int i = 0; i < numLEDs; i++) {
          digitalWrite(ledPins[i], LOW);
      }
    }
    else if(customKey == '8'){
      for (int i = 0; i < numLEDss; i++) {
          digitalWrite(leftLEDs[i], HIGH); // Turn on the LED
          delay(blinkDuration);            // Wait for the specified duration
          digitalWrite(leftLEDs[i], LOW);  // Turn off the LED
      }
      
      // Blink LEDs from the right
      for (int i = 0; i < numLEDss; i++) {
          digitalWrite(rightLEDs[i], HIGH); // Turn on the LED
          delay(blinkDuration);             // Wait for the specified duration
          digitalWrite(rightLEDs[i], LOW);  // Turn off the LED
      }
    }
    else if(customKey == '9'){
      Serial.println("Error: Something went wrong!");

      // Blink all LEDs for 2 seconds
      for (int i = 0; i < numLEDs; i++) {
          digitalWrite(ledPins[i], HIGH); // Turn on the LED
      }
      delay(blinkDuration9); // Wait for the specified duration
      for (int i = 0; i < numLEDs; i++) {
          digitalWrite(ledPins[i], LOW); // Turn off the LED
      } 
    }
    else if(customKey == '0'){
      Serial.println("INVALID CODE!!!");
    } 
    else if (customKey == '*' || customKey =='#'){
      Serial.println(customKey);
    }
    String user_input;
    do {
      Serial.println("Do you want to try again? Y/N");
      while (!Serial.available()); // Wait until data is available
      user_input = Serial.readStringUntil('\n'); // Read the input string until newline character
      user_input.trim(); // Remove leading and trailing whitespaces
      
      // Check if the input is neither 'Y' nor 'N'
      if (!user_input.equals("Y") && !user_input.equals("N")) {
        Serial.println("Invalid input. Please enter 'Y' or 'N': ");
      }
    } while (!user_input.equals("Y") && !user_input.equals("N"));

    if (user_input.equals("Y")) {
      Serial.println("Input on Keypad");
    }
    if (user_input.equals("N")) {
      delay(600000); // Delay for 600 seconds if user chooses not to try again
    }
  }

  }



  
  

