/* This program tests the rotatry encoder in input pull up connection.

Tested with:
ESP32-S2-DEV 
*/

#define ROTARY_LEFT_PIN 4
#define ROTARY_RIGHT_PIN 1
#define ROTARY_BUTTON_PIN 3

bool rightState = 0;
bool leftState = 0;
bool buttonState = 0;

int encoderPos = 0;

void setup() {
  
  pinMode(ROTARY_LEFT_PIN, INPUT);
  pinMode(ROTARY_RIGHT_PIN, INPUT);
  pinMode(ROTARY_BUTTON_PIN, INPUT_PULLUP);

  Serial.begin(115200);

}

void loop() {


  rightState = digitalRead(ROTARY_LEFT_PIN);

  if (rightState == LOW) {
    Serial.println("Right");
    delay(200);
  }
  
  leftState = digitalRead(ROTARY_RIGHT_PIN);

  if (leftState == LOW) {
    Serial.println("Left");
    delay(200);
  }
  
  buttonState = digitalRead(ROTARY_BUTTON_PIN);
  if (buttonState == HIGH) {
    delay(200);
    Serial.println("Select Button pressed");
  }
  

}
