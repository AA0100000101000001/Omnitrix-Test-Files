/* This program tests the ability of the omnitrix to go into deep sleep mode after a short period of time of inactivity and wake up when the transformation time is over 
in order to go to the recharging state. Interrupts are used to check input*/

#define buttonPin 5 //Start button
#define RightPin 1 //Right button
#define LeftPin 4 //Left button
#define SelectPin 3 //Select button

#define ALIEN_NUMBER 11 //0-12

#define uS_TO_S_FACTOR 1000000ULL  /* Conversion factor for micro seconds to seconds */
#define DEEP_SLEEP_TIMER 5 // 5 sec
uint32_t start; //timer for deep sleep

#define ALIEN_TRANSFORMATION_TIME_TEST 20 //10 sec
#define OMNITRIX_RECHARGE_TIME_TEST 20 //10 sec
#define ALIEN_TRANSFORMATION_TIME_DEFAULT 60 //1 min
#define OMNITRIX_RECHARGE_TIME_DEFAULT 60 //1 min

//Convert timer variables int micro seconds
int transform_time_val = ALIEN_TRANSFORMATION_TIME_TEST * uS_TO_S_FACTOR;
int recharge_time_val = OMNITRIX_RECHARGE_TIME_TEST * uS_TO_S_FACTOR;

//Time variables that are saved in deep sleep mode
RTC_DATA_ATTR uint32_t transformation_start_time;
RTC_DATA_ATTR uint32_t recharging_start_time;
RTC_DATA_ATTR uint32_t transformation_start_time_offset;
RTC_DATA_ATTR uint32_t recharging_start_time_offset;

RTC_DATA_ATTR unsigned long millisOffset=0;

RTC_DATA_ATTR int bootCount = 0; //Number of times the system wakes up
RTC_DATA_ATTR int mode = 1; //Omnitrix state
RTC_DATA_ATTR int alienNo = 0; //Alien number

//variables to keep track of the timing of recent interrupts
unsigned long button_time = 0;  
unsigned long last_button_time = 0; 

//Input States
bool buttonState = false; //State of start button
bool rightState = false; //State of right
bool leftState = false; //State of left
bool selectbuttonState = false; //State of select button

//------INTERRUPTS------------------------
//----------------------------------------

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

//------INTERRUPTS-END--------------------
//----------------------------------------

// the setup function runs once when you press reset or power the board or wake up from deep sleep
void setup() {

  Serial.begin(115200);

  //Increment boot number and print it every reboot
  ++bootCount;
  Serial.println("Boot number: " + String(bootCount));
  delay(100);
  Serial.print("Mode: ");
  Serial.println(mode);

  if (bootCount == 1) {
    RTC_setTime(0, 0, 0, 1, 1, 2023, 0);  // 1st Jan 2023 00:00:00:00
  }

  //The omnitrix will wake up when the button is pressed
  esp_sleep_enable_ext0_wakeup(GPIO_NUM_5,1);

  //initialize inputs and interrupts
  pinMode(buttonPin, INPUT);
  attachInterrupt(buttonPin, button_interrupt, RISING);
  pinMode(RightPin, INPUT);
  attachInterrupt(RightPin, Rightbutton_interrupt, RISING);
  pinMode(LeftPin, INPUT);
  attachInterrupt(LeftPin, Leftbutton_interrupt, RISING);
  pinMode(SelectPin, INPUT);
  attachInterrupt(SelectPin, Selectbutton_interrupt, RISING);

  //Check the wakeup reason for ESP32
  get_wakeup_reason();

  //reset timer 
  start = RTC_getLocalEpoch(); // Get epoch
}

// the loop function runs over and over again forever
void loop() {
    if (buttonState) {
      Serial.printf("Button pressed\n");
      buttonState = false;

      switch (mode) {
        //Omnitrix is in start mode
        case 1:
          //Go to select alien mode
          mode = 2;
          Serial.println("Mode 2");

          //reset timer
          start = RTC_getLocalEpoch();
          break;

        //Omnitrix is in select alien mode
         case 2:
          //Go to start mode
          mode = 1;
          Serial.println("Mode 1");

          //reset timer
          start = RTC_getLocalEpoch();
          break;
      }
      
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

          //reset timer
          start = RTC_getLocalEpoch();
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

          //reset timer
          start = RTC_getLocalEpoch();
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
          mode2ToMode3();

          //reset timer
          start = RTC_getLocalEpoch();
          break;

        //Omnitrix is in transformation mode
         case 3:
          //Go to start mode
          mode = 1;
          Serial.println("Button pressed, untransforming and going back to Start mode");

          //Disable waking up by timer
          esp_sleep_disable_wakeup_source(ESP_SLEEP_WAKEUP_TIMER);
          Serial.println("Disabled Timer1");

          //reset timer
          start = RTC_getLocalEpoch();
          break;
      }
      Serial.print("mode ");
      Serial.println(mode);

    }
    if (mode == 3){
      mode3();
    }
    if (mode == 4){
      mode4();
    }

    //Check timer for deep sleep
    check_timer();
}

