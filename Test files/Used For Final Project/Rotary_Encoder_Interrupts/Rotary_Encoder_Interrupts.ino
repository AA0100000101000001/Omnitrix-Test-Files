/*
//Esp32-S2
#define ROTARY_LEFT_PIN 4
#define ROTARY_RIGHT_PIN 1
*/
//Esp32-S3-Pico
#define ROTARY_LEFT_PIN 5 //A
#define ROTARY_RIGHT_PIN 6 //B

bool rightState = 0; //State of right
bool leftState = 0; //State of left

void setup() {
  pinMode(ROTARY_LEFT_PIN, INPUT_PULLUP); // Using internal pullup resistor
  pinMode(ROTARY_RIGHT_PIN, INPUT_PULLUP);

  attachInterrupt(ROTARY_LEFT_PIN, rotEncoder, CHANGE); // Need to detect both rising or falling signal
  attachInterrupt(ROTARY_RIGHT_PIN, rotEncoder, CHANGE);

  Serial.begin (115200);
}

void rotEncoder() {

  static uint8_t old_AB = 3;  // Lookup table index
  static int8_t encval = 0;   // Encoder value  
  static const int8_t enc_states[]  = {0,-1,1,0,1,0,0,-1,-1,0,0,1,0,1,-1,0}; // Lookup table
  static unsigned long lastInterruptTime = 0;
  unsigned long interruptTime = millis();

  old_AB <<=2;  // Remember previous state 

  if (digitalRead(ROTARY_LEFT_PIN)) old_AB |= 0x02; // Add current state of pin A
  if (digitalRead(ROTARY_RIGHT_PIN)) old_AB |= 0x01; // Add current state of pin B
   
  encval += enc_states[( old_AB & 0x0f )];
 
  // Update counter if encoder has rotated a full indent, that is at least 4 steps
  if( encval > 3 ) {        // Four steps forward
    if (interruptTime - lastInterruptTime > 80) {
      rightState = true; //Right
    }
    encval = 0;
    lastInterruptTime = millis(); 
  }
  else if( encval < -3 ) {  // Four steps backwards
   if (interruptTime - lastInterruptTime > 80) {
      leftState = true; //Left
    }
    encval = 0;
    lastInterruptTime = millis(); 
  }
}

void loop() {

  if (rightState) {
    Serial.printf("Right\n");
    rightState = false;

  }
  if (leftState) {
    Serial.printf("Left\n");
    leftState = false;

  }
}