/*
This is a test for configuring pins using ifdef
*/

//Checking TFT_eSPI pinouts
//#include <TFT_eSPI.h>
//TFT_eSPI tft = TFT_eSPI();

#include "User_Setup.h"

void setup() {
  Serial.begin(115200);

  //tft.begin();
  
}

void loop() {
  
  Serial.println("");
/*
  //Show LCD pins
  Serial.println("LCD pins are:");

  Serial.print("TFT_MOSI = ");
  Serial.println(TFT_MOSI);
  Serial.print("TFT_SCLK = ");
  Serial.println(TFT_SCLK);
  Serial.print("TFT_CS = ");
  Serial.println(TFT_CS);
  Serial.print("TFT_DC = ");
  Serial.println(TFT_DC);
  Serial.print("TFT_RST = ");
  Serial.println(TFT_RST);
  */
  //Check if CST816S touch driver and GC9A01 lcd display are being used
  #ifdef ESP32_S3_TOUCH_LCD_1_28
  Serial.println("Using ESP32-S3 Touch LCD 1.28 board");
  
  /*Serial.println("Additional LCD pins:");
  Serial.print("TFT_BL = ");
  Serial.println(TFT_BL);
  Serial.print("TFT_MISO = ");
  Serial.println(TFT_MISO);*/
  #endif

  //Check if no touch GC9A01 display is being used
  #ifdef ESP32_S2_PINOUT
  Serial.println("Using ESP32-S2 Dev with GC9101 Display");
  #endif

  //Check if button interrupts are being used
  #ifdef BUTTONS_ENABLED
  Serial.println("Using Button interrupts");

  Serial.print("START_BUTTON_PIN = ");
  Serial.println(START_BUTTON_PIN);

  Serial.print("RIGHT_BUTTON_PIN = ");
  Serial.println(RIGHT_BUTTON_PIN);

  Serial.print("LEFT_BUTTON_PIN = ");
  Serial.println(LEFT_BUTTON_PIN);

  Serial.print("SELECT_BUTTON_PIN = ");
  Serial.println(SELECT_BUTTON_PIN);

  #endif

  //Check if sound is being used
  #ifdef SOUND_ENABLED
  Serial.println("Using Sound");
  #endif

  //Check if RGB LEDs are being used
  #ifdef RGB_LEDS_ENABLED
  Serial.println("Using RGB LEDs");

  Serial.print("RGB_LED_R = ");
  Serial.println(RGB_LED_R);

  Serial.print("RGB_LED_G = ");
  Serial.println(RGB_LED_G);

  Serial.print("RGB_LED_B = ");
  Serial.println(RGB_LED_B);

  #endif

  Serial.println("");

  delay(5000);

}
