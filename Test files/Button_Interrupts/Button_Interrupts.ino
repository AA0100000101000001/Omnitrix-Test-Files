#define buttonPin 5 //Start button
#define RightPin 1 //Right button
#define LeftPin 4 //Left button
#define SelectPin 3 //Select button

bool buttonState = false; //State of start button
bool rightState = false; //State of right
bool leftState = false; //State of left
bool selectbuttonState = false; //State of select button

int mode = 0;

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
        case 0:
          mode = 1;
          break;
         case 1:
          mode = 0;
          break;
      }
      Serial.print("mode = ");
      Serial.println(mode);
    }
    if (rightState) {
      Serial.printf("Right Button pressed\n");
      rightState = false;
    }
    if (leftState) {
      Serial.printf("Left Button pressed\n");
      leftState = false;
    }
    if (selectbuttonState) {
      Serial.printf("Select Button pressed\n");
      selectbuttonState = false;
      switch (mode) {
        case 1:
          mode = 2;
          break;
         case 2:
          mode = 0;
          break;
      }
      Serial.print("mode = ");
      Serial.println(mode);

    }
}