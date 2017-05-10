//Pin Numbers for Seven-Segment Display
int pinC = 2;
int pinD = 3;
int pinE = 4;
int pinF = 5;
int pinG = 6;
int pinH = 7;
int pinKM = 8;
int pinL = 9;
int pinN = 10;
int pinO = 11;
int pinP = 12;

//Other Inputs and Outputs
int switchPin = 13;
int LEDPin = 14;

//Digits to display on 7-segment display
int digit1 = 10;
int digit2 = 10;
int digit3 = 10;

unsigned long milliseconds;
bool finished = false;

void setup() {
  //Set up pins:
  pinMode(switchPin, INPUT);
  pinMode(pinC, OUTPUT);
  pinMode(pinD, OUTPUT);
  pinMode(pinE, OUTPUT);
  pinMode(pinF, OUTPUT);
  pinMode(pinG, OUTPUT);
  pinMode(pinH, OUTPUT);
  pinMode(pinKM, OUTPUT);
  pinMode(pinL, OUTPUT);
  pinMode(pinN, OUTPUT);
  pinMode(pinO, OUTPUT);
  pinMode(pinP, OUTPUT);
  //Set up serial port:
  Serial.begin(115200);

}

void loop() {
  if (!finished) {
    findTime();
  }
  displayTime();
}

void findTime() {
  // Calculate the time in minutes and seconds from milliseconds
  milliseconds = millis();
  int seconds = (milliseconds / 1000);
  int minutes = (seconds / 60);
  //Break the seconds up into digits and keep minutes under 10 due to number of 
  //digital pins
  if (minutes > 9) {
    digit1 = 0;
  } else {
    digit1 = minutes;
  }
  digit2 = (seconds - (minutes * 60)) / 10;
  digit3 = seconds - (minutes* 60) - (digit2 * 10);
  //Send the time info to the serial display
  Serial.print("Time: ");
  Serial.print(minutes);
  Serial.print(":");
  Serial.print(digit2);
  Serial.println(digit3);
}

void displayTime() {
  //Control the seven-seg display
  int repeat1 = digit1;
  int repeat2 = digit2;
  int countdown = 100;
  
  while (countdown > 0) {
    //Reset pulls high
    digitalWrite(pinP,HIGH);
    digitalWrite(pinO,HIGH);
    digitalWrite(pinKM,HIGH);
    digitalWrite(pinD,HIGH);
    //Reset digit pins low
    digitalWrite(pinC,LOW);
    digitalWrite(pinE,LOW);
    digitalWrite(pinF,LOW);
    digitalWrite(pinG,LOW);
    digitalWrite(pinH,LOW);
    digitalWrite(pinL,LOW);
    digitalWrite(pinN,LOW);
    
    //Choose which digit to write to the seven-seg display
    if (digit1 < 10) {
      displayFromDigit(digit1);
      digitalWrite(pinKM,LOW);
      digit1 = 10;
    } else if (digit2 < 10) {
      displayFromDigit(digit2);
      digitalWrite(pinO,LOW);
      digit2 = 10;
    } else if (digit3 < 10) {
      displayFromDigit(digit3);
      digitalWrite(pinP,LOW);
      digit1 = repeat1;
      digit2 = repeat2;
    }
    
    //Check if the puzzle's circuit is complete. If it is, turn on the light.
    int switchState = digitalRead(switchPin);
    if (switchState == HIGH) {
      finished = true;
      digitalWrite(LEDPin, HIGH);
      Serial.println("Finished");
    } else {
      countdown = countdown - 1;
    }
    delay(5);
    
  }
  
}

void displayFromDigit(int num) {
  //Display a digit on the Seven-Segment Display
  if (num == 0) {
    digitalWrite(pinC,HIGH);
    digitalWrite(pinE,HIGH);
    digitalWrite(pinF,HIGH);
    digitalWrite(pinH,HIGH);
    digitalWrite(pinL,HIGH);
    digitalWrite(pinN,HIGH);
  } else if (num == 1) {
    digitalWrite(pinC,HIGH);
    digitalWrite(pinL,HIGH);
  } else if (num == 2) {
    digitalWrite(pinF,HIGH);
    digitalWrite(pinG,HIGH);
    digitalWrite(pinH,HIGH);
    digitalWrite(pinL,HIGH);
    digitalWrite(pinN,HIGH);
  } else if (num == 3) {
    digitalWrite(pinC,HIGH);
    digitalWrite(pinF,HIGH);
    digitalWrite(pinG,HIGH);
    digitalWrite(pinL,HIGH);
    digitalWrite(pinN,HIGH);
  } else if (num == 4) {
    digitalWrite(pinC,HIGH);
    digitalWrite(pinE,HIGH);
    digitalWrite(pinG,HIGH);
    digitalWrite(pinL,HIGH);
  } else if (num == 5) {
    digitalWrite(pinC,HIGH);
    digitalWrite(pinE,HIGH);
    digitalWrite(pinF,HIGH);
    digitalWrite(pinG,HIGH);
    digitalWrite(pinN,HIGH);
  } else if (num == 6) {
    digitalWrite(pinC,HIGH);
    digitalWrite(pinE,HIGH);
    digitalWrite(pinF,HIGH);
    digitalWrite(pinG,HIGH);
    digitalWrite(pinH,HIGH);
  } else if (num == 7) {
    digitalWrite(pinC,HIGH);
    digitalWrite(pinL,HIGH);
    digitalWrite(pinN,HIGH);
  } else if (num == 8) {
    digitalWrite(pinC,HIGH);
    digitalWrite(pinE,HIGH);
    digitalWrite(pinF,HIGH);
    digitalWrite(pinG,HIGH);
    digitalWrite(pinH,HIGH);
    digitalWrite(pinL,HIGH);
    digitalWrite(pinN,HIGH);
  } else if (num == 9) {
    digitalWrite(pinC,HIGH);
    digitalWrite(pinE,HIGH);
    digitalWrite(pinL,HIGH);
    digitalWrite(pinG,HIGH);
    digitalWrite(pinN,HIGH);
  }
  
}

