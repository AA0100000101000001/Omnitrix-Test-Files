/*
This is an update to Button Test with interrupts. It implements the basic omnitrix modes and alien selection.
*/
/*
//ESP32-S2
#define buttonPin 5 //Start button
#define RightPin 1 //Right button
#define LeftPin 4 //Left button
#define SelectPin 3 //Select button
*/
//ESP32-S3-Pico
#define buttonPin 2 //Start button
#define RightPin 6 //Right button
#define LeftPin 5 //Left button
#define SelectPin 4 //Select button
#define ALIEN_NUMBER 11 //0-12

bool buttonState = false; //State of start button
bool rightState = false; //State of right
bool leftState = false; //State of left
bool selectbuttonState = false; //State of select button

int mode = 1;
int alienNo = 0;

//variables to keep track of the timing of recent interrupts
unsigned long button_time = 0;  
unsigned long last_button_time = 0; 

void IRAM_ATTR button_interrupt() {
  //Debouncing
  button_time = millis();
  if (button_time - last_button_time > 200)
  {
    buttonState = true;
    last_button_time = button_time;
  }
}

void IRAM_ATTR Rightbutton_interrupt() {
  //Debouncing
  button_time = millis();
  if (button_time - last_button_time > 200)
  {
    rightState = true;
    last_button_time = button_time;
  }
}

void IRAM_ATTR Leftbutton_interrupt() {
  //Debouncing
  button_time = millis();
  if (button_time - last_button_time > 200)
  {
    leftState = true;
    last_button_time = button_time;
  }
}

void IRAM_ATTR Selectbutton_interrupt() {
  //Debouncing
  button_time = millis();
  if (button_time - last_button_time > 200)
  {
    selectbuttonState = true;
    last_button_time = button_time;
  }
}

void setup() {
    Serial.begin(115200);

    pinMode(buttonPin, INPUT);
    attachInterrupt(buttonPin, button_interrupt, RISING);
    pinMode(RightPin, INPUT);
    attachInterrupt(RightPin, Rightbutton_interrupt, RISING);
    pinMode(LeftPin, INPUT);
    attachInterrupt(LeftPin, Leftbutton_interrupt, RISING);
    pinMode(SelectPin, INPUT);
    attachInterrupt(SelectPin, Selectbutton_interrupt, RISING);
}

void loop() {
    if (buttonState) {
      Serial.printf("Button pressed\n");
      buttonState = false;

      switch (mode) {
        //Omnitrix is in start mode
        case 1:
          //Go to select alien mode
          mode = 2;
          break;
        //Omnitrix is in select alien mode
         case 2:
          //Go to start mode
          mode = 1;
          break;
      }
      Serial.print("mode = ");
      Serial.println(mode);
    }
    if (rightState) {
      Serial.printf("Right Button pressed\n");
      rightState = false;

      switch (mode) {
        //Omnitrix is in select alien mode
        case 2:
          if ((alienNo  + 1)> ALIEN_NUMBER ) {
            alienNo = 0;
          }
          else {
            alienNo += 1;
          }
          Serial.print("alien: ");
          Serial.println(alienNo);
        break;
      }
    }
    if (leftState) {
      Serial.printf("Left Button pressed\n");
      leftState = false;

      switch (mode) {
        //Omnitrix is in select alien mode
        case 2:
          if ((alienNo - 1) < 0 ) {
            alienNo = ALIEN_NUMBER;
          }
          else {
            alienNo -= 1;
          }
          Serial.print("alien: ");
          Serial.println(alienNo);
          break;
      }
    }
    if (selectbuttonState) {
      Serial.printf("Select Button pressed\n");
      selectbuttonState = false;

      switch (mode) {
        //Omnitrix is in select alien mode
        case 2:
          //Go to transformation mode
          mode = 3;
          break;
        //Omnitrix is in transformation mode
         case 3:
          //Go to start mode
          mode = 1;
          break;
      }
      Serial.print("mode = ");
      Serial.println(mode);

    }
}
