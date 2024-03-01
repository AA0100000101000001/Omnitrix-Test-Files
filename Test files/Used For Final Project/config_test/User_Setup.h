
//Edit User_Setups/config_DEFAULT to create your own configuration or uncomment your preferred configuration

#include "User_Setups/config_ESP32_S2_PINOUT.h"
//#include "User_Setups/config_ESP32_S3_TOUCH_LCD_1_28.h"


//-------------------------------------------------------
//----------DON'T EDIT THIS------------------------------
//-------------------------------------------------------


//Define button pins
#if defined BUTTONS_ENABLED

	#define START_BUTTON_PIN 	CONFIG_START_BUTTON_PIN
	#define RIGHT_BUTTON_PIN	CONFIG_RIGHT_BUTTON_PIN
	#define LEFT_BUTTON_PIN		CONFIG_LEFT_BUTTON_PIN
	#define SELECT_BUTTON_PIN	CONFIG_SELECT_BUTTON_PIN

#endif

//Define RGB LED pins
#if defined RGB_LEDS_ENABLED

	#define RGB_LED_R CONFIG_RGB_LED_R
	#define RGB_LED_G CONFIG_RGB_LED_G
	#define RGB_LED_B CONFIG_RGB_LED_B

#endif

/* Failed LCD pin configuration
//Define Esp32-s2 development board pins
#if defined ESP32_S2_PINOUT
  #include "User_Setups/Setup303_ESP32S2_GC9A01.h"
#endif

//Define Esp32-s3 touch LCD pins
#if defined ESP32_S3_TOUCH_LCD_1_28
	//Using integrated Touch LCD with GC9A01/CST816S drivers
  #include "User_Setups/Setup302_ESP32S3_GC9A01_TOUCH.h"
#endif
*/

//-------------------------------------------------------
//----------DON'T EDIT THIS------------------------------
//-------------------------------------------------------