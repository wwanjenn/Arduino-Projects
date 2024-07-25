// Pin definitions
const int LDR1 = A2;
const int LDR2 = A3;

// 7-segment display segment pins
const int segmentPins1[] = {2, 3, 4, 5, 6, 7, 8};
const int segmentPins2[] = {9, 10, 11, 12, 13, A0, A1};

// Characters to be displayed
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

const byte hello[7][7] = {
  {0, 1, 1, 0, 1, 1, 1}, // H
  {1, 1, 1, 1, 0, 0, 1}, // E
  {0, 0, 0, 1, 1, 1, 0}, // L
  {0, 0, 0, 1, 1, 1, 0}, // L
  {1, 1, 1, 1, 1, 1, 0}, // O
  {0, 0, 0, 0, 0, 0, 0}, 
  {0, 1, 1, 0, 1, 1, 1} // H
  
};

const byte bye[5][7] = {
  {0, 0, 1, 1, 1, 1, 1}, // B
  {0, 1, 1, 0, 0, 1, 1}, // Y
  {1, 0, 0, 1, 1, 1, 1}, // E
  {0, 0, 0, 0, 0, 0, 0},
  {0, 0, 1, 1, 1, 1, 1} // B
};

// Function to display a character on a 7-segment display
void displayCharacter(const byte segmentsData[], int segmentPins[]) {
  for (int i = 0; i < 7; i++) {
    digitalWrite(segmentPins[i], segmentsData[i]);
  }
}

// Function to scroll a message


void scrollMessageLTR(const byte message[][7], int messageLength, int segmentPins1[], int segmentPins2[], int delayTime, bool ldr1State, bool ldr2State) {
  int ldr1Value = analogRead(LDR1);
  int ldr2Value = analogRead(LDR2);

  bool ldr1Enabled = ldr1Value > 80; // Adjust threshold as needed
  bool ldr2Enabled = ldr2Value > 80; // Adjust threshold as needed
  for (int i = 0; i <= messageLength - 2; i++) {
    if (ldr1Enabled != ldr1State || ldr2Enabled != ldr2State) {
        return;
    }
    displayCharacter(message[i], segmentPins1);
    displayCharacter(message[i + 1], segmentPins2);
    delay(delayTime);
  }
}

void scrollMessageRTL(const byte message[][7], int messageLength, int segmentPins1[], int segmentPins2[], int delayTime, bool ldr1State, bool ldr2State) {
  int ldr1Value = analogRead(LDR1);
  int ldr2Value = analogRead(LDR2);

  bool ldr1Enabled = ldr1Value > 80; // Adjust threshold as needed
  bool ldr2Enabled = ldr2Value > 80; // Adjust threshold as needed
  for (int i = 0; i <= messageLength - 2; i++) {
    if (ldr1Enabled != ldr1State || ldr2Enabled != ldr2State) {
        return;
    }
    displayCharacter(message[i + 1], segmentPins1);
    displayCharacter(message[i], segmentPins2);
    delay(delayTime);
  }
}

void setup() {
  // Initialize segment pins as outputs
  for (int i = 0; i < 7; i++) {
    pinMode(segmentPins1[i], OUTPUT);
    pinMode(segmentPins2[i], OUTPUT);
  }
  // Initialize LDR pins as inputs
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
  bool ldr1Enabled = ldr1Value > 80; // Adjust threshold as needed
  bool ldr2Enabled = ldr2Value > 80; // Adjust threshold as needed

  if (ldr1Enabled && !ldr2Enabled) {
    scrollMessageLTR(hello, 7, segmentPins1, segmentPins2, 750, ldr1Enabled, ldr2Enabled);
  } else if (!ldr1Enabled && ldr2Enabled) {
    scrollMessageRTL(bye, 5, segmentPins1, segmentPins2, 750, ldr1Enabled, ldr2Enabled);
  } else {
    displayCharacter(digits[0], segmentPins1);
    displayCharacter(digits[0], segmentPins2);
  }
  // Pause before checking LDRs again
}
