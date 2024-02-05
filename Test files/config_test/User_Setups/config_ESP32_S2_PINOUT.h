
//Uncomment for CST816S touch driver and GC9A01 lcd display
//#define ESP32_S3_TOUCH_LCD_1_28
//Uncomment for no touch GC9A01 display
#define ESP32_S2_PINOUT

//Uncomment for buttons
#define BUTTONS_ENABLED

//Uncomment for sound
//#define SOUND_ENABLED

//Uncomment for RGB LEDS
#define RGB_LEDS_ENABLED


//Define pins for ESP32-S2 board
//Define button pins
#if defined ESP32_S2_PINOUT && defined BUTTONS_ENABLED

	#define START_BUTTON_PIN 5
	#define RIGHT_BUTTON_PIN 1
	#define LEFT_BUTTON_PIN 4
	#define SELECT_BUTTON_PIN 3

#endif
//Define RGB LED pins
#if defined ESP32_S2_PINOUT && defined RGB_LEDS_ENABLED

	#define RGB_LED_R 6
	#define RGB_LED_G 7
	#define RGB_LED_B 8

#endif


//Define pins for ESP32-S3 Touch LCD 1.28 board
//Define button pins
#if defined ESP32_S3_TOUCH_LCD_1_28 && defined BUTTONS_ENABLED
	
	#define START_BUTTON_PIN 15
	#define RIGHT_BUTTON_PIN 16
	#define LEFT_BUTTON_PIN 17
	#define SELECT_BUTTON_PIN 18

#endif