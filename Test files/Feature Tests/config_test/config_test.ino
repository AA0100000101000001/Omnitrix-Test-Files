/*
This is a test for configuring pins and settings using ifdef
*/

#include "User_Setup.h"

//Checking TFT_eSPI pinouts
//#include <TFT_eSPI.h>
//TFT_eSPI tft = TFT_eSPI();

#if defined SOUND_ENABLED
  #if defined SOUND_MUTED_IN_BOOTING
    bool mute = true;
  #else
    bool mute = false;
  #endif


  //Function that plays sound
  void playsound() {

    Serial.println("Using Sound");

    //Check if sound is muted in booting
    if (mute) {
      Serial.print("Sound muted, ");
      Serial.println(mute);
    } else {
      Serial.print("Sound unmuted, ");
      Serial.println(mute);
    }
  }
#endif


//Function that shows animation type
void display_animation() {

  //Start animation with images
  #if defined START_ANIMATION_WITH_IMAGES
    Serial.println("Start animation with images");
  #endif

  //Hard coded start animation
  #if defined START_ANIMATION_WITHOUT_IMAGES
    Serial.println("Hard coded start animation");
  #endif
}




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

  //Check which Development board is being used
  #ifdef ESP32_S2_PINOUT
  Serial.println("Using ESP32-S2 Dev with GC9101 Display");
  #endif
  #ifdef ESP32_S3_PINOUT
  Serial.println("Using ESP32-S3 Dev with GC9101 Display");
  #endif

  //Check if demo is enebled
  #ifdef DEMO_ENABLED
  Serial.println("Demo of the software is enabled");
  #endif
  //Check type of demo
  #ifdef DEMO_AYTOMATED_ENABLED
  Serial.println("Demo automated display of the features");
  #elif DEMO_CONTROLLED_ENABLED
  Serial.println("Demo user controlled");
  #endif

  //Check if button interrupts are being used
  #ifdef POP_UP_BUTTONS_ENABLED
    Serial.println("Using Buttons for the pop up mechanism");

    Serial.print("START_BUTTON_PIN = ");
    Serial.println(START_BUTTON_PIN);

    Serial.print("SELECT_BUTTON_PIN = ");
    Serial.println(SELECT_BUTTON_PIN);

  #endif

  //Use of micro switches for encoder
  #ifdef MICRO_SWITCHES_ROTARY_ENCODER_ENABLED
    Serial.println("Using micro switches for encoder");

    Serial.print("RIGHT_BUTTON_PIN = ");
    Serial.println(RIGHT_BUTTON_PIN);

    Serial.print("LEFT_BUTTON_PIN = ");
    Serial.println(LEFT_BUTTON_PIN);
  #endif

  //Use of magnetic encoder
  #ifdef MAGNETIC_ROTARY_ENCODER_ENABLED
    Serial.println("Using magnetic encoder");

    Serial.print("RIGHT_BUTTON_PIN = ");
    Serial.println(RIGHT_BUTTON_PIN);

    Serial.print("LEFT_BUTTON_PIN = ");
    Serial.println(LEFT_BUTTON_PIN);
  #endif


  //Check if sound is being used
  #ifdef SOUND_ENABLED
    playsound();
  #endif

  //Check if using Dfplayer pro sound
  #ifdef SOUND_DFPLAYER_PRO_ENABLED
  Serial.println("Using Dfplayer pro sound");

  Serial.print("RXD1 = ");
  Serial.println(RXD1);

  Serial.print("TXD1 = ");
  Serial.println(TXD1);

  #endif

  //Check if using buzzer sound
  #ifdef SOUND_BUZZER_ENABLED
  Serial.println("Using Buzzzer sound");

  Serial.print("BUZZER_PIN = ");
  Serial.println(BUZZER_PIN);

  #endif

  //Check if LEDs are enabled
  Serial.println("Using LEDs");

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

  //Check if Neopixel ring LEDs are being used
  #ifdef NEOPIXEL_RING_LEDS_ENABLED
  Serial.println("Using Neopixel Ring");

  Serial.print("LED_DI = ");
  Serial.println(LED_DI);

  #endif

  //Check if IR controlled LEDs are being used
  #ifdef IR_CONTROLLED_LEDS_ENABLED
  Serial.println("Using IR controlled LEDs");

  Serial.print("LED_IR_TRANS = ");
  Serial.println(LED_IR_TRANS);

  #endif

  //Show what type of animation is being used
  display_animation();

  Serial.println("");

  delay(5000);

}
