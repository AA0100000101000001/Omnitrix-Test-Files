/* 
This program uses four buttons in active high connection. 

Tested with:
ESP32-S2-DEV
*/

const int buttonPin = 5;  // the number of the pushbutton pin
const int ledPin = 2;    // the number of the LED pin
int A = 1;
int B = 4;
int S = 3;

int buttonState = 0;  // variable for reading the pushbutton status
int rightState = 0;
int leftState = 0;
int selectButtonState = 0;
int mode = 1;

void setup() {
  
  // initialize the pushbutton pin as an input:
  pinMode(buttonPin, INPUT);
  // initialize left and right buttons
  pinMode(A, INPUT);
  pinMode(B, INPUT);
  // initalize select button
  pinMode(S, INPUT);

  // initialize the LED pin as an output:
  pinMode(ledPin, OUTPUT);

  Serial.begin(115200);
}

void loop() {
  // read the state of the pushbutton value:
  buttonState = digitalRead(buttonPin);

  if (buttonState == HIGH) {
    
    delay(200);
    Serial.println("Button pressed");
  }
/*
  //If button is pressed then led is turned on
  if (mode == 1) {
    // check if the pushbutton is pressed. If it is, the buttonState is LOW:
    if (buttonState == HIGH) {
      // turn LED on:
      digitalWrite(ledPin, HIGH);
      mode = 2;
      delay(200);
      Serial.println("Button pressed");
    }

  //If button is pressed then led is turned off
  } else if (mode == 2) {
    
    if (buttonState == HIGH) {
      // turn LED off:
      digitalWrite(ledPin, LOW);
      mode = 1;
      delay(200);
      Serial.println("Button pressed");
    }
  }
*/

  //read right botton state
  rightState = digitalRead(A);

  //right botton is pressed
  if (rightState == HIGH) {
    delay(300);
    Serial.println("Right");
  }
  
  //read left botton state
  leftState = digitalRead(B);

  //left botton is pressed
  if (leftState == HIGH) {
    delay(300);
    Serial.println("Left");
  }

  //read select botton state
  selectButtonState = digitalRead(S);

  //left botton is pressed
  if (selectButtonState == HIGH) {
    delay(300);
    Serial.println("Select button pressed");
  }
  
}
