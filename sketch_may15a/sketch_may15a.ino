const int segmentPins1[] = {2, 3, 4, 5, 6, 7, 8}; // Pins for units display
const int segmentPins2[] = {9, 10, 11, 12, 13, A0, A1}; // Pins for tens display
const int switchPin = A2; // Pin for toggle switch
int counter = 0; // Initialize counter

const byte digits[10][7] = {
  {1, 1, 1, 1, 1, 1, 0}, // 0
  {0, 1, 1, 0, 0, 0, 0}, // 1
  {1, 1, 0, 1, 1, 0, 1}, // 2
  {1, 1, 1, 1, 0, 0, 1}, // 3
  {0, 1, 1, 0, 0, 1, 1}, // 4
  {1, 0, 1, 1, 0, 1, 1}, // 5
  {1, 0, 1, 1, 1, 1, 1}, // 6
  {1, 1, 1, 0, 0, 0, 0}, // 7
  {1, 1, 1, 1, 1, 1, 1}, // 8
  {1, 1, 1, 0, 0, 1, 1}  // 9
};

void setup() {
  for (int i = 0; i < 7; i++) {
    pinMode(segmentPins1[i], OUTPUT);
    pinMode(segmentPins2[i], OUTPUT);
  }
  pinMode(switchPin, INPUT_PULLUP);
}

void loop() {
  bool direction = digitalRead(switchPin); // Read the switch state
  if (direction == LOW) {
    // Switch is ON, count up
    counter++;
    if (counter > 15) counter = 0; // Reset if counter exceeds 15
  } else {
    // Switch is OFF, count down
    counter--;
    if (counter < 0) counter = 15; // Reset if counter goes below 0
  }

  int units = counter % 10;
  int tens = counter / 10;

  displayNumber(segmentPins2, units); // Display units
  displayNumber(segmentPins1, tens);  // Display tens

  delay(1000); // Delay for 1 second before next count
}

void displayNumber(const int *segmentPins, int number) {
  for (int i = 0; i < 7; i++) {
    digitalWrite(segmentPins[i], digits[number][i]);
  }
}