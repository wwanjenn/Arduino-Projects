int buttState = 0;     
int lastButtState = 0; 
int buttCounter = 0;

void setup() {
  pinMode(8, INPUT);
  pinMode(9, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  buttState = digitalRead(8);
  
    if (buttState != lastButtState) {
      if (buttCounter >= 5) {
        if (buttState == HIGH) {
          digitalWrite(9, HIGH);
          Serial.print("Button Presses: ");
          Serial.println(buttCounter);
          Serial.println("ALL DONE!"); 
        }
        if (buttState == LOW) {
          Serial.println("Off (Button Released)");
          digitalWrite(9, LOW);
        }
      } else{
        if (buttState == HIGH) {
          Serial.println("On (Button Pressed)");
          digitalWrite(9, HIGH);
          buttCounter++;
          Serial.print("Button Presses: ");
          Serial.println(buttCounter);
        } else {
          Serial.println("Off (Button Released)");
          digitalWrite(9, LOW);
        }
      }
    }
  lastButtState = buttState;
  delay(50); 
}
