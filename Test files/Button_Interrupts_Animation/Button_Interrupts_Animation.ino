/*
This is an update to Button Test with interrupts. It implements the basic omnitrix modes and alien selection.
*/

#include <SPI.h>
#include <TFT_eSPI.h>
#include <PNGdec.h>

#include "omnitrix_alien_backround.h"
#include "omnitrix_aliens.h"
#include "omnitrix_anim.h"

#define OMNITRIX_GREEN 0xA707
#define OMNITRIX_RED 0xC000
#define OMNITRIX_GRAY 0xAD55

TFT_eSPI tft = TFT_eSPI();
PNG png; // PNG decoder instance

#define buttonPin 5 //Start button
#define RightPin 1 //Right button
#define LeftPin 4 //Left button
#define SelectPin 3 //Select button

#define ALIEN_NUMBER 11 //0-12
int omnitrix_anim_N = 10; //11 frames for animation
#define MAX_IMAGE_WDITH 240 // Set rendering line buffer lengths for image

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
    //Start button pressed
    if (buttonState) {
      Serial.printf("Button pressed\n");
      buttonState = false;

      //Check modes
      startButtonModes();
    }
    //Right button pressed
    if (rightState) {
      Serial.printf("Right Button pressed\n");
      rightState = false;

      //Check modes
      rightButtonModes();
    }
    //Left button pressed
    if (leftState) {
      Serial.printf("Left Button pressed\n");
      leftState = false;

      //Check modes
      leftButtonModes();
    }
    //Select button pressed
    if (selectbuttonState) {
      Serial.printf("Select Button pressed\n");
      selectbuttonState = false;

      //Check modes
      selectbuttonModes();

    }
}