void mode2ToMode3() {

  mode = 3;
  delay(200);
  Serial.println("Tranformed into alien");

  Serial.println(RTC_getLocalEpoch()); //Get minutes passed since first boot
  //reset transformation time to current epoch
  transformation_start_time = RTC_getLocalEpoch();
  //Set offset to time passed since last time the timer was checked (in sec)
  transformation_start_time_offset = RTC_getLocalEpoch() - transformation_start_time;

  //Configure the wake up source to wake up every time the transfomation is done
  esp_sleep_enable_timer_wakeup(transform_time_val - transformation_start_time_offset * uS_TO_S_FACTOR);
  Serial.println("Transformation: Setup ESP32 to sleep every " + String(ALIEN_TRANSFORMATION_TIME_TEST - transformation_start_time_offset) +
  " Seconds");

}

void mode3() {

  //Check transformation time
  //Transformation time is done while omnitrix does not sleep
  if ((RTC_getLocalEpoch() - transformation_start_time) > ALIEN_TRANSFORMATION_TIME_TEST) {

    mode3ToMode4();

  //Transformation time is not finished
  } else {
    //Set offset to time passed since last time the timer was checked (in sec)
    transformation_start_time_offset = RTC_getLocalEpoch() - transformation_start_time;
  }

  //Check timer for deep sleep
  check_timer();

}

void mode4() {

  //Check recharging time
  //Recharging time is done
  if ((RTC_getLocalEpoch() - recharging_start_time) > OMNITRIX_RECHARGE_TIME_TEST) {

    mode4ToMode1();

  //Recharging time is not finished
  } else {
    //Set offset to time passed since last time the timer was checked (in sec)
    recharging_start_time_offset = RTC_getLocalEpoch() - recharging_start_time;
  }
  
  //Check timer for deep sleep
  check_timer();

}

void mode3ToMode4() {

  //reset recharging time
  recharging_start_time = RTC_getLocalEpoch();
  //Set offset to time passed since last time the timer was checked (in sec)
  recharging_start_time_offset = RTC_getLocalEpoch() - recharging_start_time;

  mode = 4;

  //Configure the wake up source to wake up every time the recharge is done
  esp_sleep_enable_timer_wakeup(recharge_time_val - recharging_start_time_offset * uS_TO_S_FACTOR);
  Serial.println("Recharging1: Setup ESP32 to sleep every " + String(OMNITRIX_RECHARGE_TIME_TEST - recharging_start_time_offset) +
  " Seconds");

}

void mode4ToMode1() {

  mode = 1;

  //Disable waking up by timer
  esp_sleep_disable_wakeup_source(ESP_SLEEP_WAKEUP_TIMER);
  Serial.println("Disabled Timer2");

}

//Check time for deep sleep
void check_timer() {

  //if the time has passed then go to deep sleep
  if ((RTC_getLocalEpoch() - start) > DEEP_SLEEP_TIMER) {

    Serial.println("Going to sleep");
    
    esp_deep_sleep_start();
  }
}

void get_wakeup_reason() {

  esp_sleep_wakeup_cause_t wakeup_reason;
  wakeup_reason = esp_sleep_get_wakeup_cause();

  //Check wake up reason
  switch(wakeup_reason)
  {
    //Wake up by button
    case ESP_SLEEP_WAKEUP_EXT0 : {

      Serial.println("Wakeup caused by external signal using RTC_IO"); 

      //Transformation mode is done, enable deep sleep timer for recharhing
      if (mode == 3) {

        //Set offset to time passed since last time the timer was checked (in sec)
        transformation_start_time_offset = RTC_getLocalEpoch() - transformation_start_time;

        //Configure the wake up source to wake up every time the transfomation is done
        esp_sleep_enable_timer_wakeup(transform_time_val - transformation_start_time_offset * uS_TO_S_FACTOR);
        Serial.println("Transformation: Setup ESP32 to sleep every " + String(ALIEN_TRANSFORMATION_TIME_TEST - transformation_start_time_offset) +
        " Seconds");

      }
      //Recharging mode is done, disable timer
      else if (mode == 4) {

        //Set offset to time passed since last time the timer was checked (in sec)
        recharging_start_time_offset = RTC_getLocalEpoch() - recharging_start_time;

        //Configure the wake up source to wake up every time the recharge is done
        esp_sleep_enable_timer_wakeup(recharge_time_val - recharging_start_time_offset * uS_TO_S_FACTOR);
        Serial.println("Recharging1: Setup ESP32 to sleep every " + String(OMNITRIX_RECHARGE_TIME_TEST - recharging_start_time_offset) +
        " Seconds");

      }

      break;
    }
    //Wake up by timer
    case ESP_SLEEP_WAKEUP_TIMER : {

      Serial.println("Wakeup caused by timer"); 

      //Go to recharge mode after transformation time is finished
      if (mode == 3) {

        mode3ToMode4();

        Serial.println(RTC_getLocalEpoch()); //Get minutes passed since first boot

    
      //Go to start mode after recharge timer is finished
      } else if (mode == 4) {

        mode4ToMode1();

      }
        break;
      }
    //Wake up not caused by deep sleep
    default : Serial.printf("Wakeup was not caused by deep sleep: %d\n",wakeup_reason); break;
  }

}
