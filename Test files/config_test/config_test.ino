/*
This is a test for configuring pins using ifdef
*/

#include "User_Setup.h"

void setup() {
  Serial.begin(115200);
  
}

void loop() {
  
  
  //Check if CST816S touch driver and GC9A01 lcd display are being used
  #ifdef ESP32_S3_ROUND_DISPLAY_1_28
  Serial.println("Using ESP32-S3 Round Display 1.28");
  #endif

  //Check if no touch GC9A01 display is being used
  #ifdef OMNITRIX_CUSTOM_GC9A01
  Serial.println("Using no touch GC9101 Display");
  #endif

  //Check if button interrupts are being used
  #ifdef BUTTONS_ENABLED
  Serial.println("Using Button interrupts");
  #endif

  //Check if sound is being used
  #ifdef SOUND_ENABLED
  Serial.println("Using Sound");
  #endif

  //Check if RGB LEDs are being used
  #ifdef RGB_LEDS_ENABLED
  Serial.println("Using RGB LEDs");
  #endif

  delay(5000);

}
