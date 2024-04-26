/* This program tests the rotatry encoder using a lookup table to compare the states.
More info at: https://garrysblog.com/2021/03/20/reliably-debouncing-rotary-encoders-with-arduino-and-esp32/

Tested with:
ESP32-S2-DEV 
*/

#define ROTARY_LEFT_PIN 4
#define ROTARY_RIGHT_PIN 1
#define ROTARY_BUTTON_PIN 3

bool rightState = 0;
bool leftState = 0;
bool buttonState = 0;

int8_t checkRotaryEncoder(){

  static uint8_t old_AB = 3;  // Lookup table index
  static int8_t encval = 0;   // Encoder value  
  static const int8_t enc_states[]  = {0,-1,1,0,1,0,0,-1,-1,0,0,1,0,1,-1,0}; // Lookup table

  old_AB <<=2;  // Remember previous state 

  if (digitalRead(ROTARY_LEFT_PIN)) old_AB |= 0x02; // Add current state of pin A
  if (digitalRead(ROTARY_RIGHT_PIN)) old_AB |= 0x01; // Add current state of pin B
   
  encval += enc_states[( old_AB & 0x0f )];
 
  // Update counter if encoder has rotated a full indent, that is at least 4 steps
  if( encval > 3 ) {        // Four steps forward
    encval = 0;
    return 1; //Right
  }
  else if( encval < -3 ) {  // Four steps backwards
   encval = 0;
    return -1; //Left
  }

  return 0;
  
}

void setup() {
  
  pinMode(ROTARY_LEFT_PIN, INPUT);
  pinMode(ROTARY_RIGHT_PIN, INPUT);
  pinMode(ROTARY_BUTTON_PIN, INPUT_PULLUP);

  Serial.begin(115200);

}

void loop() {

  int8_t rotation = checkRotaryEncoder();

  if (rotation == 1) {

    Serial.println("Right");
  } 
  else if (rotation == -1) {

    Serial.println("Left");
  }
  
  buttonState = digitalRead(ROTARY_BUTTON_PIN);
  if (buttonState == HIGH) {
    delay(200);
    Serial.println("Select Button pressed");
  }
  

}
