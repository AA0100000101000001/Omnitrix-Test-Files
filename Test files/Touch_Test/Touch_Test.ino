/*
Test for ESP32-S3 ROUND LCD 1.28 TOUCH DISPLAY with CST816S driver.
*/

#include <SPI.h>
#include <TFT_eSPI.h>
#include "CST816S.h"

//TFT_eSPI tft = TFT_eSPI();
CST816S touch(6, 7, 13, 5);	// sda, scl, rst, irq

//====================================================================

void setup(void) {
  Serial.begin(115200);
  touch.begin();
  Serial.println("\n\nStarting...");

  //tft.init();
}

//====================================================================

void loop() {

  if (touch.available()){
    Serial.printf("Gesture: %s     ", touch.gesture());
    Serial.printf("x: %i     ", touch.data.x);
    Serial.printf("y: %i     \n", touch.data.y);

    //Right touch
    if (touch.data.x < 60 && touch.data.y < 190) {

      Serial.println("Right");
    }
    //Left touch
    else if (touch.data.x > 180 && touch.data.y < 190) {

      Serial.println("Left");
    }
    //Bottom touch
    else if (touch.data.y > 190) {

      Serial.println("Bottom");
    }
    //Middle touch
    else {

      Serial.println("Middle");
    }
  }

  delay(250);

}

//====================================================================

