void setup() {
  Serial.begin(9600);
  pinMode(9, OUTPUT);
  Serial.println("What is the volume of the Cone?");
}

void loop() {
  float Rad, Hei, Volume;

    Serial.println("What is the radius of the Cone?");
    while(!Serial.available());
    String inputRad = Serial.readStringUntil('\n'); 
    Rad = inputRad.toFloat();
    if(Rad < 0 || !isNumeric(inputRad)){
      Serial.println("Invalid Input");
      return;
    }
    Serial.println(Rad);

    Serial.println("What is the Height of the Cone?");
    while(!Serial.available());
    String inputHei = Serial.readStringUntil('\n'); 
    Hei = inputHei.toFloat();
    if(Hei < 0 || !isNumeric(inputHei)){
      Serial.println("Invalid Input");
      return;
    }
    Serial.println(Hei);

    Volume = 3.14 * Rad * Rad * Hei / 3;
    if(Volume < 0){
      Serial.println("Invalid Input");
      return;
    }

    Serial.print("Volume is ");
    Serial.println(Volume);  

    if(Volume < 100){
      for(int i=0; i<3; i++){
      digitalWrite(9, HIGH);
      delay(5000);
      digitalWrite(9,LOW);
      delay(5000);
      };
    };
    if(Volume >= 100 && Volume <= 500){
      for(int i=0; i<3; i++){
      digitalWrite(9, HIGH);
      delay(3000);
      digitalWrite(9,LOW);
      delay(5000);
      };
    };
    if(Volume > 500){
      for(int i=0; i<3; i++){
      digitalWrite(9, HIGH);
      delay(1000);
      digitalWrite(9,LOW);
      delay(3000);
      };
    };

    float Cho;
    String inputCho;
  do {
    Serial.println("Do you want to find the volume of another cone? (0 = Yes, 1 = No)");
    while (!Serial.available());
    inputCho = Serial.readStringUntil('\n');
    Cho = inputCho.toFloat();
    if (inputCho != "0" && inputCho != "1" || !isNumeric(inputCho)) {
      Serial.println("Invalid Input");
    }
  } while (inputCho != "0" && inputCho != "1" || !isNumeric(inputCho));

  if (Cho == 0) {

  } 
  if (Cho == 1) {
    Serial.println("Goodbye!");
    delay(100000000);
  }
}
    



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