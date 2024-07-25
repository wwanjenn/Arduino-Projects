#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <Servo.h>
#include <avr/sleep.h>  // For using power down modes

// Define servo and sensor pins for each station
const int servoPins[5] = {9, 10, 11, 12, 13}; // Servo pins for each station
const int irSensorPins[5] = {2, 3, 4, 5, 6}; // IR sensor pins for each station

// Define I2C addresses for each station
const int lcdAddresses[5] = {0x27, 0x26, 0x25, 0x24, 0x23}; // I2C addresses for each station

// Create LCD objects for each station
LiquidCrystal_I2C lcds[5] = {
  LiquidCrystal_I2C(0x27, 16, 2),
  LiquidCrystal_I2C(0x26, 16, 2),
  LiquidCrystal_I2C(0x25, 16, 2),
  LiquidCrystal_I2C(0x24, 16, 2),
  LiquidCrystal_I2C(0x23, 16, 2)
};

Servo servos[5];
bool trainDetected[5] = {false, false, false, false, false};

// Train names and initial positions
String trainNames[2] = {"BYTE", "DEJA"};
int trainPositions[2] = {0, 2}; // BYTE at station 0, DEJA at station 2

// Station names
String stationNames[5] = {"NAP STAP", "BYTE ME", "HAYDAY", "CTRL+Z", "DEJA VIEW"};

void setup() {
  // Attach servos and set initial positions
  for (int i = 0; i < 5; i++) {
    servos[i].attach(servoPins[i]);
    servos[i].write(0); // Initial position of each servo motor
    pinMode(irSensorPins[i], INPUT);

    // Initialize LCDs
    lcds[i].init();
    lcds[i].backlight();
    updateLCD(i, "Waiting.... ", stationNames[i]);
  }
  
  // Manually set initial train detections
  for (int i = 0; i < 2; i++) {
    trainDetected[trainPositions[i]] = true; 
  }

  // Start serial communication for monitoring
  Serial.begin(9600);
}

void loop() {
  static int moveSequence[12][2] = {
    {0, 1}, {2, 3}, {4, 0}, {1, 2}, {3, 4}, {0, 1},
    {2, 3}, {4, 0}, {1, 2}, {3, 4}, {0, 1}, {2, 3}
  };

  for (int i = 0; i < 12; i++) {
    moveTrain(moveSequence[i][0], moveSequence[i][1]);
  }

}

// Function to move the train from one station to another
void moveTrain(int fromStation, int toStation) {
  Serial.println(fromStation);
  Serial.println(toStation);
  if (trainDetected[fromStation] && digitalRead(irSensorPins[fromStation]) == LOW) {
    int trainIndex = getTrainIndexAtStation(fromStation);
    
    if (trainIndex != -1) {
      Serial.print(trainNames[trainIndex]);
      Serial.print(" moving from ");
      Serial.print(stationNames[fromStation]);
      Serial.print(" to ");
      Serial.println(stationNames[toStation]);

      // Update LCD displays
      updateLCD(fromStation, "Train " + trainNames[trainIndex], "to " + stationNames[toStation]);
      updateLCD(toStation, "Train " + trainNames[trainIndex], "to " + stationNames[toStation]);
      trainDetected[fromStation] = false; // Reset detection for the current station
      trainDetected[toStation] = true; // Set detection for the next station
      trainPositions[trainIndex] = toStation; // Update the train position

      delay(5000); // Wait for 5 seconds
      servos[fromStation].write(90); // Open servo to 90 degrees
      delay(5000); // Wait for 5 seconds
      servos[fromStation].write(0); // Close servo back to 0 degrees
    
      updateLCD(fromStation, "Waiting.... ", stationNames[toStation]);
    }
  }
}

// Function to get the train index at a station
int getTrainIndexAtStation(int station) {
  for (int i = 0; i < 2; i++) {
    if (trainPositions[i] == station) {
      return i;
    }
  }
  return -1; // No train at the station
}

// Function to update LCD display at a station
void updateLCD(int station, String line1, String line2) {
  lcds[station].clear();
  lcds[station].setCursor(0, 0);
  lcds[station].print(line1);
  lcds[station].setCursor(0, 1);
  lcds[station].print(line2);
  delay(2000); // Display the message for 2 seconds
}
