
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

//Define touch LCD
#if defined ESP32_S3_TOUCH_LCD_1_28
	//Using CST816S touch driver
#endif


//-------------------------------------------------------
//----------DON'T EDIT THIS------------------------------
//-------------------------------------------------------