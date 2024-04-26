/* This program tests the rotatry encoder in input pull up connection.

Tested with:
ESP32-S2-DEV 
*/

int anienNo = 0;
int rightState = 0;
int leftState = 0;
int encoderPos = 0;
int buttonState = 0;


int A = 4;
int B = 1;
int S = 3;

void setup() {
  
  pinMode(A, INPUT);
  pinMode(B, INPUT);
  pinMode(S, INPUT_PULLUP);

  Serial.begin(115200);

}

void loop() {


  rightState = digitalRead(A);

  if (rightState == LOW) {
    Serial.println("Right");
    delay(200);
  }
  
  leftState = digitalRead(B);

  if (leftState == LOW) {
    Serial.println("Left");
    delay(200);
  }
  
  buttonState = digitalRead(S);
  if (buttonState == HIGH) {
    delay(200);
    Serial.println("Select Button pressed");
  }
  

}
