/*
Test for ESP32-S3 ROUND LCD 1.28 TOUCH DISPLAY with CST816S driver. 
This is an update to Touch_Test. Animation is added.
*/

#include <SPI.h>
#include <TFT_eSPI.h>
#include <PNGdec.h>
#include "CST816S.h"

#define MAX_IMAGE_WDITH 240 // Set rendering line buffer lengths for image

#define OMNITRIX_GREEN 0xA707
#define OMNITRIX_RED 0xC000
#define OMNITRIX_GRAY 0xAD55


TFT_eSPI tft = TFT_eSPI();
PNG png; // PNG decoder instance
CST816S touch(6, 7, 13, 5);	// sda, scl, rst, irq

int mode = 1;
RTC_DATA_ATTR int alienNo = 0;
#define ALIEN_NUMBER 11 //0...11 = 12
int omnitrix_anim_N = 10; //11

#include "omnitrix_alien_backround.h"
#include "omnitrix_aliens.h"
#include "omnitrix_anim.h"

//====================================================================

void setup(void) {
  Serial.begin(115200);
  touch.begin();
  Serial.println("\n\nStarting...");

  tft.init();
  //Display start screen
  tft.fillScreen(OMNITRIX_GREEN);
  ShowSymbols();
}

//====================================================================

void loop() {

  if (touch.available()){
    Serial.printf("Gesture: %s     ", touch.gesture());
    Serial.printf("x: %i     ", touch.data.x);
    Serial.printf("y: %i     \n", touch.data.y);

    //Right touch
    if (touch.data.x < 60 && touch.data.y < 190) {
      delay(200);

      Serial.println("Right");
      //Check mode
      rightButtonModes();

    }
    //Left touch
    else if (touch.data.x > 180 && touch.data.y < 190) {
      delay(200);

      Serial.println("Left");
      //Check mode
      leftButtonModes();

    }
    //Bottom touch
    else if (touch.data.y > 190) {
      delay(200);

      Serial.println("Bottom");
      //Check mode
      startButtonModes();

    }
    //Middle touch
    else {
      delay(200);

      Serial.println("Middle");
      //Check mode
      selectbuttonModes();

    }
  }

  delay(250);

}

//====================================================================

